#include "LALR.h"


std::string LALR::countcore(std::unordered_set<LR1Item> itemset)
{

    // 收集当前节点的核心项目集
    std::unordered_set <std::string> coreset;
    for (const auto& item : itemset) {
        std::string str = item.lhs;
        str += "=";
        for (auto j : item.rhs)
        {
            str += j;
            str += "&";
        }
        str += item.dotPos;
        coreset.insert(str);
    }
    std::string result;
    for (auto i : coreset)
    {
        result += i;
        result += "\n";
    }
    std::cout << result;
    return result;
}

// 闭包函数，用于计算LR1项目集的闭包。
std::unordered_set<LR1Item> LALR::closure(const std::unordered_set<LR1Item>& items) {
    std::unordered_set<LR1Item> closureSet = items; // 初始化闭包集为输入的项目集
    bool added; // 标记是否在迭代中添加了新项目
    do {
        added = false; // 每次循环开始时，假定没有添加新项目
        for (const auto& item : closureSet) {
            if (item.dotPos < item.rhs.size()) { // 点未到达产生式右侧的末尾
                std::string symbol = item.rhs[item.dotPos]; // 当前处理的符号
                if (G.unendSet.find(symbol) != G.unendSet.end()) { // 如果是终结符，加入闭包
                    // 对于每个以symbol为左侧符号的产生式，生成新的LR1项目
                    for (const auto& prod : G.ex_G) {
                        if (prod.left == symbol) {
                            std::unordered_set<std::string> lookaheads; // 初始化lookahead集合
                            // 计算lookahead集合
                            if (item.dotPos + 1 < item.rhs.size()) {
                                // 如果点后面还有符号，计算FIRST集合
                                std::string nextSymbol;
                                bool isnull = true;
                                for (int next = item.dotPos + 1; next < item.rhs.size(); next++) {
                                    nextSymbol = item.rhs[next];
                                    if (G.unendSet.find(nextSymbol) == G.unendSet.end()) {
                                        // 如果是终结符，加入lookahead集合
                                        lookaheads.insert(nextSymbol);
                                        isnull = false;
                                        break;
                                    }
                                    else if (G.nullMap[nextSymbol]) {
                                        // 如果是非终结符且可为空，加入FIRST集合
                                        lookaheads.insert(G.firstMap[nextSymbol].begin(), G.firstMap[nextSymbol].end());
                                        lookaheads.erase("@"); // 移除特殊符号
                                    }
                                    else {
                                        // 如果是非终结符且不可为空，加入FIRST集合
                                        lookaheads.insert(G.firstMap[nextSymbol].begin(), G.firstMap[nextSymbol].end());
                                        isnull = false;
                                        break;
                                    }
                                }
                                if (isnull) { // 如果点后所有符号都可为空，加入FOLLOW集合
                                    lookaheads.insert(G.followMap[symbol].begin(), G.followMap[symbol].end());
                                }
                            }
                            else {
                                // 如果点后面没有符号，使用当前lookahead
                                lookaheads.insert(item.lookahead);
                            }
                            // 将新生成的LR1项目加入闭包集
                            for (const auto& lookahead : lookaheads) {
                                LR1Item newItem{ symbol, prod.right, 0, lookahead };
                                if (closureSet.insert(newItem).second) {
                                    added = true; // 如果新项目被添加，标记为true
                                }
                            }
                        }
                    }
                }
            }
        }
    } while (added); // 如果添加了新项目，则继续迭代
    return closureSet; // 返回闭包集
}

// 转移函数，用于计算在给定符号下从某个项目集转移得到新的项目集。
std::unordered_set<LR1Item> LALR::gotoState(const std::unordered_set<LR1Item>& items, const std::string& symbol) {
    std::unordered_set<LR1Item> gotoSet;
    for (const auto& item : items) {
        if (item.dotPos < item.rhs.size() && item.rhs[item.dotPos] == symbol) {
            // 创建新的LR1项目，点向右移动一位
            gotoSet.insert({ item.lhs, item.rhs, item.dotPos + 1, item.lookahead });
        }
    }
    // 对得到的goto集进行闭包操作
    return closure(gotoSet);
}

// 创建LR1自动机
void LALR::createLR1Automaton() {
    // 初始项目集，包含起始符号的起始项目
    std::unordered_set<LR1Item> startItems;

    startItems.insert({ G.ex_G[0].left, {G.ex_G[0].right[0]}, 0, "$" });
    head = new LR1NODE{}; // 创建初始节点
    std::queue<std::unordered_set<LR1Item>> stateQueue; // 用于存储待处理的状态队列
    stateQueue.push(closure(startItems)); // 将初始闭包集入队

    std::unordered_map<std::unordered_set<LR1Item>, LR1NODE*> stateMap; // 映射从项目集到节点
    stateMap[stateQueue.front()] = head; // 将初始闭包集映射到初始节点
    int stateNum = 0; // 状态编号

    while (!stateQueue.empty()) {
        std::unordered_set<LR1Item> currentState = stateQueue.front(); // 获取当前状态
        stateQueue.pop(); // 出队

        LR1NODE* currentNode = stateMap[currentState]; // 获取当前节点

        currentNode->stateNum = stateNum++; // 设置状态编号并递增
        currentNode->items = currentState; // 设置节点的项目集

        // 计算每个符号的转移
        std::unordered_map<std::string, std::unordered_set<LR1Item>> symbolTransitions;
        for (const auto& item : currentState) {
            if (item.dotPos < item.rhs.size()) {
                symbolTransitions[item.rhs[item.dotPos]].insert(item); // 以符号为键，存储项目
            }
        }
        // 为每个符号的转移创建新的节点或更新映射表
        for (const auto& transition : symbolTransitions) {
            auto symbol = transition.first;
            auto newState = gotoState(currentState, symbol); // 计算转移后的状态
            
            if (stateMap.find(newState) == stateMap.end()) {
                // 如果新状态不在映射表中，创建新节点并加入映射表
                LR1NODE* newNode = new LR1NODE{};
                stateMap[newState] = newNode;
                stateQueue.push(newState); // 将新状态入队
            }
            // 更新当前节点的转移表
            currentNode->state[symbol] = stateMap[newState];
        }
    }
}

// 合并同心项目集生成LALR(1)自动机
void LALR::createLALRAutomaton() {
    //// 合并具有相同内核的状态
    //std::unordered_map<std::set<std::pair<std::string, std::vector<std::string>>>, std::unordered_set<LR1NODE*>> coreToStatesMap;
    //std::queue<LR1NODE*> stateQueue;
    //std::unordered_set<LR1NODE*> visitedStates; // 记录已访问的状态
    //stateQueue.push(head); // 将初始节点入队
    //visitedStates.insert(head); // 标记初始节点为已访问
    //while (!stateQueue.empty()) {
    //    LR1NODE* currentNode = stateQueue.front();
    //    stateQueue.pop();

    //    std::set<std::pair<std::string, std::vector<std::string>>> core;
    //    // 收集当前状态的核心项目集
    //    for (const auto& item : currentNode->items) {
    //        core.insert({ item.lhs, item.rhs });
    //    }

    //    // 将当前节点映射到其核心
    //    coreToStatesMap[core].insert(currentNode);

    //    // 遍历当前节点的所有转移
    //    for (const auto& transition : currentNode->state) {
    //        if (visitedStates.find(transition.second) == visitedStates.end()) {
    //            stateQueue.push(transition.second); // 如果转移的目标状态未被访问过，入队
    //            visitedStates.insert(transition.second); // 标记为已访问
    //        }
    //    }
    //}
    //// 合并状态
    //for (auto& entry : coreToStatesMap) {
    //    auto& states = entry.second;
    //    if (states.size() > 1) {
    //        // 如果一个核心映射到多个状态，进行合并
    //        auto it = states.begin();
    //        LR1NODE* firstState = *it;
    //        ++it;
    //        for (; it != states.end(); ++it) {
    //            LR1NODE* state = *it;
    //            // 将其他状态的项目集和转移合并到第一个状态
    //            firstState->items.insert(state->items.begin(), state->items.end());
    //            for (auto& transition : state->state) {
    //                firstState->state[transition.first] = transition.second;
    //            }
    //            delete state; // 删除被合并的状态节点
    //        }
    //    }
    //}
        // 初始项目集，包含起始符号的起始项目
    
    std::unordered_set<LR1Item> startItems;
    startItems.insert({ G.ex_G[0].left, {G.ex_G[0].right[0]}, 0, "$" });
    LALRhead = new LR1NODE{}; // 创建初始节点
    std::queue<std::unordered_set<LR1Item>> stateQueue; // 用于存储待处理的状态队列
    stateQueue.push(closure(startItems)); // 将初始闭包集入队

    std::unordered_map<std::unordered_set<LR1Item>, LR1NODE*> stateMap; // 映射从项目集到节点
    std::unordered_map<std::string, LR1NODE*> coreMap;

    coreMap[countcore(stateQueue.front())] = LALRhead;
    stateMap[stateQueue.front()] = LALRhead; // 将初始闭包集映射到初始节点
    int stateNum = 0; // 状态编号

    while (!stateQueue.empty()) {
        std::unordered_set<LR1Item> currentState = stateQueue.front(); // 获取当前状态
        stateQueue.pop(); // 出队
        LR1NODE* currentNode = stateMap[currentState]; // 获取当前节点
        currentNode->stateNum = stateNum++; // 设置状态编号并递增
        currentNode->items = currentState; // 设置节点的项目集
        indexmap.push_back(currentNode);
        // 收集当前状态的核心项目集
        currentNode->core = countcore(currentState);
        // 计算每个符号的转移
        std::unordered_map<std::string, std::unordered_set<LR1Item>> symbolTransitions;
        for (const auto& item : currentState) {
            if (item.dotPos < item.rhs.size()) {
                symbolTransitions[item.rhs[item.dotPos]].insert(item); // 以符号为键，存储项目
            }
        }

        // 为每个符号的转移创建新的节点或更新映射表
        for (const auto& transition : symbolTransitions) {
            auto symbol = transition.first;
            auto newState = gotoState(currentState, symbol); // 计算转移后的状态
            auto newcore = countcore(newState);
            if (coreMap.find(newcore) == coreMap.end()) {
                // 如果新状态不在映射表中，创建新节点并加入映射表
                LR1NODE* newNode = new LR1NODE{};
                stateMap[newState] = newNode;
                coreMap[newcore] = newNode;

                stateQueue.push(newState); // 将新状态入队
                // 更新当前节点的转移表
                currentNode->state[symbol] = stateMap[newState];
            }
            else
            {
                //合并展望符号
                for (auto i : newState)
                {
                    coreMap[newcore]->items.insert(i);
                }
                //newState = currentNode->items;
                //stateMap[newState] = currentNode;
            }

        }
    }
}


void LALR::generateParsingTable() {
    for (int i = 0; i < indexmap.size(); i++) {
        for (const auto& symbol : G.endSet) {
            actionTable[i][symbol] = "";
            actionTable[i]["$"] = "";
        }
        
        for (const auto& symbol : G.unendSet) {
            gotoTable[i][symbol] = -1;
        }
    }
    // Initialize ACTION and GOTO tables based on LALR(1) states
    for (int i = 0; i < indexmap.size();i++) {
        for (const auto& item :indexmap[i]->items) {
            if (item.dotPos == item.rhs.size()) {
                if (item.lhs == G.first) {
                    actionTable[i][item.lookahead] = "accept";
                }
                else {
                    int prodIndex = G.itemMap[item.lhs + item.rhs2str()];
                    actionTable[i][item.lookahead] = "r" + std::to_string(prodIndex);
                }
            }
            else {
                std::string symbol = item.rhs[item.dotPos];
                if (G.unendSet.find(symbol)==G.unendSet.end()) {
                    auto nextState = indexmap[i]->state.find(symbol);
                    if (nextState != indexmap[i]->state.end()) {
                        actionTable[i][symbol] = "s" + std::to_string(nextState->second->stateNum);
                    }
                }
            }
        }

        for (const auto& j: indexmap[i]->state) {
            const auto & symbol = j.first;
            const auto& nextNode= j.second;
            if (G.unendSet.find(symbol)!= G.unendSet.end()) {
                gotoTable[i][symbol] = nextNode->stateNum;
            }
        }
    }
}

void printAutomaton(const LALR& lalr, LR1NODE* start, QTableWidget* tableWidget) {
    if (!start) return;

    tableWidget->clear(); // 清除现有内容
    tableWidget->setRowCount(0); // 重置行数
    tableWidget->setColumnCount(3); // 设置列数（根据需要调整列数）

    QStringList headers;
    headers << "State" << "Item" << "Lookahead";
    tableWidget->setHorizontalHeaderLabels(headers);

    // 使用BFS遍历自动机的所有节点
    std::unordered_set<LR1NODE*> visited;
    std::queue<LR1NODE*> stateQueue;
    stateQueue.push(start);
    visited.insert(start);

    while (!stateQueue.empty()) {
        LR1NODE* currentNode = stateQueue.front();
        stateQueue.pop();

        // 打印当前状态编号
        int currentRow = tableWidget->rowCount();
        tableWidget->insertRow(currentRow);
        tableWidget->setItem(currentRow, 0, new QTableWidgetItem(QString::number(currentNode->stateNum)));

        QString itemsStr;
        for (const auto& item : currentNode->items) {
            itemsStr += QString("%1 -> ").arg(QString::fromStdString(item.lhs));
            for (size_t i = 0; i < item.rhs.size(); ++i) {
                if (i == item.dotPos) {
                    itemsStr += ". ";
                }
                itemsStr += QString::fromStdString(item.rhs[i]) + " ";
            }
            if (item.dotPos == item.rhs.size()) {
                itemsStr += ".";
            }
            itemsStr += QString(", lookahead: %1\n").arg(QString::fromStdString(item.lookahead));
        }
        tableWidget->setItem(currentRow, 1, new QTableWidgetItem(itemsStr));

        QString transitionsStr;
        for (const auto& transition : currentNode->state) {
            transitionsStr += QString("%1 -> State%2\n").arg(QString::fromStdString(transition.first)).arg(transition.second->stateNum);
            if (visited.find(transition.second) == visited.end()) {
                stateQueue.push(transition.second);
                visited.insert(transition.second);
            }
        }
        tableWidget->setItem(currentRow, 2, new QTableWidgetItem(transitionsStr));
    }

    // 自动调整列宽度
    tableWidget->resizeColumnsToContents();
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->verticalHeader()->setVisible(false);
}

void printParsingTable(const LALR& lalr, QTableWidget* tableWidget) {
    tableWidget->clear();
    tableWidget->setRowCount(0);
    // 找出所有的符号
    std::unordered_set<std::string> symbols;
    for (const auto& stateActions : lalr.actionTable) {
        for (const auto& action : stateActions.second) {
            symbols.insert(action.first);
        }
    }
    for (const auto& stateGotos : lalr.gotoTable) {
        for (const auto& go : stateGotos.second) {
            symbols.insert(go.first);
        }
    }

    QStringList headers;
    headers << "State";
    for (const auto& symbol : symbols) {
        headers << QString::fromStdString(symbol);
    }
    tableWidget->setColumnCount(headers.size());
    tableWidget->setHorizontalHeaderLabels(headers);

    for (const auto& stateActions : lalr.actionTable) {
        int state = stateActions.first;
        int currentRow = tableWidget->rowCount();
        tableWidget->insertRow(currentRow);
        tableWidget->setItem(currentRow, 0, new QTableWidgetItem(QString::number(state)));

        for (const auto& symbol : symbols) {
            QString cellContent;
            if (stateActions.second.find(symbol) != stateActions.second.end()) {
                cellContent = QString::fromStdString(stateActions.second.at(symbol));
            }
            if (lalr.gotoTable.find(state) != lalr.gotoTable.end() &&
                lalr.gotoTable.at(state).find(symbol) != lalr.gotoTable.at(state).end()) {
                if (!cellContent.isEmpty()) {
                    cellContent += ", ";
                }
                cellContent += "goto" + QString::number(lalr.gotoTable.at(state).at(symbol));
            }
            int column = headers.indexOf(QString::fromStdString(symbol));
            if (column != -1) {
                tableWidget->setItem(currentRow, column, new QTableWidgetItem(cellContent));
            }
        }
    }

    // 自动调整列宽度
    tableWidget->resizeColumnsToContents();
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->verticalHeader()->setVisible(false);
}
// LALR构造函数，接受一个文件路径作为参数
LALR::LALR(const std::string filepath) : G(filepath), head(nullptr) {
    // 创建LR1自动机
    createLR1Automaton();
    // 打印LR1自动机的状态
    std::cout << "LR1 AUTOMATION\n";
    // 创建LALR(1)自动机
    std::cout << "LALR1 AUTOMATION\n";
    createLALRAutomaton();
    // 打印LALR(1)自动机的状态
    generateParsingTable();
    // 打印自动机创建完成的消息
    std::cout << "create finish" << std::endl;
}

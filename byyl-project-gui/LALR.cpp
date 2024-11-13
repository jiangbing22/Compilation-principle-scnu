#include "LALR.h"

std::string LALR::countcore(std::unordered_set<LR1Item> itemset)
{
    // 收集当前节点的核心项目集
    std::unordered_set <std::string> coreset;
    // 遍历项目集
    for (const auto& item : itemset) {
        // 初始化字符串，内容为当前项目的左侧符号
        std::string str = item.lhs;
        // 遍历右侧符号
        for (auto j : item.rhs)
        {
            // 将右侧符号依次追加到字符串中
            str += j;
        }
        // 将点位置追加到字符串中
        str += item.dotPos;
        // 将生成的字符串插入到核心项目集中
        coreset.insert(str);
    }
    std::string result;
    // 遍历核心项目集
    for (auto i : coreset)
    {
        // 将核心项目集中的字符串依次追加到结果字符串中
        result += i;
    }
    // std::cout << result;
    return result;
}

// LALR类的closure函数，用于计算LR(1)项集的闭包
std::unordered_set<LR1Item> LALR::closure(const std::unordered_set<LR1Item>& items) {
    // 初始化闭包集合为传入的项集
    std::unordered_set<LR1Item> closureSet = items;
    // 标记是否有新的项被添加到闭包集合中
    bool added;

    // 循环直到没有新的项被添加到闭包集合中
    do {
        added = false;
        // 遍历闭包集合中的每一项
        for (const auto& item : closureSet) {
            // 如果项的点号位置不在最右端
            if (item.dotPos < item.rhs.size()) {
                // 获取点号位置的符号
                std::string symbol = item.rhs[item.dotPos];
                // 如果该符号是非终结符
                if (G.unendSet.find(symbol) != G.unendSet.end()) {
                    // 遍历文法中的所有产生式
                    for (const auto& prod : G.ex_G) {
                        // 如果产生式的左部是当前的非终结符
                        if (prod.left == symbol) {
                            std::unordered_set<std::string> lookaheads;
                            // 正确计算该产生式对应的向前看符号集合

                            // 如果点号位置的下一个符号存在
                            if (item.dotPos + 1 < item.rhs.size()) {
                                bool isNull = true;  // 标记从点号位置后的符号是否都能推导出空串
                                // 遍历点号位置后的所有符号
                                for (int next = item.dotPos + 1; next < item.rhs.size(); ++next) {
                                    std::string nextSymbol = item.rhs[next];
                                    // 如果下一个符号是终结符
                                    if (G.unendSet.find(nextSymbol) == G.unendSet.end()) {
                                        lookaheads.insert(nextSymbol);  // 将其加入向前看符号集合
                                        isNull = false;  // 标记不能推导出空串
                                        break;  // 终止循环
                                    } 
                                    // 如果下一个符号是非终结符且能推导出空串
                                    else if (G.nullMap[nextSymbol]) {
                                        lookaheads.insert(G.firstMap[nextSymbol].begin(), G.firstMap[nextSymbol].end());
                                        lookaheads.erase("@");  // 去除空串标记
                                    } 
                                    // 如果下一个符号是非终结符但不能推导出空串
                                    else {
                                        lookaheads.insert(G.firstMap[nextSymbol].begin(), G.firstMap[nextSymbol].end());
                                        isNull = false;  // 标记不能推导出空串
                                        break;  // 终止循环
                                    }
                                }
                                // 如果从点号位置后的所有符号都能推导出空串
                                if (isNull) {
                                    lookaheads.insert(G.followMap[item.lhs].begin(), G.followMap[item.lhs].end());
                                }
                            } 
                            // 如果点号位置是产生式右部的最右端
                            else {
                                lookaheads.insert(item.lookahead);  // 直接将该项的向前看符号加入集合
                            }

                            // 为新的项设置向前看符号，并尝试加入闭包集合
                            for (const auto& lookahead : lookaheads) {
                                LR1Item newItem{symbol, prod.right, 0, lookahead};
                                // 如果成功加入，则标记有新项被添加
                                if (closureSet.insert(newItem).second) {
                                    added = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    } while (added);  // 如果有新项被添加，则继续循环

    // 返回最终的闭包集合
    return closureSet;
}

std::unordered_set<LR1Item> LALR::gotoState(const std::unordered_set<LR1Item>& items, const std::string& symbol) {
    // 创建一个新的goto集合
    std::unordered_set<LR1Item> gotoSet;

    // 遍历输入的items集合
    for (const auto& item : items) {
        // 判断当前item的点是否在产生式右侧字符串的中间，并且该位置字符与symbol相同
        if (item.dotPos < item.rhs.size() && item.rhs[item.dotPos] == symbol) {
            // 将满足条件的item加入gotoSet，同时将点的位置加1
            gotoSet.insert({ item.lhs, item.rhs, item.dotPos + 1, item.lookahead });
        }
    }

    // 返回gotoSet的闭包
    return closure(gotoSet);
}

void LALR::createLR1Automaton() {
    // 初始化起始项目集合
    std::unordered_set<LR1Item> startItems;
    // 插入起始项目 {G.ex_G[0].left, { G.ex_G[0].right[0] }, 0, "$"}
    startItems.insert({ G.ex_G[0].left, { G.ex_G[0].right[0] }, 0, "$" });

    // 创建头节点
    head = new LR1NODE{};
    // 创建一个队列用于存储状态集合
    std::queue<std::unordered_set<LR1Item>> stateQueue;
    // 将起始项目的闭包集合推入队列
    stateQueue.push(closure(startItems));

    // 创建一个哈希表用于存储状态集合与节点的映射关系
    std::unordered_map<std::unordered_set<LR1Item>, LR1NODE*> stateMap;
    // 将起始状态的闭包集合映射到头节点
    stateMap[stateQueue.front()] = head;

    // 初始化状态编号
    int stateNum = 0;

    // 当队列不为空时循环处理
    while (!stateQueue.empty()) {
        // 从队列中取出当前状态集合
        auto currentState = stateQueue.front();
        stateQueue.pop();

        // 从状态映射表中找到当前状态集合对应的节点
        LR1NODE* currentNode = stateMap[currentState];
        // 设置当前节点的状态编号
        currentNode->stateNum = stateNum++;
        // 设置当前节点的项目集合
        currentNode->items = currentState;
        // 将当前节点添加到 indexmap 中
        indexmap.push_back(currentNode);
        // 创建一个哈希表用于存储符号转换关系
        std::unordered_map<std::string, std::unordered_set<LR1Item>> symbolTransitions;
        // 遍历当前状态集合中的每个项目
        for (const auto& item : currentState) {
            // 如果当前项目的点位置小于右侧符号集合的大小
            if (item.dotPos < item.rhs.size()) {
                // 将当前项目添加到对应符号的转换集合中
                symbolTransitions[item.rhs[item.dotPos]].insert(item);
            }
        }

        // 遍历符号转换关系
        for (const auto& transition : symbolTransitions) {
            // 获取符号
            auto symbol = transition.first;
            // 获取新状态集合
            auto newState = gotoState(currentState, symbol);

            // 如果新状态集合在状态映射表中不存在
            if (stateMap.find(newState) == stateMap.end()) {
                // 创建新节点
                LR1NODE* newNode = new LR1NODE{};
                // 将新状态集合映射到新节点
                stateMap[newState] = newNode;
                // 将新状态集合推入队列
                stateQueue.push(newState);
            }
            // 设置当前节点的符号转换关系
            currentNode->state[symbol] = stateMap[newState];
        }
    }
}
// 合并同心项目集生成LALR(1)自动机
void LALR::createLALRAutomaton() {
    // 初始化开始项集，包含文法G的第一个产生式
    std::unordered_set<LR1Item> startItems;
    startItems.insert({ G.ex_G[0].left, {G.ex_G[0].right[0]}, 0, "$" });

    // 创建LALR自动机的根节点
    LALRhead = new LR1NODE{};
    
    // 队列，用于处理状态集合
    std::queue<std::unordered_set<LR1Item>> stateQueue;
    stateQueue.push(closure(startItems)); // 将闭包的起始项集入队列

    // 状态映射表，将状态集合映射到对应的LR1节点
    std::unordered_map<std::unordered_set<LR1Item>, LR1NODE*> stateMap;
    // 核心映射表，映射到不同状态的核心
    std::unordered_map<std::string, LR1NODE*> coreMap;

    // 获取初始核心并将其添加到核心映射表
    auto initialCore = countcore(stateQueue.front());
    coreMap[initialCore] = LALRhead;
    stateMap[stateQueue.front()] = LALRhead;

    // 状态编号，从1开始
    int stateNum = 1;

    // 开始循环，直到状态队列为空
    while (!stateQueue.empty()) {
        // 从队列中取出当前状态
        auto currentState = stateQueue.front();
        stateQueue.pop();
        LR1NODE* currentNode = stateMap[currentState];
        currentNode->stateNum = stateNum++; // 设置状态编号
        currentNode->items = currentState;  // 设置该状态的项目集

        // 创建一个映射，用于记录符号到状态的转移
        std::unordered_map<std::string, std::unordered_set<LR1Item>> symbolTransitions;
        
        // 遍历当前状态集中的所有项目
        for (const auto& item : currentState) {
            // 如果点不在产生式的末尾，继续对下一个符号进行转移
            if (item.dotPos < item.rhs.size()) {
                symbolTransitions[item.rhs[item.dotPos]].insert(item);
            }
        }

        // 遍历符号转移，处理每个符号的转移
        for (const auto& transition : symbolTransitions) {
            auto symbol = transition.first; // 当前转移符号
            // 根据符号计算新的状态
            auto newState = gotoState(currentState, symbol);
            newState = closure(newState); // 计算闭包

            // 如果新的状态非空
            if (!newState.empty()) {
                auto newCore = countcore(newState); // 获取新的核心

                // 如果核心不存在，则创建新的节点并将其加入队列
                if (coreMap.find(newCore) == coreMap.end()) {
                    LR1NODE* newNode = new LR1NODE{};
                    stateMap[newState] = newNode;
                    coreMap[newCore] = newNode;
                    stateQueue.push(newState); // 将新状态入队
                    currentNode->state[symbol] = newNode; // 设置当前状态到新节点的转移

                    newNode->stateNum = stateNum++; // 新状态编号
                    std::cout << "Created new state: " << newNode->stateNum << " with core: " << newCore << std::endl;
                } else {
                    // 如果该核心已经存在，则合并状态
                    auto existingNode = coreMap[newCore];
                    for (const auto& item : newState) {
                        if (!item.lookahead.empty() || !item.lhs.empty() || !item.rhs.empty()) { // 确保lookahead不为空
                            existingNode->items.insert(item);
                        }
                    }
                    currentNode->state[symbol] = existingNode; // 更新转移到已有节点

                    std::cout << "Merged with existing state: " << existingNode->stateNum << " for core: " << newCore << std::endl;
                }
            } else {
                // 如果新状态为空，则跳过
                std::cout << "Skipped empty new state for symbol: " << symbol << std::endl;
            }
        }
    }
}

void LALR::generateParsingTable() {
    // 初始化 action 表和 goto 表
    int numStates = indexmap.size();
    for (int i = 0; i < numStates; i++) {
        for (const auto& symbol : G.endSet) {
            actionTable[indexmap[i]->stateNum][symbol] = ""; // 使用原始状态编号
        }
        actionTable[indexmap[i]->stateNum]["$"] = ""; // 结束符初始化

        for (const auto& symbol : G.unendSet) {
            gotoTable[indexmap[i]->stateNum][symbol] = -1; // 默认值
        }
    }

    // 填充 action 表
    for (int i = 0; i < numStates; i++) {
        for (const auto& item : indexmap[i]->items) {
            if (item.dotPos == item.rhs.size()) {
                // 完成规约的项目
                if (item.lhs == G.first) {
                    actionTable[indexmap[i]->stateNum][item.lookahead] = "accept";
                } else {
                    int prodIndex = G.itemMap[item.lhs + item.rhs2str()];
                    actionTable[indexmap[i]->stateNum][item.lookahead] = "r" + std::to_string(prodIndex);
                }
            } else {
                // 移进操作
                std::string symbol = item.rhs[item.dotPos];
                if (symbol == "@") { // 处理空串的逻辑
                    for (const auto& lookahead : G.followMap[item.lhs]) {
                        if (actionTable[indexmap[i]->stateNum][lookahead].empty()) { // 仅在未设置的情况下填充
                            actionTable[indexmap[i]->stateNum][lookahead] = "r" + std::to_string(G.itemMap[item.lhs + item.rhs2str()]);
                        }
                    }
                }
                else if (G.unendSet.find(symbol) == G.unendSet.end()) {
                    auto nextNode = indexmap[i]->state.find(symbol);
                    if (nextNode != indexmap[i]->state.end()) {
                        actionTable[indexmap[i]->stateNum][symbol] = "s" + std::to_string(nextNode->second->stateNum); // 使用原始状态的编号
                    }
                }
            }
        }

        // 填充 goto 表
        for (const auto& j : indexmap[i]->state) {
            const auto& symbol = j.first;
            const auto& nextNode = j.second;
            if (G.unendSet.find(symbol) != G.unendSet.end()) {
                gotoTable[indexmap[i]->stateNum][symbol] = nextNode->stateNum; // 使用原始状态的编号
            }
        }
    }
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

//规约时生成语法树——需要:tokentype tokenstring；
//每个单词都要以string+type的形式存在
//做移进或规约时候输出操作数据——需要 tokentype tokenstring
//需要编写处理函数，把源代码处理成上述结构
string LALR::Analysis(string filepath)
{
    stringstream resultss; // 使用 stringstream 记录结果日志
    ifstream infile(filepath);
    vector<pair<string, string>> tokens;

    // 词法分析
    if (infile.is_open()) {
        string sentence;
        while (getline(infile, sentence)) {
            stringstream ss(sentence);
            string left, assign, right;
            ss >> left;
            if (left == "comments") {
                continue; // 跳过注释行
            }
            ss >> assign >> right;
            tokens.emplace_back(make_pair(left, right));
        }
    }
    else {
        return "无法打开文件。";
    }

    // 初始化解析变量
    tokens.emplace_back(make_pair("$", "END_C")); // 添加结束符
    stack<AI> anaStk; // 状态栈
    AI firstItem;
    firstItem.state = 0; // 初始状态
    anaStk.push(firstItem);

    // 语法树根节点
    stack<shared_ptr<SyntaxTreeNode>> treeStack; // 用于存储树节点的栈

    // 解析过程
    int i = 0; // 词法单元索引
    while (!anaStk.empty()) {
        AI top = anaStk.top();
        string currentToken = tokens[i].first;
        string currentString = tokens[i].second;
        string act = actionTable[top.state][currentToken];
        cout << currentToken << "->" << currentString << endl;

        // 检查是否存在操作
        if (act.empty()) {
            resultss << "错误：在状态 " << top.state << " 下没有处理符号 " << currentToken << " 的操作。\n";
            break;
        }

        // 移进操作
        if (act[0] == 's') {
            int nextState = stoi(act.substr(1));
            resultss << "移进：将 " << currentString << " (" << currentToken << ") 移入状态 " << nextState << "\n";

            // 创建语法树节点
            auto newNode = make_shared<SyntaxTreeNode>(currentToken);
            newNode->tokenString = currentString; // 当前 token 字符串
            treeStack.push(newNode);

            // 将新状态压入栈中
            AI newItem;
            newItem.state = nextState;
            newItem.token = make_pair(currentString, currentToken);
            anaStk.push(newItem);
            i++; // 移动到下一个词法单元
        }
        // 规约操作
        else if (act[0] == 'r') {
            int prodIndex = stoi(act.substr(1)); // 获取产生式索引
            if (prodIndex < 0 || prodIndex >= G.ex_G.size()) {
                resultss << "错误：产生式索引 " << prodIndex << " 超出范围。\n";
                break;
            }
            auto production = G.ex_G[prodIndex]; // G.ex_G 存储产生式

            // 判断是否是空产生式
            bool isEmptyProduction = (production.right.size() == 1 && production.right[0] == "@");

            // 打印规约信息
            resultss << "规约：通过产生式 " << production.left << " -> ";
            if (isEmptyProduction) {
                resultss << "@\n";
            }
            else {
                for (const auto& symbol : production.right) {
                    resultss << symbol << " ";
                }
                resultss << "\n";
            }

            // 创建语法树节点
            auto newNode = make_shared<SyntaxTreeNode>(production.left);
            newNode->tokenString = production.left; // 当前产生式左部

            if (!isEmptyProduction) {
                // 规约非空产生式，弹出相应数量的节点并作为子节点
                for (const auto& symbol : production.right) {
                    if (!treeStack.empty()) {
                        if (treeStack.top()->tokenString != "Lparen" &&
                            treeStack.top()->tokenString != "Rparen" &&
                            treeStack.top()->tokenString != "branch" &&
                            treeStack.top()->tokenString != "Lbrace" &&
                            treeStack.top()->tokenString != "Rbrace" &&
                            treeStack.top()->tokenString != "comon")
                        {
                            newNode->children.push_back(treeStack.top());
                        }
                        treeStack.pop();
                    }
                }
            }
            else {
                // 规约空产生式，可以选择添加一个特殊的子节点，或不添加任何子节点
                // 例如，添加一个表示空的节点：
                // auto emptyNode = make_shared<SyntaxTreeNode>("@");
                // newNode->children.push_back(emptyNode);
                // 或者直接不添加子节点
            }

            // 将新节点压入语法树栈中
            treeStack.push(newNode);

            if (!isEmptyProduction) {
                // 根据产生式的长度弹出状态栈
                for (size_t j = 0; j < production.right.size(); j++) {
                    if (!anaStk.empty()) {
                        anaStk.pop();
                    }
                    else {
                        resultss << "错误：状态栈为空，无法弹出。\n";
                        break;
                    }
                }
            }
            // 对于空产生式，不弹出任何状态

            if (anaStk.empty()) {
                resultss << "错误：状态栈为空，无法获取 GOTO。\n";
                break;
            }

            // 使用 GOTO 表确定下一个状态
            AI newTop = anaStk.top();
            if (gotoTable.find(newTop.state) == gotoTable.end() ||
                gotoTable[newTop.state].find(production.left) == gotoTable[newTop.state].end()) {
                resultss << "错误：在状态 " << newTop.state << " 下没有找到非终结符 " << production.left << " 的 GOTO。\n";
                break;
            }

            int nextState = gotoTable[newTop.state][production.left];
            resultss << "goto: 转移到状态 " << nextState << "\n";

            if (nextState == -1) {
                resultss << "错误：在状态 " << newTop.state << " 下没有找到非终结符 " << production.left << " 的 GOTO。\n";
                break;
            }

            // 将新状态压入栈中
            AI newItem;
            newItem.token = make_pair(production.left, "UNEND");
            newItem.state = nextState;
            anaStk.push(newItem);
        }
        // 接受操作
        else if (act == "accept") {
            resultss << "接受输入\n";
            if (!treeStack.empty()) {
                syntaxTreeRoot = treeStack.top(); // 获取语法树根节点
                treeStack.pop();
            }
            break;
        }
    }

    // 生成语法树的打印逻辑（可选）
    if (syntaxTreeRoot) {
        resultss << "生成的语法树：\n";
        printSyntaxTree(syntaxTreeRoot, resultss, 0); // 递归打印语法树
    }

    // 返回分析结果
    return resultss.str();
}

// 打印语法树的辅助函数
void LALR::printSyntaxTree(const std::shared_ptr<SyntaxTreeNode>& node, std::stringstream& ss, int depth) {
    for (int i = 0; i < depth; ++i) ss << "  "; // 缩进
    ss << node->tokenString << "\n";
    for (const auto& child : node->children) {
        printSyntaxTree(child, ss, depth + 1); // 递归打印子节点
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

    // 创建表头
    QStringList headers;
    headers << "State";
    for (const auto& symbol : symbols) {
        headers << QString::fromStdString(symbol);
    }
    tableWidget->setColumnCount(headers.size());
    tableWidget->setHorizontalHeaderLabels(headers);

    // 填充表格
    for (const auto& stateActions : lalr.actionTable) {
        int state = stateActions.first;
        int currentRow = tableWidget->rowCount();
        tableWidget->insertRow(currentRow);
        tableWidget->setItem(currentRow, 0, new QTableWidgetItem(QString::number(state)));

        for (const auto& symbol : symbols) {
            QString cellContent;

            // 获取当前状态的动作
            auto actionIt = stateActions.second.find(symbol);
            if (actionIt != stateActions.second.end()) {
                cellContent = QString::fromStdString(actionIt->second);
            }

            // 获取当前状态的转移
            auto gotoIt = lalr.gotoTable.find(state);
            if (gotoIt != lalr.gotoTable.end()) {
                auto goIt = gotoIt->second.find(symbol);
                if (goIt != gotoIt->second.end()) {
                    if (!cellContent.isEmpty()) {
                        cellContent += ", ";
                    }
                    cellContent += "goto " + QString::number(goIt->second);
                }
            }

            // 设置单元格内容
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
void populateTreeView(const std::shared_ptr<SyntaxTreeNode> &node, QStandardItem *parentItem)
{
    if (!node) return;

    // 创建当前节点的 QStandardItem
    QStandardItem* currentItem = new QStandardItem(QString::fromStdString(node->tokenString));
    parentItem->appendRow(currentItem);

    // 递归处理子节点
    for (const auto& child : node->children) {
        populateTreeView(child, currentItem);
    }
}
void LALR::printTreeView(QTreeView* treeView) {
    QStandardItemModel* model = new QStandardItemModel(treeView);
    model->setHorizontalHeaderLabels(QStringList() << "Syntax Tree");

    if (syntaxTreeRoot) {
        populateTreeView(syntaxTreeRoot, model->invisibleRootItem());
    }

    treeView->setModel(model);
    treeView->expandAll(); // 展开所有项
}

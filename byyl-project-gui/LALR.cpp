#include "LALR.h"

std::string LALR::countcore(std::unordered_set<LR1Item> itemset)
{

    // 收集当前节点的核心项目集
    std::unordered_set <std::string> coreset;
    for (const auto& item : itemset) {
        std::string str = item.lhs;
        for (auto j : item.rhs)
        {
            str += j;
        }
        str += item.dotPos;
        coreset.insert(str);
    }
    std::string result;
    for (auto i : coreset)
    {
        result += i;
    }
    // std::cout << result;
    return result;
}

// 闭包函数，用于计算LR1项目集的闭包。
std::unordered_set<LR1Item> LALR::closure(const std::unordered_set<LR1Item>& items) {
    std::unordered_set<LR1Item> closureSet = items;
    bool added;

    do {
        added = false;
        for (const auto& item : closureSet) {
            if (item.dotPos < item.rhs.size()) {
                std::string symbol = item.rhs[item.dotPos];
                if (G.unendSet.find(symbol) != G.unendSet.end()) {
                    for (const auto& prod : G.ex_G) {
                        if (prod.left == symbol) {
                            std::unordered_set<std::string> lookaheads;
                            // Calculate lookaheads correctly
                            if (item.dotPos + 1 < item.rhs.size()) {
                                bool isNull = true;
                                for (int next = item.dotPos + 1; next < item.rhs.size(); ++next) {
                                    std::string nextSymbol = item.rhs[next];
                                    if (G.unendSet.find(nextSymbol) == G.unendSet.end()) {
                                        lookaheads.insert(nextSymbol);
                                        isNull = false;
                                        break;
                                    } else if (G.nullMap[nextSymbol]) {
                                        lookaheads.insert(G.firstMap[nextSymbol].begin(), G.firstMap[nextSymbol].end());
                                        lookaheads.erase("@");
                                    } else {
                                        lookaheads.insert(G.firstMap[nextSymbol].begin(), G.firstMap[nextSymbol].end());
                                        isNull = false;
                                        break;
                                    }
                                }
                                if (isNull) {
                                    lookaheads.insert(G.followMap[item.lhs].begin(), G.followMap[item.lhs].end());
                                }
                            } else {
                                lookaheads.insert(item.lookahead);
                            }

                            for (const auto& lookahead : lookaheads) {
                                LR1Item newItem{symbol, prod.right, 0, lookahead};
                                if (closureSet.insert(newItem).second) {
                                    added = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    } while (added);
    return closureSet;
}

std::unordered_set<LR1Item> LALR::gotoState(const std::unordered_set<LR1Item>& items, const std::string& symbol) {
    std::unordered_set<LR1Item> gotoSet;
    for (const auto& item : items) {
        if (item.dotPos < item.rhs.size() && item.rhs[item.dotPos] == symbol) {
            gotoSet.insert({ item.lhs, item.rhs, item.dotPos + 1, item.lookahead });
        }
    }
    return closure(gotoSet);
}

void LALR::createLR1Automaton() {
    std::unordered_set<LR1Item> startItems;
    startItems.insert({ G.ex_G[0].left, { G.ex_G[0].right[0] }, 0, "$" });

    head = new LR1NODE{};
    std::queue<std::unordered_set<LR1Item>> stateQueue;
    stateQueue.push(closure(startItems));

    std::unordered_map<std::unordered_set<LR1Item>, LR1NODE*> stateMap;
    stateMap[stateQueue.front()] = head;

    int stateNum = 0;

    while (!stateQueue.empty()) {
        auto currentState = stateQueue.front();
        stateQueue.pop();

        LR1NODE* currentNode = stateMap[currentState];
        currentNode->stateNum = stateNum++;
        currentNode->items = currentState;

        // 将当前状态映射到 indexmap
        indexmap.push_back(currentNode);

        std::unordered_map<std::string, std::unordered_set<LR1Item>> symbolTransitions;
        for (const auto& item : currentState) {
            if (item.dotPos < item.rhs.size()) {
                symbolTransitions[item.rhs[item.dotPos]].insert(item);
            }
        }

        for (const auto& transition : symbolTransitions) {
            auto symbol = transition.first;
            auto newState = gotoState(currentState, symbol);

            if (stateMap.find(newState) == stateMap.end()) {
                LR1NODE* newNode = new LR1NODE{};
                stateMap[newState] = newNode;
                stateQueue.push(newState);
            }
            currentNode->state[symbol] = stateMap[newState];
        }
    }
}

// 合并同心项目集生成LALR(1)自动机
void LALR::createLALRAutomaton() {
    std::unordered_set<LR1Item> startItems;
    startItems.insert({ G.ex_G[0].left, {G.ex_G[0].right[0]}, 0, "$" });
    LALRhead = new LR1NODE{};
    std::queue<std::unordered_set<LR1Item>> stateQueue;
    stateQueue.push(closure(startItems));

    std::unordered_map<std::unordered_set<LR1Item>, LR1NODE*> stateMap;
    std::unordered_map<std::string, LR1NODE*> coreMap;

    auto initialCore = countcore(stateQueue.front());
    coreMap[initialCore] = LALRhead;
    stateMap[stateQueue.front()] = LALRhead;
    int stateNum = 1;

    while (!stateQueue.empty()) {
        auto currentState = stateQueue.front();
        stateQueue.pop();
        LR1NODE* currentNode = stateMap[currentState];
        currentNode->stateNum = stateNum++;
        currentNode->items = currentState;
        // indexmap.push_back(currentNode);

        std::unordered_map<std::string, std::unordered_set<LR1Item>> symbolTransitions;
        for (const auto& item : currentState) {
            if (item.dotPos < item.rhs.size()) {
                symbolTransitions[item.rhs[item.dotPos]].insert(item);
            }
        }

        for (const auto& transition : symbolTransitions) {
            auto symbol = transition.first;
            auto newState = gotoState(currentState, symbol);
            newState = closure(newState);

            if (!newState.empty()) {
                auto newCore = countcore(newState);

                if (coreMap.find(newCore) == coreMap.end()) {
                    LR1NODE* newNode = new LR1NODE{};
                    stateMap[newState] = newNode;
                    coreMap[newCore] = newNode;
                    stateQueue.push(newState);
                    currentNode->state[symbol] = newNode;

                    newNode->stateNum = stateNum++;
                    std::cout << "Created new state: " << newNode->stateNum << " with core: " << newCore << std::endl;
                } else {
                    auto existingNode = coreMap[newCore];
                    for (const auto& item : newState) {
                        if (!item.lookahead.empty()||!item.lhs.empty()||!item.rhs.empty()) { // 确保lookahead不为空
                            existingNode->items.insert(item);
                        }
                    }
                    currentNode->state[symbol] = existingNode;

                    std::cout << "Merged with existing state: " << existingNode->stateNum << " for core: " << newCore << std::endl;
                }
            } else {
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

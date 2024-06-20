#include "LALR.h"


std::string LALR::countcore(std::unordered_set<LR1Item> itemset)
{

    // �ռ���ǰ�ڵ�ĺ�����Ŀ��
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

// �հ����������ڼ���LR1��Ŀ���ıհ���
std::unordered_set<LR1Item> LALR::closure(const std::unordered_set<LR1Item>& items) {
    std::unordered_set<LR1Item> closureSet = items; // ��ʼ���հ���Ϊ�������Ŀ��
    bool added; // ����Ƿ��ڵ��������������Ŀ
    do {
        added = false; // ÿ��ѭ����ʼʱ���ٶ�û���������Ŀ
        for (const auto& item : closureSet) {
            if (item.dotPos < item.rhs.size()) { // ��δ�������ʽ�Ҳ��ĩβ
                std::string symbol = item.rhs[item.dotPos]; // ��ǰ����ķ���
                if (G.unendSet.find(symbol) != G.unendSet.end()) { // ������ս��������հ�
                    // ����ÿ����symbolΪ�����ŵĲ���ʽ�������µ�LR1��Ŀ
                    for (const auto& prod : G.ex_G) {
                        if (prod.left == symbol) {
                            std::unordered_set<std::string> lookaheads; // ��ʼ��lookahead����
                            // ����lookahead����
                            if (item.dotPos + 1 < item.rhs.size()) {
                                // �������滹�з��ţ�����FIRST����
                                std::string nextSymbol;
                                bool isnull = true;
                                for (int next = item.dotPos + 1; next < item.rhs.size(); next++) {
                                    nextSymbol = item.rhs[next];
                                    if (G.unendSet.find(nextSymbol) == G.unendSet.end()) {
                                        // ������ս��������lookahead����
                                        lookaheads.insert(nextSymbol);
                                        isnull = false;
                                        break;
                                    }
                                    else if (G.nullMap[nextSymbol]) {
                                        // ����Ƿ��ս���ҿ�Ϊ�գ�����FIRST����
                                        lookaheads.insert(G.firstMap[nextSymbol].begin(), G.firstMap[nextSymbol].end());
                                        lookaheads.erase("@"); // �Ƴ��������
                                    }
                                    else {
                                        // ����Ƿ��ս���Ҳ���Ϊ�գ�����FIRST����
                                        lookaheads.insert(G.firstMap[nextSymbol].begin(), G.firstMap[nextSymbol].end());
                                        isnull = false;
                                        break;
                                    }
                                }
                                if (isnull) { // ���������з��Ŷ���Ϊ�գ�����FOLLOW����
                                    lookaheads.insert(G.followMap[symbol].begin(), G.followMap[symbol].end());
                                }
                            }
                            else {
                                // ��������û�з��ţ�ʹ�õ�ǰlookahead
                                lookaheads.insert(item.lookahead);
                            }
                            // �������ɵ�LR1��Ŀ����հ���
                            for (const auto& lookahead : lookaheads) {
                                LR1Item newItem{ symbol, prod.right, 0, lookahead };
                                if (closureSet.insert(newItem).second) {
                                    added = true; // �������Ŀ����ӣ����Ϊtrue
                                }
                            }
                        }
                    }
                }
            }
        }
    } while (added); // ������������Ŀ�����������
    return closureSet; // ���رհ���
}

// ת�ƺ��������ڼ����ڸ��������´�ĳ����Ŀ��ת�Ƶõ��µ���Ŀ����
std::unordered_set<LR1Item> LALR::gotoState(const std::unordered_set<LR1Item>& items, const std::string& symbol) {
    std::unordered_set<LR1Item> gotoSet;
    for (const auto& item : items) {
        if (item.dotPos < item.rhs.size() && item.rhs[item.dotPos] == symbol) {
            // �����µ�LR1��Ŀ���������ƶ�һλ
            gotoSet.insert({ item.lhs, item.rhs, item.dotPos + 1, item.lookahead });
        }
    }
    // �Եõ���goto�����бհ�����
    return closure(gotoSet);
}

// ����LR1�Զ���
void LALR::createLR1Automaton() {
    // ��ʼ��Ŀ����������ʼ���ŵ���ʼ��Ŀ
    std::unordered_set<LR1Item> startItems;

    startItems.insert({ G.ex_G[0].left, {G.ex_G[0].right[0]}, 0, "$" });
    head = new LR1NODE{}; // ������ʼ�ڵ�
    std::queue<std::unordered_set<LR1Item>> stateQueue; // ���ڴ洢�������״̬����
    stateQueue.push(closure(startItems)); // ����ʼ�հ������

    std::unordered_map<std::unordered_set<LR1Item>, LR1NODE*> stateMap; // ӳ�����Ŀ�����ڵ�
    stateMap[stateQueue.front()] = head; // ����ʼ�հ���ӳ�䵽��ʼ�ڵ�
    int stateNum = 0; // ״̬���

    while (!stateQueue.empty()) {
        std::unordered_set<LR1Item> currentState = stateQueue.front(); // ��ȡ��ǰ״̬
        stateQueue.pop(); // ����

        LR1NODE* currentNode = stateMap[currentState]; // ��ȡ��ǰ�ڵ�

        currentNode->stateNum = stateNum++; // ����״̬��Ų�����
        currentNode->items = currentState; // ���ýڵ����Ŀ��

        // ����ÿ�����ŵ�ת��
        std::unordered_map<std::string, std::unordered_set<LR1Item>> symbolTransitions;
        for (const auto& item : currentState) {
            if (item.dotPos < item.rhs.size()) {
                symbolTransitions[item.rhs[item.dotPos]].insert(item); // �Է���Ϊ�����洢��Ŀ
            }
        }
        // Ϊÿ�����ŵ�ת�ƴ����µĽڵ�����ӳ���
        for (const auto& transition : symbolTransitions) {
            auto symbol = transition.first;
            auto newState = gotoState(currentState, symbol); // ����ת�ƺ��״̬
            
            if (stateMap.find(newState) == stateMap.end()) {
                // �����״̬����ӳ����У������½ڵ㲢����ӳ���
                LR1NODE* newNode = new LR1NODE{};
                stateMap[newState] = newNode;
                stateQueue.push(newState); // ����״̬���
            }
            // ���µ�ǰ�ڵ��ת�Ʊ�
            currentNode->state[symbol] = stateMap[newState];
        }
    }
}

// �ϲ�ͬ����Ŀ������LALR(1)�Զ���
void LALR::createLALRAutomaton() {
    //// �ϲ�������ͬ�ں˵�״̬
    //std::unordered_map<std::set<std::pair<std::string, std::vector<std::string>>>, std::unordered_set<LR1NODE*>> coreToStatesMap;
    //std::queue<LR1NODE*> stateQueue;
    //std::unordered_set<LR1NODE*> visitedStates; // ��¼�ѷ��ʵ�״̬
    //stateQueue.push(head); // ����ʼ�ڵ����
    //visitedStates.insert(head); // ��ǳ�ʼ�ڵ�Ϊ�ѷ���
    //while (!stateQueue.empty()) {
    //    LR1NODE* currentNode = stateQueue.front();
    //    stateQueue.pop();

    //    std::set<std::pair<std::string, std::vector<std::string>>> core;
    //    // �ռ���ǰ״̬�ĺ�����Ŀ��
    //    for (const auto& item : currentNode->items) {
    //        core.insert({ item.lhs, item.rhs });
    //    }

    //    // ����ǰ�ڵ�ӳ�䵽�����
    //    coreToStatesMap[core].insert(currentNode);

    //    // ������ǰ�ڵ������ת��
    //    for (const auto& transition : currentNode->state) {
    //        if (visitedStates.find(transition.second) == visitedStates.end()) {
    //            stateQueue.push(transition.second); // ���ת�Ƶ�Ŀ��״̬δ�����ʹ������
    //            visitedStates.insert(transition.second); // ���Ϊ�ѷ���
    //        }
    //    }
    //}
    //// �ϲ�״̬
    //for (auto& entry : coreToStatesMap) {
    //    auto& states = entry.second;
    //    if (states.size() > 1) {
    //        // ���һ������ӳ�䵽���״̬�����кϲ�
    //        auto it = states.begin();
    //        LR1NODE* firstState = *it;
    //        ++it;
    //        for (; it != states.end(); ++it) {
    //            LR1NODE* state = *it;
    //            // ������״̬����Ŀ����ת�ƺϲ�����һ��״̬
    //            firstState->items.insert(state->items.begin(), state->items.end());
    //            for (auto& transition : state->state) {
    //                firstState->state[transition.first] = transition.second;
    //            }
    //            delete state; // ɾ�����ϲ���״̬�ڵ�
    //        }
    //    }
    //}
        // ��ʼ��Ŀ����������ʼ���ŵ���ʼ��Ŀ
    
    std::unordered_set<LR1Item> startItems;
    startItems.insert({ G.ex_G[0].left, {G.ex_G[0].right[0]}, 0, "$" });
    LALRhead = new LR1NODE{}; // ������ʼ�ڵ�
    std::queue<std::unordered_set<LR1Item>> stateQueue; // ���ڴ洢�������״̬����
    stateQueue.push(closure(startItems)); // ����ʼ�հ������

    std::unordered_map<std::unordered_set<LR1Item>, LR1NODE*> stateMap; // ӳ�����Ŀ�����ڵ�
    std::unordered_map<std::string, LR1NODE*> coreMap;

    coreMap[countcore(stateQueue.front())] = LALRhead;
    stateMap[stateQueue.front()] = LALRhead; // ����ʼ�հ���ӳ�䵽��ʼ�ڵ�
    int stateNum = 0; // ״̬���

    while (!stateQueue.empty()) {
        std::unordered_set<LR1Item> currentState = stateQueue.front(); // ��ȡ��ǰ״̬
        stateQueue.pop(); // ����
        LR1NODE* currentNode = stateMap[currentState]; // ��ȡ��ǰ�ڵ�
        currentNode->stateNum = stateNum++; // ����״̬��Ų�����
        currentNode->items = currentState; // ���ýڵ����Ŀ��
        indexmap.push_back(currentNode);
        // �ռ���ǰ״̬�ĺ�����Ŀ��
        currentNode->core = countcore(currentState);
        // ����ÿ�����ŵ�ת��
        std::unordered_map<std::string, std::unordered_set<LR1Item>> symbolTransitions;
        for (const auto& item : currentState) {
            if (item.dotPos < item.rhs.size()) {
                symbolTransitions[item.rhs[item.dotPos]].insert(item); // �Է���Ϊ�����洢��Ŀ
            }
        }

        // Ϊÿ�����ŵ�ת�ƴ����µĽڵ�����ӳ���
        for (const auto& transition : symbolTransitions) {
            auto symbol = transition.first;
            auto newState = gotoState(currentState, symbol); // ����ת�ƺ��״̬
            auto newcore = countcore(newState);
            if (coreMap.find(newcore) == coreMap.end()) {
                // �����״̬����ӳ����У������½ڵ㲢����ӳ���
                LR1NODE* newNode = new LR1NODE{};
                stateMap[newState] = newNode;
                coreMap[newcore] = newNode;

                stateQueue.push(newState); // ����״̬���
                // ���µ�ǰ�ڵ��ת�Ʊ�
                currentNode->state[symbol] = stateMap[newState];
            }
            else
            {
                //�ϲ�չ������
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

    tableWidget->clear(); // �����������
    tableWidget->setRowCount(0); // ��������
    tableWidget->setColumnCount(3); // ����������������Ҫ����������

    QStringList headers;
    headers << "State" << "Item" << "Lookahead";
    tableWidget->setHorizontalHeaderLabels(headers);

    // ʹ��BFS�����Զ��������нڵ�
    std::unordered_set<LR1NODE*> visited;
    std::queue<LR1NODE*> stateQueue;
    stateQueue.push(start);
    visited.insert(start);

    while (!stateQueue.empty()) {
        LR1NODE* currentNode = stateQueue.front();
        stateQueue.pop();

        // ��ӡ��ǰ״̬���
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

    // �Զ������п��
    tableWidget->resizeColumnsToContents();
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->verticalHeader()->setVisible(false);
}

void printParsingTable(const LALR& lalr, QTableWidget* tableWidget) {
    tableWidget->clear();
    tableWidget->setRowCount(0);
    // �ҳ����еķ���
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

    // �Զ������п��
    tableWidget->resizeColumnsToContents();
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->verticalHeader()->setVisible(false);
}
// LALR���캯��������һ���ļ�·����Ϊ����
LALR::LALR(const std::string filepath) : G(filepath), head(nullptr) {
    // ����LR1�Զ���
    createLR1Automaton();
    // ��ӡLR1�Զ�����״̬
    std::cout << "LR1 AUTOMATION\n";
    // ����LALR(1)�Զ���
    std::cout << "LALR1 AUTOMATION\n";
    createLALRAutomaton();
    // ��ӡLALR(1)�Զ�����״̬
    generateParsingTable();
    // ��ӡ�Զ���������ɵ���Ϣ
    std::cout << "create finish" << std::endl;
}

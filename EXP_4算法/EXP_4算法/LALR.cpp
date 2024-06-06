#include "LALR.h"


// �հ�����

std::unordered_set<LR1Item> LALR::closure(const std::unordered_set<LR1Item>& items) {
    std::unordered_set<LR1Item> closureSet = items;
    bool added;
    do {
        added = false;
        for (const auto& item : closureSet) {
            if (item.dotPos < item.rhs.size()) {//��δ�����βʱ
                std::string symbol = item.rhs[item.dotPos];
                if (G.unendSet.find(symbol) != G.unendSet.end()) { // ���ս���ż���հ�
                    for (const auto& prod : G.ex_G) {
                        if (prod.left == symbol) {//�ҵ���Ӧ���ķ�
                            std::unordered_set<std::string> lookaheads;
                            // �����֮���з���
                            if (item.dotPos + 1 < item.rhs.size()) {
                                std::string nextSymbol;
                                // �����һ�������Ƿ��ս������������select��
                                bool isnull = 1;
                                for (int next = item.dotPos + 1; next < item.rhs.size(); next++)
                                {
                                    nextSymbol = item.rhs[next];
                                    if (G.unendSet.find(nextSymbol) == G.unendSet.end())//������ս����ֱ�Ӽ���,����ѭ��
                                    {
                                        lookaheads.insert(nextSymbol);
                                        isnull = 0;
                                        break;
                                    }
                                    else if (G.nullMap[nextSymbol])//������ս����Ϊ�գ�����ɨ����һ��;
                                    {
                                        lookaheads.insert(G.firstMap[nextSymbol].begin(), G.firstMap[nextSymbol].end());
                                        lookaheads.erase("@");
                                    }
                                    else//������ս������Ϊ�գ�ֱ�Ӽ���first���ϣ�
                                    {
                                        lookaheads.insert(G.firstMap[nextSymbol].begin(), G.firstMap[nextSymbol].end());
                                        break;
                                        isnull = 0;
                                    }
                                        
                                }
                                if (isnull)//��������ķ��ս��ȫ����Ϊ�գ�������ŵ�follow����;
                                {
                                    lookaheads.insert(G.followMap[symbol].begin(), G.followMap[symbol].end());
                                }
                            }
                            else {
                                // �����֮��û�з��ţ����ֵ�ǰ��lookahead
                                lookaheads.insert(item.lookahead);
                            }
                            for (const auto& lookahead : lookaheads) {
                                LR1Item newItem{ symbol, prod.right, 0, lookahead };
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

// ת�ƺ���
std::unordered_set<LR1Item> LALR::gotoState(const std::unordered_set<LR1Item>& items, const std::string& symbol) {
    std::unordered_set<LR1Item> gotoSet;
    for (const auto& item : items) {
        if (item.dotPos < item.rhs.size() && item.rhs[item.dotPos] == symbol) {
            gotoSet.insert({ item.lhs, item.rhs, item.dotPos + 1, item.lookahead });
        }
    }
    return closure(gotoSet);
}
// ����LR1�Զ���

void LALR::createLR1Automaton() {
    // ��ʼ��Ŀ��
    std::unordered_set<LR1Item> startItems;
    startItems.insert({ G.ex_G[0].left, {G.ex_G[0].right[0]}, 0, "$"});
    head = new LR1NODE{};
    std::queue<std::unordered_set<LR1Item>> stateQueue;
    stateQueue.push(closure(startItems));

    std::unordered_map<std::unordered_set<LR1Item>, LR1NODE*> stateMap;
    stateMap[stateQueue.front()] = head;
    int stateNum = 0;
    while (!stateQueue.empty()) {
        std::unordered_set<LR1Item> currentState = stateQueue.front();
        stateQueue.pop();

        LR1NODE* currentNode = stateMap[currentState];
        currentNode->stateNum = stateNum++;
        currentNode->items = currentState;

        std::unordered_map<std::string, std::unordered_set<LR1Item>> symbolTransitions;
        for (const auto& item : currentState) {
            if (item.dotPos < item.rhs.size()) {
                std::string symbol = item.rhs[item.dotPos];
                symbolTransitions[symbol].insert(item);
            }
        }

        for (const auto& i : symbolTransitions) {
            auto symbol = i.first;
            auto items = i.second;
            std::unordered_set<LR1Item> newState = gotoState(currentState, symbol);
            if (stateMap.find(newState) == stateMap.end()) {
                LR1NODE* newNode = new LR1NODE{};
                stateMap[newState] = newNode;
                stateQueue.push(newState);
            }
            currentNode->state[symbol] = stateMap[newState];
        }
    }
}
LALR::LALR(const std::string filepath) : G(filepath), head(nullptr) {
    createLR1Automaton();
    std::cout << "create finish" << std::endl;
}

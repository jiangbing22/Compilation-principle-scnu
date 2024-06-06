#include "LALR.h"


// 闭包函数

std::unordered_set<LR1Item> LALR::closure(const std::unordered_set<LR1Item>& items) {
    std::unordered_set<LR1Item> closureSet = items;
    bool added;
    do {
        added = false;
        for (const auto& item : closureSet) {
            if (item.dotPos < item.rhs.size()) {//点未到达结尾时
                std::string symbol = item.rhs[item.dotPos];
                if (G.unendSet.find(symbol) != G.unendSet.end()) { // 非终结符才加入闭包
                    for (const auto& prod : G.ex_G) {
                        if (prod.left == symbol) {//找到对应的文法
                            std::unordered_set<std::string> lookaheads;
                            // 如果点之后还有符号
                            if (item.dotPos + 1 < item.rhs.size()) {
                                std::string nextSymbol;
                                // 如果下一个符号是非终结符，加入它的select集
                                bool isnull = 1;
                                for (int next = item.dotPos + 1; next < item.rhs.size(); next++)
                                {
                                    nextSymbol = item.rhs[next];
                                    if (G.unendSet.find(nextSymbol) == G.unendSet.end())//如果是终结符，直接加入,跳出循环
                                    {
                                        lookaheads.insert(nextSymbol);
                                        isnull = 0;
                                        break;
                                    }
                                    else if (G.nullMap[nextSymbol])//如果非终结符可为空，继续扫描下一个;
                                    {
                                        lookaheads.insert(G.firstMap[nextSymbol].begin(), G.firstMap[nextSymbol].end());
                                        lookaheads.erase("@");
                                    }
                                    else//如果非终结符不可为空，直接加入first集合；
                                    {
                                        lookaheads.insert(G.firstMap[nextSymbol].begin(), G.firstMap[nextSymbol].end());
                                        break;
                                        isnull = 0;
                                    }
                                        
                                }
                                if (isnull)//如果后续的非终结符全都可为空，加入符号的follow集合;
                                {
                                    lookaheads.insert(G.followMap[symbol].begin(), G.followMap[symbol].end());
                                }
                            }
                            else {
                                // 如果点之后没有符号，保持当前的lookahead
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

// 转移函数
std::unordered_set<LR1Item> LALR::gotoState(const std::unordered_set<LR1Item>& items, const std::string& symbol) {
    std::unordered_set<LR1Item> gotoSet;
    for (const auto& item : items) {
        if (item.dotPos < item.rhs.size() && item.rhs[item.dotPos] == symbol) {
            gotoSet.insert({ item.lhs, item.rhs, item.dotPos + 1, item.lookahead });
        }
    }
    return closure(gotoSet);
}
// 创建LR1自动机

void LALR::createLR1Automaton() {
    // 初始项目集
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

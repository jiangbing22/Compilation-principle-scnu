#include "grammar.h"
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

// 辅助函数，检查一个符号是否为非终结符
bool isNonTerminal(const std::string& symbol, const std::unordered_set<std::string>& unendSet) {
    return unendSet.find(symbol) != unendSet.end();
}

// 辅助函数，将一个集合的元素添加到另一个集合，并检查是否有新元素添加
bool addToSet(std::unordered_set<std::string>& set1, const std::unordered_set<std::string>& set2) {
    bool changed = false;
    for (const auto& elem : set2) {
        if (set1.insert(elem).second) {
            changed = true;
        }
    }
    return changed;
}
void grammar::createExG()
{
    int grammarnum = 1;//编号
    for (const auto& nonTerminal : unendSet) {
        nullMap[nonTerminal] = false;
    }
    bool flag = 0;
    for (auto i : G)
    {
        auto itr = i.right.begin();
        while (itr != i.right.end())
        {
            //std::cout << *itr;
            auto last = itr;
            itr = std::find(itr, i.right.end(), "|");
            if (!flag)
            {
                flag = 1;
                grammarNode newnode;
                newnode.left = first + "^";
                newnode.right.push_back(first);
                this->ex_G.push_back(newnode);
            }
            grammarNode newnode;
            newnode.left = i.left;
            for (auto j = last; j < itr; j++)
            {
                newnode.right.push_back(*j);
                if (unendSet.find(*j) == unendSet.end())
                {
                    endSet.insert(*j);
                }
                if (*j == "@")
                {
                    nullMap[i.left] = true;
                }
            }
            ex_G.push_back(newnode);
            itemMap[newnode.left + newnode.right2str()] = grammarnum;
            if (itr != i.right.end())
            {
                itr++;
            }
        }
    }
}

void grammar::createFirst() {
    // 初始化firstMap，所有非终结符的FIRST集合为空集
    for (const auto& nonTerminal : unendSet) {
        firstMap[nonTerminal] = std::unordered_set<std::string>();
    }

    bool changed = true;
    while (changed) {
        changed = false;

        for (const auto& rule : ex_G) {
            const std::string& left = rule.left;
            const std::vector<std::string>& right = rule.right;

            bool epsilonFound = true; 
            for (size_t i = 0; i < right.size(); ++i) {
                const std::string& symbol = right[i];

                // 如果符号是终结符，将其添加到FIRST(left)
                if (symbol == "@")
                {
                    break;
                }
                if (!isNonTerminal(symbol, unendSet)) {
                    if (firstMap[left].insert(symbol).second) {
                        changed = true;
                    }
                    epsilonFound = false;  // 终结符不能生成空串
                    break;
                }
                else {
                    // 将FIRST(symbol)添加到FIRST(left)
                    if (addToSet(firstMap[left], firstMap[symbol])) {
                        changed = true;
                    }
                    // 如果FIRST(symbol)不包含ε，则不再继续处理下一个符号
                    if (!nullMap[symbol]) {
                        epsilonFound = false;
                        break;
                    }
                }
            }
                        
            // 如果当前产生式右部所有符号都能生成空串，则first集里有空串
            if (epsilonFound) {
                nullMap[left] = true;
            }
        }
    }
    for (const auto& nonTerminal : unendSet) {        
        if (nullMap[nonTerminal])
        {
            firstMap[nonTerminal].insert("@");
        }
    }
    //for (auto i : nullMap)
    //{
    //    std::cout << i.first << i.second << std::endl;
    //}
}
void grammar::createFollow() {
    // 初始化followMap，所有非终结符的FOLLOW集合为空集
    for (const auto& nonTerminal : unendSet) {
        followMap[nonTerminal] = std::unordered_set<std::string>();
    }

    // 将文法开始符号的FOLLOW集合中加入结束符号$
    followMap[first].insert("$");

    bool changed = true;  // 标志变量，表示FOLLOW集合是否发生变化
    while (changed) {  // 当FOLLOW集合发生变化时，继续循环
        changed = false;  // 每次循环开始时，重置changed为false

        // 遍历每一个产生式规则
        for (const auto& rule : ex_G) {
            const std::string& left = rule.left;  // 产生式左部
            const std::vector<std::string>& right = rule.right;  // 产生式右部

            // 遍历产生式右部的每一个符号
            for (size_t i = 0; i < right.size(); ++i) {
                const std::string& symbol = right[i];  // 当前符号

                // 如果当前符号是非终结符
                if (isNonTerminal(symbol, unendSet)) {
                    std::unordered_set<std::string> followTemp;  // 临时集合，用于存储需要加入FOLLOW集合的符号

                    // FOLLOW规则1：A → αBβ，将FIRST(β)中除了ε以外的所有符号加入FOLLOW(B)中
                    if (i + 1 < right.size()) {  // 如果B后面还有符号β
                        for (size_t j = i + 1; j < right.size(); ++j) {
                            const std::string& nextSymbol = right[j];  // 下一个符号
                            if (nextSymbol == "@") {
                                continue;  // 跳过空符号
                            }

                            // 如果下一个符号是终结符，直接加入临时集合，然后停止处理
                            if (!isNonTerminal(nextSymbol, unendSet)) {
                                followTemp.insert(nextSymbol);
                                break;
                            }
                            else {
                                // 如果下一个符号是非终结符，将其FIRST集合加入临时集合
                                addToSet(followTemp, firstMap[nextSymbol]);
                                followTemp.erase("@");
                                // 如果下一个符号不能生成空串，停止处理
                                if (!nullMap[nextSymbol]) {
                                    break;
                                }
                            }
                        }
                    }

                    // FOLLOW规则2：A → αB 或 A → αBβ 且ε在FIRST(β)中，将FOLLOW(A)中的所有符号加入FOLLOW(B)中
                    bool addFollow = (i + 1 == right.size());  // 判断B是否是产生式最后一个符号
                    if (!addFollow && i + 1 < right.size()) {  // 如果B后面还有符号β
                        for (size_t j = i + 1; j < right.size(); ++j) {
                            const std::string& nextSymbol = right[j];  // 下一个符号
                            // 如果下一个符号是空符号或能生成空串，继续检查下一个符号
                            if (nextSymbol == "@" || nullMap[nextSymbol]) {
                                addFollow = true;
                            }
                            else {
                                addFollow = false;  // 只要有一个符号不能生成空串，停止检查
                                break;
                            }
                        }
                    }

                    // 如果需要将FOLLOW(A)中的符号加入FOLLOW(B)中
                    if (addFollow) {
                        addToSet(followTemp, followMap[left]);
                    }

                    // 如果FOLLOW集合发生变化，更新changed标志
                    if (addToSet(followMap[symbol], followTemp)) {
                        changed = true;
                    }
                }
            }
        }
    }


}


grammar::grammar(const std::string filepath) {
    std::ifstream infile(filepath);
    bool flag = false;
    if (infile.is_open()) {
        std::string sentence;
        while (std::getline(infile, sentence)) {
            std::stringstream ss(sentence);
            std::string left, assign, right;
            grammarNode newnode;
            ss >> left >> assign;
            if (!flag) {
                flag = true;
                first = left;
            }
            unendSet.insert(left);
            newnode.left = left;
            while (ss >> right) {
                newnode.right.push_back(right);
            }
            G.push_back(newnode);
        }
    }
    else {
        std::cout << "grammar error";
    }
    createExG();
    createFirst();
    createFollow();
    return;
}

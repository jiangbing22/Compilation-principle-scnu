#include "grammar.h"
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

// �������������һ�������Ƿ�Ϊ���ս��
bool isNonTerminal(const std::string& symbol, const std::unordered_set<std::string>& unendSet) {
    return unendSet.find(symbol) != unendSet.end();
}

// ������������һ�����ϵ�Ԫ����ӵ���һ�����ϣ�������Ƿ�����Ԫ�����
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
            }
            ex_G.push_back(newnode);
            if (itr != i.right.end())
            {
                itr++;
            }
        }
    }
}

void grammar::createFirst() {
    // ��ʼ��firstMap�����з��ս����FIRST����Ϊ�ռ�
    for (const auto& nonTerminal : unendSet) {
        firstMap[nonTerminal] = std::unordered_set<std::string>();
    }

    bool changed = true;
    while (changed) {
        changed = false;

        for (const auto& rule : ex_G) {
            const std::string& left = rule.left;
            const std::vector<std::string>& right = rule.right;

            bool epsilonFound = true;  // ���赱ǰ����ʽ�Ҳ��������ɿմ�
            for (size_t i = 0; i < right.size(); ++i) {
                const std::string& symbol = right[i];

                // ����������ս����������ӵ�FIRST(left)
                if (!isNonTerminal(symbol, unendSet)) {
                    if (firstMap[left].insert(symbol).second) {
                        changed = true;
                    }
                    epsilonFound = false;  // �ս���������ɿմ�
                    break;
                }
                else {
                    // ��FIRST(symbol)��ӵ�FIRST(left)
                    if (addToSet(firstMap[left], firstMap[symbol])) {
                        changed = true;
                    }

                    // ���FIRST(symbol)�������ţ����ټ���������һ������
                    if (firstMap[symbol].find("@") == firstMap[symbol].end()) {
                        epsilonFound = false;
                        break;
                    }
                }
            }

            // �����ǰ����ʽ�Ҳ����з��Ŷ������ɿմ������ż��뵽FIRST(left)
            if (epsilonFound) {
                if (firstMap[left].insert("@").second) {
                    changed = true;
                }
            }
        }
    }
}
void grammar::createFollow() {
    // ��ʼ��followMap�����з��ս����FOLLOW����Ϊ�ռ�
    for (const auto& nonTerminal : unendSet) {
        followMap[nonTerminal] = std::unordered_set<std::string>();
    }

    // ��ӿ�ʼ���ŵ�FOLLOW���ϳ�ʼΪ"$"
    followMap[first].insert("$");

    bool changed = true;
    while (changed) {
        std::cout << changed;
        changed = false;
        for (const auto& rule : ex_G) {
            const std::string& left = rule.left;
            const std::vector<std::string>& right = rule.right;

            for (size_t i = 0; i < right.size(); ++i) {
                const std::string& symbol = right[i];

                if (isNonTerminal(symbol, unendSet)) {
                    std::unordered_set<std::string> followSet;

                    bool epsilonInNextFirst = true;
                    for (size_t j = i + 1; j < right.size() && epsilonInNextFirst; ++j) {
                        epsilonInNextFirst = false;
                        const std::string& nextSymbol = right[j];

                        if (!isNonTerminal(nextSymbol, unendSet)) {
                            followSet.insert(nextSymbol);
                            break;
                        }
                        else {
                            const auto& nextFirstSet = firstMap[nextSymbol];
                            followSet.insert(nextFirstSet.begin(), nextFirstSet.end());
                            followSet.erase("@");

                            if (nextFirstSet.find("@") != nextFirstSet.end()) {
                                epsilonInNextFirst = true;
                            }
                        }
                    }

                    if (epsilonInNextFirst || i + 1 == right.size()) {
                        if (addToSet(followSet, followMap[left])) {
                            changed = true;
                        }
                    }

                    if (addToSet(followMap[symbol], followSet)) {
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
    /*createFollow();*/
    return;
}

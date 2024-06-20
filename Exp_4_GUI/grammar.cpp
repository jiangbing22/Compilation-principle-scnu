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
    int grammarnum = 1;//���
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

            bool epsilonFound = true; 
            for (size_t i = 0; i < right.size(); ++i) {
                const std::string& symbol = right[i];

                // ����������ս����������ӵ�FIRST(left)
                if (symbol == "@")
                {
                    break;
                }
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
                    if (!nullMap[symbol]) {
                        epsilonFound = false;
                        break;
                    }
                }
            }
                        
            // �����ǰ����ʽ�Ҳ����з��Ŷ������ɿմ�����first�����пմ�
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
    // ��ʼ��followMap�����з��ս����FOLLOW����Ϊ�ռ�
    for (const auto& nonTerminal : unendSet) {
        followMap[nonTerminal] = std::unordered_set<std::string>();
    }

    // ���ķ���ʼ���ŵ�FOLLOW�����м����������$
    followMap[first].insert("$");

    bool changed = true;  // ��־��������ʾFOLLOW�����Ƿ����仯
    while (changed) {  // ��FOLLOW���Ϸ����仯ʱ������ѭ��
        changed = false;  // ÿ��ѭ����ʼʱ������changedΪfalse

        // ����ÿһ������ʽ����
        for (const auto& rule : ex_G) {
            const std::string& left = rule.left;  // ����ʽ��
            const std::vector<std::string>& right = rule.right;  // ����ʽ�Ҳ�

            // ��������ʽ�Ҳ���ÿһ������
            for (size_t i = 0; i < right.size(); ++i) {
                const std::string& symbol = right[i];  // ��ǰ����

                // �����ǰ�����Ƿ��ս��
                if (isNonTerminal(symbol, unendSet)) {
                    std::unordered_set<std::string> followTemp;  // ��ʱ���ϣ����ڴ洢��Ҫ����FOLLOW���ϵķ���

                    // FOLLOW����1��A �� ��B�£���FIRST(��)�г��˦���������з��ż���FOLLOW(B)��
                    if (i + 1 < right.size()) {  // ���B���滹�з��Ŧ�
                        for (size_t j = i + 1; j < right.size(); ++j) {
                            const std::string& nextSymbol = right[j];  // ��һ������
                            if (nextSymbol == "@") {
                                continue;  // �����շ���
                            }

                            // �����һ���������ս����ֱ�Ӽ�����ʱ���ϣ�Ȼ��ֹͣ����
                            if (!isNonTerminal(nextSymbol, unendSet)) {
                                followTemp.insert(nextSymbol);
                                break;
                            }
                            else {
                                // �����һ�������Ƿ��ս��������FIRST���ϼ�����ʱ����
                                addToSet(followTemp, firstMap[nextSymbol]);
                                followTemp.erase("@");
                                // �����һ�����Ų������ɿմ���ֹͣ����
                                if (!nullMap[nextSymbol]) {
                                    break;
                                }
                            }
                        }
                    }

                    // FOLLOW����2��A �� ��B �� A �� ��B�� �Ҧ���FIRST(��)�У���FOLLOW(A)�е����з��ż���FOLLOW(B)��
                    bool addFollow = (i + 1 == right.size());  // �ж�B�Ƿ��ǲ���ʽ���һ������
                    if (!addFollow && i + 1 < right.size()) {  // ���B���滹�з��Ŧ�
                        for (size_t j = i + 1; j < right.size(); ++j) {
                            const std::string& nextSymbol = right[j];  // ��һ������
                            // �����һ�������ǿշ��Ż������ɿմ������������һ������
                            if (nextSymbol == "@" || nullMap[nextSymbol]) {
                                addFollow = true;
                            }
                            else {
                                addFollow = false;  // ֻҪ��һ�����Ų������ɿմ���ֹͣ���
                                break;
                            }
                        }
                    }

                    // �����Ҫ��FOLLOW(A)�еķ��ż���FOLLOW(B)��
                    if (addFollow) {
                        addToSet(followTemp, followMap[left]);
                    }

                    // ���FOLLOW���Ϸ����仯������changed��־
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

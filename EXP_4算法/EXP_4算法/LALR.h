#pragma once
#include"grammar.h"	
#include <iostream>
#include <sstream>
#include <queue>

// LR1��Ľṹ
struct LR1Item {
    std::string lhs;
    std::vector<std::string> rhs;
    int dotPos;
    std::string lookahead;

    bool operator==(const LR1Item& other) const {
        return lhs == other.lhs && rhs == other.rhs && dotPos == other.dotPos && lookahead == other.lookahead;
    }
};

// ��ϣ��������unordered_set
namespace std {
    template <>
    struct hash<LR1Item> {
        std::size_t operator()(const LR1Item& item) const {
            std::size_t hash1 = std::hash<std::string>()(item.lhs);
            std::size_t hash2 = 0;
            for (const auto& symbol : item.rhs) {
                hash2 ^= std::hash<std::string>()(symbol);
            }
            std::size_t hash3 = std::hash<int>()(item.dotPos);
            std::size_t hash4 = std::hash<std::string>()(item.lookahead);
            return hash1 ^ hash2 ^ hash3 ^ hash4;
        }
    };
}
struct LR1NODE {
    std::unordered_set<LR1Item> items;
    std::unordered_map<std::string, LR1NODE*> state;
    int stateNum;
};
class LALR
{
private:
    grammar G;
    LR1NODE* head;

    // �հ�����
    std::unordered_set<LR1Item> closure(const std::unordered_set<LR1Item>& items);

    // ת�ƺ���
    std::unordered_set<LR1Item> gotoState(const std::unordered_set<LR1Item>& items, const std::string& symbol);

    // ����LR1�Զ���
    void createLR1Automaton();

public:
    LALR(const std::string filepath);
};


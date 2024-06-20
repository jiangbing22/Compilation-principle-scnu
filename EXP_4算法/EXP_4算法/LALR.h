#pragma once
#include"grammar.h"	
#include <iostream>
#include <sstream>
#include <queue>
#include<set>
// LR1项的结构
struct LR1Item {
    std::string lhs;
    std::vector<std::string> rhs;
    int dotPos;
    std::string lookahead;
    std::string rhs2str() const
    {
        std::string result;
        for (auto i : rhs)
        {
            result += i;
        }
        return result;
    }
    bool operator==(const LR1Item& other) const {
        return lhs == other.lhs && rhs == other.rhs && dotPos == other.dotPos && lookahead == other.lookahead;
    }
};

// 哈希函数重载
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

    template <>
    struct hash<std::pair<std::string, std::vector<std::string>>> {
        std::size_t operator()(const std::pair<std::string, std::vector<std::string>>& core) const {
            std::size_t hash1 = std::hash<std::string>()(core.first);
            std::size_t hash2 = 0;
            for (const auto& symbol : core.second) {
                hash2 ^= std::hash<std::string>()(symbol);
            }
            return hash1 ^ hash2;
        }
    };

    template <>
    struct hash<std::set<std::pair<std::string, std::vector<std::string>>>> {
        std::size_t operator()(const std::set<std::pair<std::string, std::vector<std::string>>>& coreSet) const {
            std::size_t hash = 0;
            for (const auto& core : coreSet) {
                hash ^= std::hash<std::pair<std::string, std::vector<std::string>>>()(core);
            }
            return hash;
        }
    };
    template <>
    struct hash<std::unordered_set<LR1Item>> {
        std::size_t operator()(const std::unordered_set<LR1Item>& itemSet) const {
            std::size_t hash = 0;
            for (const auto& item : itemSet) {
                hash ^= std::hash<LR1Item>()(item);
            }
            return hash;
        }
    };
}
struct LR1NODE {
    std::unordered_set<LR1Item> items;
    std::unordered_map<std::string, LR1NODE*> state;
    int stateNum;
    std::string core;
};

class LALR
{
private:
    grammar G;
    LR1NODE* head;
    LR1NODE* LALRhead;
    std::vector<LR1NODE*> indexmap;
    std::unordered_map<int, std::unordered_map<std::string, std::string>> actionTable;
    std::unordered_map<int, std::unordered_map<std::string, int>> gotoTable;
    std::string countcore(std::unordered_set<LR1Item> itemset);
    void generateParsingTable();

    int statecount;
    // 闭包函数
    std::unordered_set<LR1Item> closure(const std::unordered_set<LR1Item>& items);

    // 转移函数
    std::unordered_set<LR1Item> gotoState(const std::unordered_set<LR1Item>& items, const std::string& symbol);

    // 创建LR1自动机
    void createLR1Automaton();
    void createLALRAutomaton();

public:
    LALR(const std::string filepath);
    void printAutomaton(LR1NODE* start) const;
    void printParsingTable() const;
};



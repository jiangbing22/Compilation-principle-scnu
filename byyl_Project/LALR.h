#pragma once
#include"grammar.h"	
#include <iostream>
#include <sstream>
#include <queue>
#include<set>
#include<stack>
using namespace std;
//�﷨������Ŀ��Ԫ
struct AI {
    int kind;    // 1��ʾ״̬��2��ʾ�ַ�
    int state;
    string Gname;
    pair<string, string> token;
    
};
// �﷨���ڵ�
struct SyntaxTreeNode {
    string tokenString;//��ǰֵ
    vector<shared_ptr<SyntaxTreeNode>>children;//���ӽڵ�
    /*
    * ���캯��
    */
    SyntaxTreeNode() :tokenString("") {};
    /*
    * ���캯��
    */
    SyntaxTreeNode(string value) : tokenString(value) {}
};


// LR1��Ľṹ��Ԫ
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

// ��ϣ��������
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

    //��ŵ�NODEת��
    std::vector<LR1NODE*> indexmap;

    //��Ϊ��
    std::unordered_map<int, std::unordered_map<std::string, std::string>> actionTable;

    //ת�Ʊ�
    std::unordered_map<int, std::unordered_map<std::string, int>> gotoTable;

    std::string countcore(std::unordered_set<LR1Item> itemset);
    void generateParsingTable();

    int statecount;
    // �հ�����
    std::unordered_set<LR1Item> closure(const std::unordered_set<LR1Item>& items);

    // ת�ƺ���
    std::unordered_set<LR1Item> gotoState(const std::unordered_set<LR1Item>& items, const std::string& symbol);

    vector<string> analysisStack1;//����ջ���Ų���

    vector<int> analysisStack2;//����ջ״̬����

    vector<pair<string, string>> sentenceAndType;
    //�﷨��
    std::shared_ptr<SyntaxTreeNode> syntaxTreeRoot = nullptr;
    void createLR1Automaton();
    void createLALRAutomaton();
public:
    grammar G;
    LR1NODE* head;
    LR1NODE* LALRhead;
    LALR(const std::string filepath);
    string Analysis(std::string filepath);
    void printSyntaxTree(const std::shared_ptr<SyntaxTreeNode>& node, std::stringstream& ss, int depth);

};




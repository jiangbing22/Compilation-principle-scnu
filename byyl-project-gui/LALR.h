#pragma once
#include"grammar.h"
#include <iostream>
#include <sstream>
#include <queue>
#include<set>
#include<stack>
#include <QTableWidget>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QTreeView>
// LR1项的结构
using namespace std;
struct AI {
    int kind;    // 1表示状态，2表示字符
    int state;
    string Gname;
    pair<string, string> token;

};
// 语法树节点
struct SyntaxTreeNode {
    string tokenString;//当前值
    vector<shared_ptr<SyntaxTreeNode>>children;//孩子节点
    SyntaxTreeNode() :tokenString("") {};
    /*
    * 构造函数
    */
    SyntaxTreeNode(string value) : tokenString(value) {}
};
struct LR1Item {
    std::string lhs;           // 左手边非终结符
    std::vector<std::string> rhs; // 右手边产生式序列，用vector<string>表示
    int dotPos;                // 点号位置，表示当前已经处理到rhs中的哪个位置
    std::string lookahead;     // 向前看符号

    std::string rhs2str() const // 将rhs转换成字符串
    {
        std::string result;    // 初始化结果字符串
        for (auto i : rhs)     // 遍历rhs中的每个元素
        {
            result += i;       // 将元素累加到结果字符串中
        }
        return result;         // 返回结果字符串
    }

    bool operator==(const LR1Item& other) const // 重载==运算符，用于比较两个LR1Item是否相等
    {
        return lhs == other.lhs &&         // 比较左手边非终结符
               rhs == other.rhs &&         // 比较右手边产生式序列
               dotPos == other.dotPos &&   // 比较点号位置
               lookahead == other.lookahead; // 比较向前看符号
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
    std::unordered_set<LR1Item> items; // 存储该节点包含的LR1项目集合，使用无序集合来保证项目的唯一性
    std::unordered_map<std::string, LR1NODE*> state; // 表示根据某个符号转移到的下一个状态，键为符号，值为指向下一个状态的指针
    int stateNum; // 状态编号，用于标识不同的状态节点
    std::string core; // 核心项目，用于合并不同状态节点
};

class LALR
{
private:

private:

    //编号到NODE转换
    std::vector<LR1NODE*> indexmap;

    //行为表
    std::unordered_map<int, std::unordered_map<std::string, std::string>> actionTable;

    //转移表
    std::unordered_map<int, std::unordered_map<std::string, int>> gotoTable;

    std::string countcore(std::unordered_set<LR1Item> itemset);
    void generateParsingTable();

    int statecount;
    // 闭包函数
    std::unordered_set<LR1Item> closure(const std::unordered_set<LR1Item>& items);

    // 转移函数
    std::unordered_set<LR1Item> gotoState(const std::unordered_set<LR1Item>& items, const std::string& symbol);

    vector<string> analysisStack1;//分析栈符号部分

    vector<int> analysisStack2;//分析栈状态部分

    vector<pair<string, string>> sentenceAndType;
    //语法树
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



    friend void printAutomaton(const LALR& lalr, LR1NODE* start, QTableWidget* tableWidget);
    friend void printParsingTable(const LALR& lalr, QTableWidget* tableWidget);
    void printTreeView(QTreeView *treeView);
};
void printAutomaton(const LALR& lalr, LR1NODE* start, QTableWidget* tableWidget);
void printParsingTable(const LALR& lalr, QTableWidget* tableWidget);
void populateTreeView(const std::shared_ptr<SyntaxTreeNode>& node, QStandardItem* parentItem);


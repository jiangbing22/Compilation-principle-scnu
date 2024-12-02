// Copyright (c) 2024, 蒋昕玮
// 保留所有权利。
// 版本: 1.0
// 功能摘要:
// 本代码实现了一个LALR（Look-Ahead LR）解析器生成器，适用于上下文无关文法。
// 定义了LR(1)项、语法树节点以及LALR自动机节点的结构。
// 提供了构建LALR自动机、生成解析表以及构建语法树的功能。
// `LALR`类负责解析逻辑，而辅助函数提供了以GUI形式打印自动机和解析表的接口。
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
// 表示LR1项的结构，包括状态、文法名称和符号信息
using namespace std;

// AI（Action/Item）结构，用于存储项的类型、状态、文法名称和符号信息
struct AI {
    int kind;    // 1表示状态，2表示字符
    int state;   // 状态编号
    string Gname;  // 文法名称
    pair<string, string> token;  // token对，表示符号类型和具体值
};

// 语法树节点，表示解析后的每个符号
struct SyntaxTreeNode {
    string tokenString;                  // 当前符号的值
    vector<shared_ptr<SyntaxTreeNode>> children; // 孩子节点
    SyntaxTreeNode() : tokenString("") {};   // 默认构造函数
    SyntaxTreeNode(string value) : tokenString(value) {} // 带值构造函数
};

// LR1项结构，包含LHS（左边非终结符）、RHS（右边产生式）、点号位置（表示当前解析的位置）和向前看符号
struct LR1Item {
    std::string lhs;           // 左边非终结符
    std::vector<std::string> rhs; // 右边产生式符号序列
    int dotPos;                // 点号位置，表示解析进度
    std::string lookahead;     // 向前看符号，用于决定解析动作

    // 将RHS转换为字符串形式
    std::string rhs2str() const {
        std::string result;
        for (auto i : rhs) {
            result += i;
        }
        return result;
    }

    // 重载等号运算符，比较两个LR1项是否相等
    bool operator==(const LR1Item& other) const {
        return lhs == other.lhs &&
               rhs == other.rhs &&
               dotPos == other.dotPos &&
               lookahead == other.lookahead;
    }
};

// 哈希函数重载，允许LR1项及其相关结构用于无序集合/映射
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

// LR1NODE结构，表示LR1自动机中的一个状态节点，包含LR1项的集合、状态转移信息和状态编号
struct LR1NODE {
    std::unordered_set<LR1Item> items; // 存储LR1项的集合
    std::unordered_map<std::string, LR1NODE*> state; // 根据符号进行状态转移，键为符号，值为目标状态指针
    int stateNum; // 状态编号
    std::string core; // 核心项，用于合并不同状态节点
};

// LALR类，包含文法、状态管理和解析逻辑
class LALR {
private:
    std::vector<LR1NODE*> indexmap; // 状态索引与LR1节点的映射
    std::unordered_map<int, std::unordered_map<std::string, std::string>> actionTable; // 解析动作表
    std::unordered_map<int, std::unordered_map<std::string, int>> gotoTable; // 状态转移表

    // 辅助函数，用于计算核心项和生成解析表
    std::string countcore(std::unordered_set<LR1Item> itemset);
    void generateParsingTable();

    int statecount; // 状态计数器，用于给状态编号
    // 闭包函数，计算一组LR1项的闭包
    std::unordered_set<LR1Item> closure(const std::unordered_set<LR1Item>& items);
    // 转移函数，计算一组LR1项根据某个符号转移后的状态
    std::unordered_set<LR1Item> gotoState(const std::unordered_set<LR1Item>& items, const std::string& symbol);
    
    // 语法树根节点
    std::shared_ptr<SyntaxTreeNode> syntaxTreeRoot = nullptr;
    
    // 自动机构造函数
    void createLR1Automaton();
    void createLALRAutomaton();

public:
    grammar G;           // 被解析的文法
    LR1NODE* head;       // LR1自动机的起始节点
    LR1NODE* LALRhead;   // LALR自动机的起始节点
    
    // 构造函数，通过文件路径加载文法
    LALR(const std::string filepath);

    // 解析函数，分析输入文件
    string Analysis(std::string filepath,string operatorpath);

    // 打印语法树的函数
    void printSyntaxTree(const std::shared_ptr<SyntaxTreeNode>& node, std::stringstream& ss, int depth);

    // 友元函数，打印自动机和解析表的GUI界面
    friend void printAutomaton(const LALR& lalr, LR1NODE* start, QTableWidget* tableWidget);
    friend void printParsingTable(const LALR& lalr, QTableWidget* tableWidget);

    // 将语法树打印到树视图中
    void printTreeView(QTreeView *treeView);
};

// 打印LR1自动机到QTableWidget表格中
void printAutomaton(const LALR& lalr, LR1NODE* start, QTableWidget* tableWidget);

// 打印解析表到QTableWidget表格中
void printParsingTable(const LALR& lalr, QTableWidget* tableWidget);

// 将语法树填充到QTreeView控件中
void populateTreeView(const std::shared_ptr<SyntaxTreeNode>& node, QStandardItem* parentItem);

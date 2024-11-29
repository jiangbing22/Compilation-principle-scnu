// Copyright (c) 2024, 蒋昕玮
// 保留所有权利。
// 版本: 1.0
// 功能摘要:
// 该代码实现了从NFA（非确定性有限自动机）构建DFA（确定性有限自动机）的功能，并提供了最小化DFA的功能。
// `DFA_graph`类处理DFA图的构建、最小化以及状态和转换的管理。它通过将NFA转换为DFA，帮助实现正则表达式的自动机求解。
// 其中涉及的DFA图是用一个包含状态和转移信息的图表示的，并提供了方法来获取状态信息、转移图、最小化后的状态信息等。
#pragma once
#include"mutils.h"
#include"NFA.h"
#include<fstream>
#define DFA_GRAPH std::vector<pair<vector<int>, unordered_map<char, vector<int>>>>

// 打印NFA图的函数声明
void print_NFA(NFA_graph NFA);

// DFA_graph类定义，表示DFA图
class DFA_graph
{
public:
    NFA_graph total_NFA;  // 存储从NFA转换过来的NFA图

    // 从多个NFA图构建DFA图
    void build_from_NFA(vector<NFA_graph> NFA);

    // 最小化DFA图
    void minimize();

    // 获取DFA的起始状态
    int get_start() { return start; };

    // 获取DFA的结束状态集合
    set<int> get_end() { return end; };

    // 获取最小化后DFA的结束状态集合
    set<int> get_minimize_end() { return minimize_end; };

    // 获取DFA图的所有状态和转移信息
    DFA_GRAPH get_Graph() { return Graph; };

    // 获取DFA图的状态数量
    size_t size() const
    {
        return Graph.size();
    }

    // 状态映射表，将状态名称映射到状态编号
    unordered_map<string, int> state_map;

    // 获取DFA图的所有输入符号
    unordered_set<char> get_key() { return DFA_key_set; };

    // 获取最小化后的DFA转移图
    unordered_map<int, unordered_map<char, int>> get_minimizeGraph() { return minimizeGraph; };

    // 获取某个结束状态的类型字符串
    string getEndtype(int a) { return endstring[a]; };

    // 获取某个最小化后的结束状态的类型字符串
    string getminEndtype(int a) { return minendstring[a]; };

    // 生成DFA的代码表示
    string generateCode();

    // 起始状态
    int start;

    // 结束状态集合
    set<int> end;

    // 存储DFA图的状态和转移信息
    DFA_GRAPH Graph;

    // 存储最小化后DFA图的结束状态集合
    set<int> minimize_end;

    // 存储最小化后DFA的状态转移图
    unordered_map<int, unordered_map<char, int>> minimizeGraph;

    // DFA图的所有输入符号集合
    unordered_set<char> DFA_key_set;

    // 字符串转整数向量的转换函数
    vector<int> stringToIntVector(string s);

    // 向量转字符串的转换函数
    string vectorToString(vector<int>& t);

    // 集合转字符串的转换函数
    string setToString(const set<int>& t);

    // 字符到字符串映射表的转换函数
    string mapToString(const unordered_map<char, string>& mp);

    // 字符到字符串映射表的转换函数（另一种实现）
    string mapToString(const map<char, string>& mp);

    // 重载下标操作符，通过状态编号访问DFA图中的状态和转移信息
    pair<vector<int>, unordered_map<char, vector<int>>>& operator[](int n);

    // 状态的结束类型字符串映射
    unordered_map<int, string> endstring;

    // 最小化DFA状态的结束类型字符串映射
    unordered_map<int, string> minendstring;
};

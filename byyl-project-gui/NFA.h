// Copyright (c) 2024, 蒋昕玮
// 保留所有权利。
// 版本: 1.0
// 功能摘要:
// 本代码实现了NFA（非确定性有限自动机）的基本数据结构和相关操作。
// 通过正则表达式（RE）生成NFA图，并支持基本的NFA操作符，如连接（&）、选择（|）、闭包（*）、正闭包（+）和可选（?）等。
// `NFA_graph`类表示一个NFA图，并提供了与NFA图相关的各种操作方法，如初始化、合并、连接、计算图等。

#pragma once
#include"RE.h"

//NFA图的宏定义
#define GRAPH std::vector<unordered_map<char, vector<int>>>

// NFA图类，用于表示非确定性有限自动机
class NFA_graph
{
public:
    // 默认构造函数，初始化图结构
    NFA_graph()
    {
        Graph.resize(1);  // 初始化图，大小为1
        start = end = 0;  // 初始化起始状态和结束状态
    }

    // 根据字符a初始化NFA图
    void init(char a);

    // NFA图的结束状态类型
    string endtype;

    // 获取NFA图中状态的数量
    int size() const
    {
        return Graph.size();  // 返回NFA图的状态数
    }

    // 重载下标操作符，返回指定状态的转移图
    unordered_map <char, vector<int>>& operator[](int n);

    // 获取整个NFA图
    vector<unordered_map<char, vector<int>>> get_graph()
    {
        return Graph;  // 返回NFA图的状态转移信息
    }

    // 获取NFA图的起始状态
    int get_start() { return start; };

    // 获取NFA图的结束状态
    int get_end() { return end; };

    // 获取NFA图的所有输入符号（即转移条件）
    set<char> getkey();

    // NFA图的连接操作符（&），返回一个新的NFA图
    NFA_graph& operator&(NFA_graph& b);

    // NFA图的选择操作符（|），返回一个新的NFA图
    NFA_graph& operator|(NFA_graph& b);

    // NFA图的闭包操作符（*），返回一个新的NFA图
    NFA_graph& operator*();

    // NFA图的正闭包操作符（+），返回一个新的NFA图
    NFA_graph& operator+();

    // NFA图的可选操作符（?），返回一个新的NFA图
    NFA_graph& optional();

    // 通过正则表达式生成NFA图
    void build_NFA(RE regex);

    // 合并两个NFA图
    void contact(NFA_graph& b);

    // NFA图的起始状态
    int start = 0;

    // NFA图的结束状态
    int end = 0;

    // 用于表示正则表达式中的操作符（例如：*，+，?，|，&，\\）
    unordered_set<char> calculator = { '*', '+', '?' , '|' ,'&','\\'};
    
    // 存储NFA图的状态转移信息，Graph[i]表示从状态i出发的所有转移（按字符分类）
    vector<unordered_map<char, vector<int>>> Graph;
};

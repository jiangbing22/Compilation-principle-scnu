// Copyright (c) 2024, 蒋昕玮
// 保留所有权利。
// 版本: 1.0
// 功能摘要:
// 本代码实现了正则表达式（RE）的处理与转换功能。主要用于将标准正则表达式（infix表示法）转换为后缀表达式（postfix表示法）。
// 提供了正则表达式的清理、括号配对、连接操作符的添加等功能，以便后续的NFA构建和正则引擎的实现。
#pragma once
#include "mutils.h"
#include <string>
using namespace std;



// 正则表达式类，包含正则表达式的处理、转换和输出
class RE {
public:
    // 构造函数，接收一个正则表达式字符串并进行一系列预处理
    RE(string initial) : re(initial) {
        // 去除两端的空白字符
        initial = trim(initial);
        // 处理括号匹配
        rBracket();
        // 为连接操作符添加连接符号（如果需要）
        addConcat();
        // 将正则表达式转换为后缀表达式
        toPost();
    };

    // 获取后缀表达式
    string get_post() { return re_post; };

    // 获取原始的正则表达式
    string get_re() { return re; };

private:
    // 去除字符串两端的空白字符
    std::string trim(const std::string& str) {
        // 找到字符串开始的第一个非空白字符
        auto start = str.begin();
        while (start != str.end() && std::isspace(*start)) {
            ++start;
        }
        
        // 找到字符串结束的第一个非空白字符
        auto end = str.end();
        do {
            --end;
        } while (std::distance(start, end) > 0 && std::isspace(*end));

        // 返回去除空白后的子字符串
        return std::string(start, end + 1);
    }

    // 操作符优先级映射
    unordered_map<char, int> prior = {
        {'*', 100}, {'+', 100}, {'?', 100}, {'|', 60}, {'&', 70}
    };

    // 存储正则表达式中的操作符和括号字符
    unordered_set<char> calculator = {
        '*', '+', '?' , '|' ,'&','(',')','[',']'
    };

    // 原始的正则表达式字符串
    string re;
    
    // 转换后的后缀表达式字符串
    string re_post;

    // 处理匹配括号，检查括号的配对
    void rBracket();

    // 添加显式连接符号
    void addConcat();

    // 将中缀正则表达式转换为后缀表达式（逆波兰表示法）
    void toPost();
};

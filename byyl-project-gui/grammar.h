// Copyright (c) 2024, 蒋昕玮
// 保留所有权利。
// 版本: 1.0
// 功能摘要:
// 本代码实现了上下文无关文法（CFG）的基础数据结构及操作方法。
// 提供了文法的表示、扩展文法（ExG）生成、First集合与Follow集合计算等功能。
// `grammarNode`结构表示一个文法产生式，`grammar`类则包含文法的相关操作，包括First、Follow集的计算及文法符号的管理。
#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<unordered_map>
#include<unordered_set>
// 语法树节点结构，表示文法的一个产生式
struct grammarNode
{
    std::string left;  // 产生式的左部（非终结符）
    std::vector<std::string> right;  // 产生式的右部（符号序列）

    // 将右部符号序列转换成字符串
    std::string right2str()
    {
        std::string result;
        for (auto i : right)
        {
            result += i;  // 将每个符号拼接成一个字符串
        }
        return result;  // 返回拼接后的字符串
    }
};

// grammar类，用于表示上下文无关文法及其操作
class grammar
{
private:
    // 用于构造扩展文法（ExG）
    void createExG();
    // 用于计算First集合
    void createFirst();
    // 用于计算Follow集合
    void createFollow();

public:
    std::string first;  // 用于存储First集合的字符串表示
    // 构造函数，通过文件路径加载文法
    grammar(const std::string filepath);
    
    // 存储First集合的映射，键为非终结符，值为对应的First集合
    std::unordered_map<std::string, std::unordered_set<std::string>> firstMap;

    // 存储Follow集合的映射，键为非终结符，值为对应的Follow集合
    std::unordered_map<std::string, std::unordered_set<std::string>> followMap;

    // 存储文法项的映射，键为产生式左部（非终结符），值为其在文法中的编号
    std::unordered_map<std::string, int> itemMap;

    // 存储每个符号是否可以推导出空串（ε）
    std::unordered_map<std::string, bool> nullMap;

    // 存储非终结符集合
    std::unordered_set<std::string> unendSet;

    // 存储终结符集合
    std::unordered_set<std::string> endSet;

    // 存储文法产生式集合
    std::vector<grammarNode> G;

    // 存储扩展文法的产生式集合
    std::vector<grammarNode> ex_G;
};

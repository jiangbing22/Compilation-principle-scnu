// Copyright (c) 2024, 蒋昕玮
// 保留所有权利。
// 版本: 1.0

#include "RE.h"

// 处理正则表达式中的字符集 '[]'，将其转换为适合内部处理的格式。
// 例如，将 "[a-z]" 转换为 "(a|b|c|d|...)" 形式。
void RE::rBracket() {
    int leftBracket = -1;  // 用于记录左括号'['的位置
    string result = "";    // 存储处理后的结果
    for (size_t i = 0; i < re.length(); i++) 
    {
        if (re[i] == '\\')  // 如果是转义字符，直接将其加入结果
        {
            result += re[i]; 
            result += re[i + 1];  // 加入转义后的字符
            i++;  // 跳过下一个字符，因为已经处理过
            continue;
        }
        else if (re[i] == '[')  // 如果遇到左括号 '['，记录其位置
        {
            leftBracket = i;
        } 
        else if (re[i] == ']')  // 如果遇到右括号 ']'，处理字符集
        {
            if (leftBracket != -1) 
            {
                // 提取括号内的内容（不包括 '[' 和 ']'）
                string subStr = re.substr(leftBracket + 1, i - leftBracket - 1); 
                string newStr = "(";
                // 遍历字符集中的内容，转换成类似 "a|b|c" 的形式
                for (size_t j = 0; j < subStr.size(); j += 3) 
                {
                    for (char ch = subStr[j]; j + 2 < subStr.size() && ch <= subStr[j + 2]; ch++) 
                    {
                        newStr += ch;   // 添加字符
                        newStr += '|';  // 添加 OR 操作符
                    }
                }
                if (!newStr.empty()) 
                {
                    // 去除最后一个多余的 '|'，然后加上 ')'
                    newStr.pop_back();
                    newStr += ')';
                    result += newStr;  // 将处理后的字符集加入结果
                }
            }
            leftBracket = -1;  // 重置为下一次的 '[' 做准备
        } 
        else
        {
            if (leftBracket == -1)
            {
                result += re[i];  // 如果不是在括号内，直接加入当前字符
            }
        }
    }
    if (!result.empty() && result.back() == '|')  // 如果结果以 '|' 结尾，去掉它
    {
        result.pop_back();
    }
    re = result;  // 更新正则表达式为处理后的结果
}

// 处理正则表达式中的连接操作符，默认在字符间添加连接符 '&'
// 例如，"a(b|c)" 会变成 "a&b|c"
void RE::addConcat()
{
    string result = "";  // 存储处理后的结果
    for (size_t i = 0; i < re.length()-1; i++) {
        result += re[i];  // 先将当前字符加入结果

        if (re[i] == '\\')  // 如果当前字符是转义字符，直接处理下一个字符
        {
            i++;  // 跳过下一个字符
            if (i < re.length() - 1)
            {
                result += re[i];
                // 如果下一个字符不是运算符或'('，加上连接符 '&'
                if (calculator.find(re[i + 1]) == calculator.end() || re[i + 1] == '(' || re[i + 1] == '\\')
                {
                    result += '&';
                }
            }
        }
        else if (calculator.find(re[i]) != calculator.end())  // 如果是运算符
        {
            if(re[i] == ')' || re[i] == '*' || re[i] == '+')  // 如果是闭括号或量词，检查后续字符
            {
                if(calculator.find(re[i + 1]) == calculator.end() || re[i + 1] == '(' || re[i + 1] == '\\')
                {
                    result += "&";  // 如果下一个字符不是运算符，加上连接符 '&'
                }
            }
        }
        else  // 如果当前字符不是运算符
        {
            // 如果下一个字符不是运算符或'('，也需要加上连接符 '&'
            if(calculator.find(re[i + 1]) == calculator.end() || re[i + 1] == '(' || re[i + 1] == '\\')
            {
                result += "&";
            }
        }
    }
    result += re.back();  // 将最后一个字符加到结果中
    re = result;  // 更新正则表达式为处理后的结果
}

// 将正则表达式从中缀表示法转换为后缀表示法（逆波兰表示法）
// 主要用于正则表达式的解析和计算
void RE::toPost() {
    if (re.empty()) {
        re_post = "";
        return;
    }
    stack<char> operators;  // 运算符栈
    string postfix = "";  // 存储后缀表达式
    string infix = re;  // 存储中缀表达式
    for (auto p = infix.begin(); p != infix.end(); p++) {
        auto c = *p;

        if (c == '\\')  // 如果是转义字符，直接将其加入后缀表达式
        {
            postfix += c;
            if (c != infix.back())
            {
                p++;
                postfix += *p;
            }
        }
        else if (calculator.find(c) == calculator.end())  // 如果是操作数（字面量字符）
        {
            postfix += c;
        }
        else if (c == '(')  // 左括号，压入运算符栈
        {
            operators.push(c);
        }
        else if (c == ')')  // 右括号，弹出运算符直到遇到左括号
        {
            while (!operators.empty() && operators.top() != '(') 
            {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop();  // 弹出 '('
        }
        else  // 运算符，按照优先级处理
        {
            // 弹出优先级大于或等于当前运算符的运算符，并加入后缀表达式
            while (!operators.empty() && prior[operators.top()] >= prior[c]) 
            {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);  // 将当前运算符压入栈
        }
    }
    while (!operators.empty())  // 将剩余的运算符弹出并加入后缀表达式
    {
        postfix += operators.top();
        operators.pop();
    }
    re_post = postfix;  // 更新正则表达式为后缀表达式
}

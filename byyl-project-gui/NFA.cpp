// Copyright (c) 2024, 蒋昕玮
// 保留所有权利。
// 版本: 1.0
#include "NFA.h"
set<char> NFA_graph::getkey()
{
    set<char> result;
    for (auto i : Graph)
    {
        for (auto j : i)
        {
            result.insert(j.first);
        }
    }
    return result;
}
void NFA_graph::contact(NFA_graph& b)
{
    // 计算当前NFA图的大小，作为偏移量
    int offset = size();

    // 遍历第二个NFA图的所有节点
    for (int i = 0; i < b.size(); ++i)
    {
        // 将第二个NFA图的节点添加到当前NFA图中
        Graph.push_back(b[i]);

        // 遍历当前节点的所有边
        for (auto& k : Graph.back())
        {
            // 遍历当前边的所有目标节点
            for (auto& v : k.second)
            {
                // 将目标节点的索引加上偏移量
                v += offset;
            }
        }
    }

    // 将第二个NFA图的起始节点和结束节点索引加上偏移量
    b.start += offset;
    b.end += offset;

    return;
}
NFA_graph& NFA_graph::operator&(NFA_graph& b)
{
    // 调用contact函数，将当前NFA与b进行连接
    contact(b);

    // 将当前NFA的结束状态与'$'连接，并指向b的起始状态
    // '$'是一个特殊的符号，用于表示NFA的接受状态
    this->Graph[this->end]['$'].push_back(b.start);

    // 更新当前NFA的结束状态为b的结束状态
    this->end = b.end;

    // 返回当前NFA的引用
    return *this;
}
NFA_graph& NFA_graph::operator|(NFA_graph& b)
{
    contact(b);
    unordered_map<char, vector<int>> newstart;
    newstart['$'].push_back(this->start);
    newstart['$'].push_back(b.start);
    Graph.push_back(newstart);
    this->start = Graph.size() - 1;

    unordered_map<char, vector<int>> newend;
    Graph.push_back(newend);
    this->Graph[this->end]['$'].push_back(Graph.size() - 1);
    this->Graph[b.end]['$'].push_back(Graph.size() - 1);
    this->end = Graph.size() - 1;

    return *this;
}
NFA_graph& NFA_graph::operator*()
{
    Graph[this->end]['$'].push_back(this->start);
    int old_start = this->start;
    int old_end = this->end;

    unordered_map<char, vector<int>> newstart;
    Graph.push_back(newstart);
    this->start = Graph.size() - 1;

    unordered_map<char, vector<int>> newend;
    Graph.push_back(newend);
    this->end = Graph.size() - 1;

    Graph[this->start]['$'].push_back(this->end);
    Graph[this->start]['$'].push_back(old_start);
    Graph[old_end]['$'].push_back(this->end);

    return *this;
}
NFA_graph& NFA_graph::operator+()
{
    NFA_graph temp1 = *this;
    NFA_graph temp2 = *this;
    NFA_graph result = temp1 & *temp2;
    this->Graph = result.get_graph();
    this->start = result.get_start();
    this->end = result.get_end();

    return *this;
}
NFA_graph& NFA_graph::optional()
{
    Graph[this->start]['$'].push_back(this->end);
    return *this;
}
void NFA_graph::init(char a)
{

    Graph.resize(2);
    this->end = 1;
    this->start = 0;
    Graph[0][a] = { this->end };

}

unordered_map<char, vector<int> >& NFA_graph::operator[](int n)
{
    if (n < Graph.size())
    {
        return Graph[n];
    }
    else
    {
        Graph.resize(n);
        return Graph[n];
    }
}
void NFA_graph::build_NFA(RE re)
{
    // 清空当前的图
    this->Graph.clear();

    // 初始化起始和结束节点
    this->start = 0;
    this->end = 0;

    // 创建一个栈用于存储NFA_graph对象
    stack<NFA_graph> stk;

    // 获取正则表达式
    string regex = re.get_post();

    // 遍历正则表达式的每个字符
    for (auto c = regex.begin(); c != regex.end(); c++)
    {
        // 如果字符不是运算符
        if (calculator.find(*c) == calculator.end())
        {
            // 创建一个临时NFA_graph对象并初始化
            NFA_graph temp;
            temp.init(*c);
            // 将临时对象压入栈中
            stk.emplace(temp);
        }
        // 如果字符是转义字符'\'
        else if (*c == '\\')
        {
            // 移动到下一个字符
            c++;
            // 创建一个临时NFA_graph对象
            NFA_graph temp;
            // 根据转义字符进行初始化
            if(*c == 'n')
            {
                temp.init('\n');
            }
            else
            {
                temp.init(*c);
            }
            // 将临时对象压入栈中
            stk.emplace(temp);
        }
        // 如果是运算符
        else
        {
            // 根据运算符进行不同的操作
            switch (*c)
            {
                // 与运算符'&'
            case '&':
            {
                // 弹出栈顶两个对象
                NFA_graph graph1 = stk.top();
                stk.pop();
                NFA_graph graph2 = stk.top();
                stk.pop();
                // 执行与操作并将结果压入栈中
                NFA_graph result = graph2 & graph1;
                stk.push(result);
                break;
            }

                // 或运算符'|'
            case '|':
            {
                // 如果栈中只有一个对象
                if (stk.size() == 1)
                {
                    // 弹出栈顶对象
                    NFA_graph graph1 = stk.top();
                    stk.pop();
                    // 执行可选操作并将结果压入栈中
                    NFA_graph result = graph1.optional();
                    stk.push(result);
                }
                else
                {
                    // 弹出栈顶两个对象
                    NFA_graph graph1 = stk.top();
                    stk.pop();
                    NFA_graph graph2 = stk.top();
                    stk.pop();
                    // 执行或操作并将结果压入栈中
                    NFA_graph result = graph2 | graph1;
                    stk.push(result);
                }
                break;
            }
                // 星号运算符'*'
            case '*':
            {
                // 弹出栈顶对象
                NFA_graph graph1 = stk.top();
                stk.pop();
                // 执行星号操作并将结果压入栈中
                NFA_graph result = *graph1;
                stk.push(result);
                break;
            }
                // 加号运算符'+'
            case '+':
            {
                // 弹出栈顶对象
                NFA_graph graph1 = stk.top();
                stk.pop();
                // 执行加号操作并将结果压入栈中
                NFA_graph result = +graph1;
                stk.push(result);
                break;
            }
                // 问号运算符'?'
            case '?':
            {
                // 弹出栈顶对象
                NFA_graph graph1 = stk.top();
                stk.pop();
                // 执行问号操作并将结果压入栈中
                NFA_graph result = graph1.optional();
                stk.push(result);
                break;
            }
            }

        }
    }

    // 获取栈顶对象的图、起始节点和结束节点
    this->Graph = stk.top().get_graph();
    this->start = stk.top().start;
    this->end = stk.top().end;
    return;
}
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
    int offset = size();
    for (int i = 0; i < b.size(); ++i)
    {
        Graph.push_back(b[i]);
        for (auto& k : Graph.back())
            for (auto& v : k.second)
                v += offset;
    }
    b.start += offset;
    b.end += offset;
    return;
}
NFA_graph& NFA_graph::operator&(NFA_graph& b)
{
    contact(b);
    this->Graph[this->end]['$'].push_back(b.start);
    this->end = b.end;
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

    this->Graph.clear();
    this->start = 0;
    this->end = 0;
    stack<NFA_graph> stk;
    string regex = re.get_post();
    for (auto c = regex.begin(); c != regex.end(); c++)
    {
        if (calculator.find(*c) == calculator.end())
        {
            NFA_graph temp;
            temp.init(*c);
            stk.emplace(temp);
        }
        else if (*c == '\\')
        {
            c++;
            std::cout << *c<<endl;
            NFA_graph temp;
            temp.init(*c);
            stk.emplace(temp);
        }
        else
        {
            switch (*c)
            {
            case '&':
            {
                NFA_graph graph1 = stk.top();
                stk.pop();
                NFA_graph graph2 = stk.top();
                stk.pop();
                NFA_graph result = graph2 & graph1;
                stk.push(result);
                break;
            }

            case '|':
            {
                if (stk.size() == 1)
                {
                    NFA_graph graph1 = stk.top();
                    stk.pop();
                    NFA_graph result = graph1.optional();
                    stk.push(result);
                }
                else
                {
                    NFA_graph graph1 = stk.top();
                    stk.pop();
                    NFA_graph graph2 = stk.top();
                    stk.pop();
                    NFA_graph result = graph2 | graph1;
                    stk.push(result);
                }
                break;
            }
            case '*':
            {
                NFA_graph graph1 = stk.top();
                stk.pop();
                NFA_graph result = *graph1;
                stk.push(result);
                break;
            }
            case '+':
            {
                NFA_graph graph1 = stk.top();
                stk.pop();
                NFA_graph result = +graph1;
                stk.push(result);
                break;
            }
            case '?':
            {
                NFA_graph graph1 = stk.top();
                stk.pop();
                NFA_graph result = graph1.optional();
                stk.push(result);
                break;
            }
            }

        }
    }
    this->Graph = stk.top().get_graph();
    this->start = stk.top().start;
    this->end = stk.top().end;
    return;
}

#include <unordered_map>
#include <stack>
#include <string>
#include<set>
using namespace std;

class RE {
public:
    RE(string initial) : re(initial) {
        init();
        /*to_post();*/
    };
    void init();
    string get_post() { return re_post; };
    string get_re() { return re; };
private:
    unordered_map<char, int> prior = {
        {'*', 100}, {'+', 100}, {'?', 100}, {'.', 80}, {'|', 60}, {'@', 70}
    };
    string re;
    string re_post;
    void to_post();
};

void RE::init() {
    string result = "";
    string regex = re;
    for (size_t i = 0; i < regex.length(); i++) {

        if (regex[i] != '[')
        {
            result += regex[i];
        } 

        if (i == regex.length() - 1)
        {
            break;
        }
        if (isalpha(regex[i])||regex[i] == '*' || regex[i] == '+' || regex[i] == '?'||regex[i]==')')
        {
            
            if (isalpha(regex[i + 1]) || regex[i + 1] == '(')
            {
                result.push_back('@');
            }
        }
        if (regex[i] == '[')
        {
            i++;
            result.push_back('(');
            while(regex[i] != ']')
            {
                result.push_back(regex[i]);
                if (regex[i + 1] != ']')
                {
                    result.push_back('|');
                }
                i++;
            }
            result.push_back(')');
        }
    }
    re = result;
}

void RE::to_post() {
    if (re.empty()) {
        re_post = "";
        return;
    }

    stack<char> operators;
    string postfix = "";
    string infix = re;

    for (char c : infix) {
        if (isalnum(c)) {
            
            postfix += c;
            
        }
        else if (c == '\\')
        {
            postfix +='\\';
        }
        else if (c == '(') {
            operators.push(c);
        }
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop();
        }
        else {
            while (!operators.empty() && prior[operators.top()] >= prior[c]) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    re_post = postfix;
}


class NFA_graph
{
public:
    NFA_graph()
    {
        Graph.resize(1);
        start = end = 0;
    }
    void init(char a);
    
    size_t size() const
    {
        return Graph.size();
    }
    unordered_map<char, vector<int>>& operator[](int n)
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
    
    NFA_graph& operator&(NFA_graph& b);
    NFA_graph& operator|(NFA_graph& b);
    NFA_graph& operator*();
    NFA_graph& operator+();
    NFA_graph& optional();
    NFA_graph build_NFA(RE regex);
private:
    vector<unordered_map<char, vector<int>>> Graph;
    int start, end;
    void contact(NFA_graph& b);
};

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
    //插入新的开始节点
    unordered_map<char, vector<int>> newstart;
    newstart['$'].push_back(this->start);
    newstart['$'].push_back(b.start);
    Graph.push_back(newstart);
    this->start = Graph.size()-1;

    //插入新的结尾节点
    unordered_map<char, vector<int>> newend;
    Graph.push_back(newend);
    this->Graph[this->end]['$'].push_back(Graph.size()-1);
    this->Graph[b.end]['$'].push_back(Graph.size()-1);
    this->end = Graph.size()-1;

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
    NFA_graph temp= *this;
    temp = temp & (*temp);
    return temp;
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
NFA_graph NFA_graph::build_NFA(RE re)
{
    stack<NFA_graph> stk;
    string regex = re.get_post();
    for (auto c : regex)
    {
        if (isalpha(c))
        {
            NFA_graph temp;
            temp.init(c);
            stk.emplace(temp);
        }
        else
        {
            switch (c)
            {
            case '&':
            {
                NFA_graph graph1 = stk.top();
                stk.pop();
                NFA_graph graph2 = stk.top();
                stk.pop();
                NFA_graph result = graph1 & graph2;
                stk.push(result);
                break;
            }

            case '|':
            {
                NFA_graph graph1 = stk.top();
                stk.pop();
                NFA_graph graph2 = stk.top();
                stk.pop();
                NFA_graph result = graph1 | graph2;
                stk.push(result);
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
    NFA_graph result = stk.top();
    return result;
}


class DFA
{
public:


private:
   



};



#include <unordered_map>
#include <stack>
#include <string>
#include<unordered_set>
#include<iostream>
#include<queue>
#include<set>
#define GRAPH std::vector<unordered_map<char, vector<int>>>
#define DFA_GRAPH std::vector<pair<vector<int>,unordered_map<char,vector<int>>>>
using namespace std;
class RE {
public:
    RE(string initial) : re(initial) {
        init();
        to_post();
    };
    void init();
    string get_post() { return re_post; };
    string get_re() { return re; };
private:
    unordered_map<char, int> prior = {
        {'*', 100}, {'+', 100}, {'?', 100}, {'|', 60}, {'&', 70}
    };
    unordered_set<char> calculator = {
    '*', '+', '?' , '|' ,'&','(',')','\\','[',']'
    };
    string re;
    string re_post;
    void to_post();
};
void RE::init() {
    string result = "";
    string regex = re;
    regex.erase(remove(regex.begin(), regex.end(),' '), regex.end());
    for (size_t i = 0; i < regex.length(); i++) {

        if (regex[i] != '[')
        {
            result += regex[i];
        }
        if (i == regex.length() - 1)
        {
            break;
        }
        if (calculator.find(regex[i])==calculator.end() || regex[i] == '*' || regex[i] == '+' || regex[i] == '?' || regex[i] == ')' || regex[i] == ']')
        {
            
            if (calculator.find(regex[i+1]) == calculator.end() || regex[i + 1] == '('||regex[i+1]=='['||regex[i+1]=='\\')
            {
                result.push_back('&');
            }
        }
        if (regex[i] == '[')
        {
            result.push_back('(');
            if(regex[i+2]=='-')
            { 
                while (regex[i + 2] == '-'&&regex[i+1]!=']') {
                    for (char j = regex[i + 1]; j <= regex[i + 3]; j++)
                    {
                        result.push_back(j);
                        result.push_back('|');
                        
                    }
                    i += 3;
                }
                result.erase(result.length() - 1);
                result.push_back(')');
                i++;

            }
            else
            {
                i++;
                while (regex[i] != ']')
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
        if (regex[i] == '\\')
        {
            result += regex[i + 1];
            if (i + 2 < regex.length())
            {
                if (calculator.find(regex[i + 2])==calculator.end() || regex[i + 2] == '(' || regex[i + 2] == '\\')
                {
                    result.push_back('&');
                }
                i += 1;
                continue;
            }
            else
            {
                break;
            }
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
        if (calculator.find(c)==calculator.end()) {
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
    
    int size() const
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
    vector<unordered_map<char, vector<int>>> get_graph()
    {
        return Graph;
    }
    int get_start() { return start; };
    int get_end() { return end; };
    set<char> getkey();
    NFA_graph& operator&(NFA_graph& b);
    NFA_graph& operator|(NFA_graph& b);
    NFA_graph& operator*();
    NFA_graph& operator+();
    NFA_graph& optional();
    void build_NFA(RE regex);
private:
    vector<unordered_map<char, vector<int>>> Graph;
    int start, end;
    void contact(NFA_graph& b);
    unordered_set<char> calculator = {'*', '+', '?' ,'.', '|' ,'&','(',')','\\'};
};
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
    //新开始节点
    unordered_map<char, vector<int>> newstart;
    Graph.push_back(newstart);
    this->start = Graph.size() - 1;
    //新结束节点
    unordered_map<char, vector<int>> newend;
    Graph.push_back(newend);
    this->end = Graph.size() - 1;
    //创建闭包连接
    Graph[this->start]['$'].push_back(this->end);
    Graph[this->start]['$'].push_back(old_start);
    Graph[old_end]['$'].push_back(this->end);

    return *this;
} 
NFA_graph& NFA_graph::operator+()
{
    //复制本体，防止递归调用
    NFA_graph temp1 = *this;
    NFA_graph temp2 = *this;
    NFA_graph result = temp1 & *temp2;
    //结果赋值回本体
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
void NFA_graph::build_NFA(RE re)
{
    stack<NFA_graph> stk;
    string regex = re.get_post();
    for (auto c=regex.begin();c!=regex.end();c++)
    {
        if (calculator.find(*c)==calculator.end())
        {
            NFA_graph temp;
            temp.init(*c);
            stk.emplace(temp);
        }
        else if (*c == '\\')
        {
            c++;
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
class DFA_graph
{
public:
    void build_from_NFA(NFA_graph NFA);
    void minimize();
    int get_start() { return start; };
    set<int> get_end() { return end; };
    set<int> get_minimize_end() { return minimize_end; };
    DFA_GRAPH get_Graph() { return Graph; };
    void init(char a); 
    size_t size() const
    {
        return Graph.size();
    }

    unordered_map<string, int> state_map;//判断集合是否已经存在
    unordered_set<char> get_key() { return DFA_key_set; };
    unordered_map<int, unordered_map<char, int>> get_minimizeGraph(){ return minimizeGraph; };
private:
    int start;
    set<int> end;
    DFA_GRAPH Graph;
    set<int> minimize_end;
    unordered_map<int,unordered_map<char,int>> minimizeGraph;
    unordered_set<char> DFA_key_set;
    string vectorToString(vector<int>& t)
    {
        string res = "{";
        for (auto p : t)
        {
            res += to_string(p) + ",";
        }
        res += "}";
        return res;
    }
    string setToString(set<int>& t)
    {
        string res = "{";
        for (auto p : t)
        {
            res += to_string(p) + ",";
        }
        res += "}";
        return res;
    }

    vector<int> stringToIntVector(string s)
    {
        vector<int> res;
        int temp = 0;
        for (int i = 1; i < s.size() - 1; i++)
        {
            if (isdigit(s[i]))
            {
                temp = temp * 10 + (s[i] - '0');
            }
            else
            {
                res.push_back(temp);
                temp = 0;
            }
        }
        return res;
    }
    string mapToString(const unordered_map<char, int>& mp) {
        string res;
        for (const auto& p : mp) {
            res += p.first;
            res += ':';
            res += to_string(p.second);
            res += " ";
        }
        return res;
    }
    pair<vector<int>,unordered_map<char, vector<int>>>& operator[](int n)
    {
        if (n < Graph.size())
        {
            return Graph[n];
        }
        else
        {
            Graph.resize(2*n);
            return Graph[n];
        }
    }
};
void DFA_graph::build_from_NFA(NFA_graph NFA)
{   

    GRAPH nfa = NFA.get_graph(); //NFA图的存储结构
    queue<vector<int>> state_queue;//状态遍历辅助队列
    set<char> key_set = NFA.getkey();//所有边的可能取值

    auto BFS_Closure = [&](const vector<int>& states) //BFS找到起始条件的epsilon闭包
     {
            set<int> closure;
            unordered_map<int, bool> visited;//访问标签
            for (int state : states) {
                closure.insert(state);
            }
            queue<int> q;//遍历辅助队列
            for (int state : states) {
                q.push(state);
                visited[state] = true;
                while (!q.empty()) {
                    int current = q.front();
                    q.pop();
                    for (int next : nfa[current]['$']) {
                        if (!visited[next]) {
                            closure.insert(next);
                            q.push(next);
                            visited[next] = true;
                        }
                    }
                }
            }
            return closure;
    };
    set<int> startstate = BFS_Closure({ NFA.get_start() });
    state_queue.push(vector<int>(startstate.begin(),startstate.end()));
    //state_map[setToString(startstate)]=this->Graph.size();
    while (!state_queue.empty())
    {
        vector<int> current_state = state_queue.front();
        state_queue.pop();
        if (current_state.empty())
        {
            continue;
        }
        for (auto c : key_set)
        {
            if (c == '$')
            {
                continue;
            }
            this->DFA_key_set.insert(c);
            set<int> next_state;
            for (auto i : current_state)
            {
                for (auto j : nfa[i][c])
                {
                    if (nfa[i].find(c) != nfa[i].end()) 
                    {
                        next_state.insert(j);
                    }
                }
            }
            set<int> next_state_closure = BFS_Closure(vector<int>{next_state.begin(), next_state.end()});//找到下一个状态中所有闭包
            vector<int> temp(next_state_closure.begin(), next_state_closure.end());//将set转换为vector
            string state_key = setToString(next_state_closure);
            if (state_map.find(vectorToString(current_state))!= state_map.end())
            {
                this->Graph[Graph.size() - 1].second[c] = temp;
            }
            else
            {
                state_map[vectorToString(current_state)] = Graph.size();
                this->Graph.push_back({ current_state,{} });
                this->Graph[Graph.size() - 1].second[c] = temp;
            }
            if (state_map.find(state_key)==state_map.end())
            {
                state_queue.push(temp);
            }
        }
    }
    this->start = 0;
    for (auto& entry : state_map) {
        string key = entry.first;
        if (key.find(to_string(NFA.get_end())) != string::npos) {
           this->end.insert(entry.second);
        }
    }
    return;
};
void DFA_graph::minimize()
{
    minimizeGraph.clear();
    minimize_end.clear();
    set<int> end_set_index = this->end;
    set<int> else_set_index;//非终态集合
    for (auto i : state_map)//初始化终态集合
    {
        if (this->end.find(i.second) != this->end.end())
        {
            else_set_index.insert(i.second);
        }
    }
    //遍历DFA，将状态集合转换为划分;
    vector<unordered_map<char, int>> partition_graph;//划分图，true表示在终态集合中,false表示不在，-1表示空;
    for (auto state : this->Graph)
    {
        auto t_map = state.second;//复制一份
        unordered_map<char, int> result;//将要插入划分图的元素
        for (auto key : DFA_key_set)
        {
            if (t_map[key].empty())
            {
                result[key] = -1;//不存在
            }
            else if (end_set_index.find(state_map[vectorToString(t_map[key])]) != end_set_index.end())//在终态集合中
            {
                result[key] = true;//在终态中
            }
            else
            {
                result[key] = false;//不在终态中
            }
        }
        partition_graph.push_back(result);
    }
    unordered_map<string, int>p_map;
    set<int> partition_tag;
    unordered_map<int,int>index_map;
    for (int i=0;i<partition_graph.size();i++)
    {
        string map_key = mapToString(partition_graph[i]);
        cout <<i<<" " << map_key << " " << endl;
        if (p_map.find(map_key)==p_map.end())
        {
            p_map[map_key] = i;
            partition_tag.insert(i);
            /*cout << i << " ";*/
        }
        else
        {
            /*cout << i << " " << p_map[map_key] << endl;*/
            index_map[i] = p_map[map_key];
        }
        
    }
    for (auto i : end_set_index)//找到最小化后DFA的终点
    {
        if (index_map.find(i) != index_map.end())
        {
            minimize_end.insert(index_map[i]);
        }
        else
        {
            minimize_end.insert(i);
        }
    }
    for (auto i: partition_tag)
    {
        if (partition_tag.find(i) == partition_tag.end())
        {
            continue;
        }

        auto t_map = Graph[i].second;//复制一份
        for (auto key : DFA_key_set)
        {
            if (!t_map[key].empty())
            {
                int index = state_map[vectorToString(t_map[key])];
                
                if (index_map.find(index) != index_map.end())
                {
                    minimizeGraph[i][key]=index_map[index];
                }
                else
                {
                    minimizeGraph[i][key] = index;
                }
            }
            else
            {
                minimizeGraph[i][key] = -1;
            }
        }
    }
    return;
}



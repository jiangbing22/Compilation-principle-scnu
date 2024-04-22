#include"to_DFA.h"
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
        if (calculator.find(regex[i])==calculator.end() || regex[i] == '*' || regex[i] == '+' || regex[i] == '?' || regex[i] == ')')
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
                if (calculator.find(regex[i + 2])==calculator.end() || regex[i + 2] == '('||regex[i+2]=='\\')
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
    //�����µĿ�ʼ�ڵ�
    unordered_map<char, vector<int>> newstart;
    newstart['$'].push_back(this->start);
    newstart['$'].push_back(b.start);
    Graph.push_back(newstart);
    this->start = Graph.size()-1;

    //�����µĽ�β�ڵ�
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
    //���Ʊ��壬��ֹ�ݹ�����
    NFA_graph temp1 = *this;
    NFA_graph temp2 = *this;
    NFA_graph result = temp1 & *temp2;
    //������ֵ�ر���
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

unordered_map<char, vector<int> > &NFA_graph::operator[](int n)
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
    this->start=0;
    this->end=0;
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
void DFA_graph::build_from_NFA(NFA_graph NFA)
{
    this->DFA_key_set.clear();
    this->Graph.clear();
    this->end.clear();
    state_map.clear();
    GRAPH nfa = NFA.get_graph(); //NFAͼ�Ĵ洢�ṹ
    queue<vector<int>> state_queue;//״̬������������
    set<char> key_set = NFA.getkey();//���бߵĿ���ȡֵ

    auto BFS_Closure = [&](const vector<int>& states) //BFS�ҵ���ʼ������epsilon�հ�
    {
        set<int> closure;
        unordered_map<int, bool> visited;//���ʱ�ǩ
        for (int state : states) {
            closure.insert(state);
        }
        queue<int> q;//������������
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
            set<int> next_state_closure = BFS_Closure(vector<int>{next_state.begin(), next_state.end()});//�ҵ���һ��״̬�����бհ�
            vector<int> temp(next_state_closure.begin(), next_state_closure.end());//��setת��Ϊvector
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
    set<int> else_set_index;
    for (auto i : state_map)
    {
        if (this->end.find(i.second) != this->end.end())
        {
            else_set_index.insert(i.second);
        }
    }
    vector<unordered_map<char, int>> partition_graph;//����ͼ��true��ʾ����̬������,false��ʾ���ڣ�-1��ʾ��;
    for (auto state : this->Graph)
    {
        auto t_map = state.second;//����һ��
        unordered_map<char, int> result;//��Ҫ���뻮��ͼ��Ԫ��
        for (auto key : DFA_key_set)
        {
            if (t_map[key].empty())
            {
                result[key] = -1;//������
            }
            else if (end_set_index.find(state_map[vectorToString(t_map[key])]) != end_set_index.end())//����̬������
            {
                result[key] = true;
            }
            else
            {
                result[key] = false;
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
        if(end_set_index.find(i)!=end_set_index.end())
        {
            map_key+=" end";
        }
        else
        {
            map_key+=" else";
        }
        cout <<i<<" " << map_key << " " << endl;
        if (p_map.find(map_key)==p_map.end())
        {
            p_map[map_key] = i;
            partition_tag.insert(i);

        }
        else
        {
            index_map[i] = p_map[map_key];
        }

    }
    for (auto i : end_set_index)
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

        auto t_map = Graph[i].second;//����һ��
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

string DFA_graph::vectorToString(vector<int> &t)
{
    string res = "{";
    for (auto p : t)
    {
        res += to_string(p) + ",";
    }
    res += "}";
    return res;
}

string DFA_graph::setToString(set<int> &t)
{
    string res = "{";
    for (auto p : t)
    {
        res += to_string(p) + ",";
    }
    res += "}";
    return res;
}

vector<int> DFA_graph::stringToIntVector(string s)
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

string DFA_graph::mapToString(const unordered_map<char, int> &mp) {
    string res;
    for (const auto& p : mp) {
        res += p.first;
        res += ':';
        res += to_string(p.second);
        res += " ";
    }
    return res;
}

pair<vector<int>, unordered_map<char, vector<int> > > &DFA_graph::operator[](int n)
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


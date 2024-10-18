#include "DFA.h"
void DFA_graph::build_from_NFA(NFA_graph NFA)
{
    this->DFA_key_set.clear();
    this->Graph.clear();
    this->end.clear();
    state_map.clear();
    GRAPH nfa = NFA.get_graph(); 
    queue<vector<int>> state_queue;
    set<char> key_set = NFA.getkey();

    auto BFS_Closure = [&](const vector<int>& states) 
        {
            set<int> closure;
            unordered_map<int, bool> visited;
            for (int state : states) {
                closure.insert(state);
            }
            queue<int> q;
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
    state_queue.push(vector<int>(startstate.begin(), startstate.end()));
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
            set<int> next_state_closure = BFS_Closure(vector<int>{next_state.begin(), next_state.end()});
            vector<int> temp(next_state_closure.begin(), next_state_closure.end());
            string state_key = setToString(next_state_closure);
            if (state_map.find(vectorToString(current_state)) != state_map.end())
            {
                this->Graph[Graph.size() - 1].second[c] = temp;
            }
            else
            {
                state_map[vectorToString(current_state)] = Graph.size();
                this->Graph.push_back({ current_state,{} });
                this->Graph[Graph.size() - 1].second[c] = temp;
            }
            if (state_map.find(state_key) == state_map.end())
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
            endstring[entry.second] = NFA.endtype;
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
    vector<unordered_map<char, int>> partition_graph;
    for (auto state : this->Graph)
    {
        auto t_map = state.second;
        unordered_map<char, int> result;
        for (auto key : DFA_key_set)
        {
            if (t_map[key].empty())
            {
                result[key] = -1;
            }
            else if (end_set_index.find(state_map[vectorToString(t_map[key])]) != end_set_index.end())
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
    unordered_map<int, int>index_map;
    for (int i = 0; i < partition_graph.size(); i++)
    {
        string map_key = mapToString(partition_graph[i]);
        if (end_set_index.find(i) != end_set_index.end())
        {
            map_key += " end";
        }
        else
        {
            map_key += " else";
        }
        cout << i << " " << map_key << " " << endl;
        if (p_map.find(map_key) == p_map.end())
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
            minendstring[index_map[i]] = endstring[i];
        }
        else
        {
            minimize_end.insert(i);
            minendstring[i] = endstring[i];
        }
    }
    for (auto i : partition_tag)
    {
        if (partition_tag.find(i) == partition_tag.end())
        {
            continue;
        }

        auto t_map = Graph[i].second;
        for (auto key : DFA_key_set)
        {
            if (!t_map[key].empty())
            {
                int index = state_map[vectorToString(t_map[key])];

                if (index_map.find(index) != index_map.end())
                {
                    minimizeGraph[i][key] = index_map[index];
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

string DFA_graph::vectorToString(vector<int>& t)
{
    string res = "{";
    for (auto p : t)
    {
        res += to_string(p) + ",";
    }
    res += "}";
    return res;
}

string DFA_graph::setToString(set<int>& t)
{
    string res = "{";
    for (auto p : t)
    {
        res += to_string(p) + ",";
    }
    res += "}";
    return res;
}

string DFA_graph::generateCode() {
    string code = "";
    code += "#include<iostream>\n";
    code += "#include<utility>\n";
    code += "#include<fstream>\n";
    code += "#include<string>\n";
    code += "#include<map>\n";
    code += "using namespace std;\n";
    code += "int main() {\n";
    code += "    ifstream infile(\"sample.txt\");\n";
    code += "    map<int, string> endmap;\n";

    for (auto i : minendstring) {
        code += "    endmap[" + to_string(i.first) + "] = \"" + i.second + "\";\n";
    }

    code += "    int idx = 0;\n";
    code += "    string line;\n";
    code += "    string tokenstring;\n";
    code += "    while (std::getline(infile, line)) {\n";
    code += "        int state = " + to_string(start) + ";\n";
    code += "        idx = 0;\n";
    code += "        tokenstring = \"\";\n";

    code += "        while (state < " + to_string(minimizeGraph.size()) + " && idx < line.size()) {\n";
    code += "            tokenstring += line[idx];\n";  // 把当前字符加入tokenstring
    code += "            switch (state) {\n";

    for (int i = 0; i < minimizeGraph.size(); i++) {
        code += "                case " + to_string(i) + ":\n";
        code += "                    switch (line[idx]) {\n";
        for (auto item : minimizeGraph[i]) {
            if (item.second!=-1)
            {
                code += "                        case \'" + string(1, item.first) + "\':\n";
                code += "                            state = " + to_string(item.second) + ";\n";
                code += "                            break;\n";
            }
        }
        code += "                        default:\n";
        code += "                            state = " + to_string(minimizeGraph.size()) + ";\n";
        code += "                            break;\n";
        code += "                    }\n";
        code += "                    break;\n";
    }

    code += "                default:\n";
    code += "                    state = " + to_string(minimizeGraph.size()) + ";\n";
    code += "                    break;\n";
    code += "            }\n";
    code += "            idx++;\n";
    code += "        }\n";

    // 判断是否处于终止状态
    code += "        if (";
    int cnt = 0;
    for (int i : minimize_end) {
        code += "state == " + to_string(i);
        cnt++;
        if (cnt != minimize_end.size()) code += " || ";
    }
    code += ") {\n";
    code += "            cout << \"tokenstring: \" << tokenstring << \" type: \" << endmap[state] << endl;\n";
    code += "        } else {\n";
    code += "            cout << \"Invalid token: \" << tokenstring << endl;\n";
    code += "        }\n";
    code += "    }\n";
    code += "}\n";
    return code;
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

string DFA_graph::mapToString(const unordered_map<char, int>& mp) {
    string res;
    for (const auto& p : mp) {
        res += p.first;
        res += ':';
        res += to_string(p.second);
        res += " ";
    }
    return res;
}

pair<vector<int>, unordered_map<char, vector<int> > >& DFA_graph::operator[](int n)
{
    if (n < Graph.size())
    {
        return Graph[n];
    }
    else
    {
        Graph.resize(2 * n);
        return Graph[n];
    }
}



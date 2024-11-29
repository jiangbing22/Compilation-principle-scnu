// Copyright (c) 2024, 蒋昕玮
// 保留所有权利。
// 版本: 1.0
#include "DFA.h"
void DFA_graph::build_from_NFA(vector<NFA_graph> NFA) {
    // 合成总NFA
    unordered_map<int, string> total_NFA_endmap;
    for (auto& i : NFA) {
        total_NFA.contact(i);
        total_NFA.Graph[0]['$'].push_back(i.get_start());
        total_NFA_endmap[i.get_end()] = i.endtype;
    }
    cout << "total_end" << endl;
    this->DFA_key_set.clear();
    this->Graph.clear();
    this->end.clear();
    state_map.clear();
    queue<set<int>> state_queue;


    GRAPH nfa = total_NFA.get_graph();
    set<char> key_set = total_NFA.getkey();
    unordered_map<string, set<int>> closure_cache;

    auto BFS_Closure = [&](const set<int>& states) {
        string stateKey = setToString(states);
        if (closure_cache.find(stateKey) != closure_cache.end()) {
            return closure_cache[stateKey];
        }
        set<int> closure;
        unordered_map<int, bool> visited;
        queue<int> q;

        // 将所有初始状态放入队列并进行标记
        for (int state : states) {
            closure.insert(state);
            q.push(state);
            visited[state] = true;
        }

        // BFS 计算 closure
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            if (nfa[current].count('$')) { // 确保 '$' 转移存在
                for (int next : nfa[current]['$']) {
                    if (!visited[next]) {
                        closure.insert(next);
                        q.push(next);
                        visited[next] = true;
                    }
                }
            }
        }

        // 缓存结果
        closure_cache[stateKey] = closure;
        return closure;
    };

    set<int> startstate = BFS_Closure({0});
    state_queue.push(startstate);

    // 初始状态映射到 Graph 中的索引
    state_map[setToString(startstate)] = this->Graph.size();
    this->Graph.push_back({vector<int>(startstate.begin(), startstate.end()), {}});

    while (!state_queue.empty()) {
        set<int> current_state = state_queue.front();
        state_queue.pop();
        if (current_state.empty()) continue;

        string current_key = setToString(current_state);
        int current_index = state_map[current_key];

        // 遍历所有非 '$' 的 key
        for (char c : key_set) {
            if (c == '$') continue;
            this->DFA_key_set.insert(c);
            set<int> next_state;

            // 找到某个key的状态转移
            for (int i : current_state) {
                if (nfa[i].count(c)) {
                    next_state.insert(nfa[i][c].begin(), nfa[i][c].end());
                }
            }

            if (next_state.empty()) continue;

            // 计算状态闭包
            set<int> next_state_closure = BFS_Closure(next_state);
            string next_state_key = setToString(next_state_closure);

            // 如果新状态未映射，加入队列和映射
            if (state_map.find(next_state_key) == state_map.end()) {
                state_map[next_state_key] = this->Graph.size();
                state_queue.push(next_state_closure);
                this->Graph.push_back({vector<int>(next_state_closure.begin(), next_state_closure.end()), {}});
            }
            this->Graph[current_index].second[c] = vector<int>{next_state_closure.begin(),next_state_closure.end()};
        }
    }

    this->start = 0;

    // 处理终态
    for (auto& entry : state_map) {
        string key = entry.first;
        int state_index = entry.second;
        bool hasNonIdEnd = false;

        for (auto& end_info : total_NFA_endmap) {
            string subString = to_string(end_info.first);
            size_t position = key.find(subString);

            // 判断是否严格匹配
            if (position != string::npos) {
                bool isStrictMatch = (position == 0 || !isdigit(key[position - 1])) &&
                                     (position + subString.length() == key.length() || !isdigit(key[position + subString.length()]));

                if (isStrictMatch) {
                    // 检查是否有非 "id" 的终态
                    if (end_info.second != "ID") {
                        hasNonIdEnd = true;
                        this->end.insert(state_index);
                        endstring[state_index] = end_info.second;
                        break; // 一旦找到非 "id" 终态，立即停止循环
                    } else if (!hasNonIdEnd) {
                        // 仅在没有非 "id" 终态时考虑 "id" 终态
                        this->end.insert(state_index);
                        endstring[state_index] = end_info.second;
                    }
                }
            }
        }
    }
}



void DFA_graph::minimize()
{
    // 清空最小化图
    minimizeGraph.clear();
    // 清空最小化图的结束状态
    minimize_end.clear();

    // 获取当前图的结束状态集合
    set<int> end_set_index = this->end;
    // 获取非结束状态集合
    set<int> else_set_index;

    // 遍历状态映射，将结束状态添加到非结束状态集合中
    for (auto i : state_map)
    {
        if (this->end.find(i.second) != this->end.end())
        {
            else_set_index.insert(i.second);
        }
    }

    // 初始化分区图
    vector<map<char, string>> partition_graph;

    // 遍历当前图的每个状态
    for (auto state : this->Graph)
    {
        auto t_map = state.second;
        map<char, string> result;

        // 遍历DFA的键集
        for (auto key : DFA_key_set)
        {
            // 如果当前状态在key下的转移为空，则赋值为"-1"
            if (t_map[key].empty())
            {
                result[key] = "-1";
            }
            else
            {
                // 否则，将转移状态映射为字符串
                result[key] = to_string(state_map[vectorToString(t_map[key])]);
            }
        }
        // 将结果添加到分区图中
        partition_graph.push_back(result);
    }

    // 初始化状态映射表
    unordered_map<string, int> p_map;
    // 初始化分区标签集合
    set<int> partition_tag;
    // 初始化状态索引映射表
    unordered_map<int, int> index_map;

    // 遍历分区图
    for (int i = 0; i < partition_graph.size(); i++)
    {
        // 将分区图转换为字符串作为键
        string map_key = mapToString(partition_graph[i]);

        // 如果当前状态是结束状态，则在键后添加" end"和结束状态字符串
        if (end_set_index.find(i) != end_set_index.end())
        {
            map_key += " end";
            map_key += " " + endstring[i];
        }
        else
        {
            // 否则，在键后添加" else"
            map_key += " else";
        }

        // 如果当前键不在状态映射表中，则添加
        if (p_map.find(map_key) == p_map.end())
        {
            p_map[map_key] = i;
            // 将当前索引添加到分区标签集合中
            partition_tag.insert(i);
        }
        else
        {
            // 否则，将当前索引映射到已存在的键对应的索引
            index_map[i] = p_map[map_key];
        }
    }

    // 遍历结束状态集合
    for (auto i : end_set_index)
    {
        // 如果当前结束状态在索引映射表中有映射，则更新最小化图的结束状态和结束状态字符串
        if (index_map.find(i) != index_map.end())
        {
            minimize_end.insert(index_map[i]);
            minendstring[index_map[i]] = endstring[i];
        }
        else
        {
            // 否则，直接将当前结束状态添加到最小化图的结束状态中，并更新结束状态字符串
            minimize_end.insert(i);
            minendstring[i] = endstring[i];
        }
    }

    // 遍历分区标签集合
    for (auto i : partition_tag)
    {
        auto t_map = Graph[i].second;

        // 遍历DFA的键集
        for (auto key : DFA_key_set)
        {
            if (!t_map[key].empty())
            {
                // 获取转移状态的索引
                int index = state_map[vectorToString(t_map[key])];

                // 如果转移状态的索引在索引映射表中有映射，则更新最小化图中当前状态的转移
                if (index_map.find(index) != index_map.end())
                {
                    minimizeGraph[i][key] = index_map[index];
                }
                else
                {
                    // 否则，直接将转移状态的索引添加到最小化图中
                    minimizeGraph[i][key] = index;
                }
            }
            else
            {
                // 如果转移为空，则设置为-1
                minimizeGraph[i][key] = -1;
            }
        }
    }

    return;
}

string DFA_graph::vectorToString(vector<int>& t)
{
    string res = "";
    for (auto p : t)
    {
        res += to_string(p) + ",";
    }
    return res;
}

string DFA_graph::setToString(const set<int>& t)
{
    string res = "";
    for (auto p : t)
    {
        res += to_string(p) + ",";
    }
    return res;
}

string DFA_graph::generateCode() {
    string code;
    code += "#include<iostream>\n";
    code += "#include<utility>\n";
    code += "#include<fstream>\n";
    code += "#include<string>\n";
    code += "#include<map>\n";
    code += "#include<sstream>\n"; // 添加ostringstream的头文件
    code += "using namespace std;\n";
    code += "\n";
    code += "int main(int argc, char* argv[]) {\n";
    code += "    if (argc != 3) {\n";
    code += "        cerr << \"Usage: \" << argv[0] << \" <input_file> <output_file>\" << endl;\n";
    code += "        return 1;\n";
    code += "    }\n";
    code += "\n";
    code += "    ifstream infile(argv[1]);\n";
    code += "    ofstream outfile(argv[2]);\n";
    code += "    if (!infile || !outfile) {\n";
    code += "        cerr << \"Error opening file!\" << endl;\n";
    code += "        return 1;\n";
    code += "    }\n";
    code += "\n";
    code += "    map<int, string> endmap;\n";
    for (auto i : minendstring) {
        code += "    endmap[" + to_string(i.first) + "] = \"" + i.second + "\";\n";
    }
    code += "\n";

    // 读取所有行并用空格替换换行符
    code += "    string input;\n";
    code += "    ostringstream oss;\n";
    code += "    string line;\n";
    code += "    while (getline(infile, line)) {\n";
    code += "        oss << line << '\\n';\n"; // 用空格替换换行符
    code += "    }\n";
    code += "    input = oss.str();\n"; // 获取合并后的字符串
    code += "    int idx = 0;\n";
    code += "    string tokenstring;\n";
    code += "    while (idx < input.size()) {\n";
    code += "        while (idx < input.size() && isspace(input[idx])) {\n";
    code += "            idx++;\n";
    code += "        }\n";
    code += "        if(idx == input.size()){\n";
    code += "        break;\n";
    code += "        }\n";
    code += "        int laststate = -1;\n";
    code += "        int state = " + to_string(start) + ";\n";
    code += "        tokenstring = \"\";\n";
    code += "\n";
    code += "        while (state >= 0 && idx < input.size()) {\n";
    code += "            switch (state) {\n";

    for (int i = 0; i < minimizeGraph.size(); i++) {
        code += "                    case " + to_string(i) + ":\n";
        code += "                        switch (input[idx]) {\n";
        for (auto item : minimizeGraph[i]) {
            if (item.second != -1) {
                if(item.first!='\n'){
                code += "                            case \'" + string(1, item.first) + "\':\n";
                code += "                                state = " + to_string(item.second) + ";\n";
                code += "                                tokenstring += input[idx];\n";
                code += "                                break;\n";
                }
                else
                {
                    code += "                            case '\\n': \n";
                    code += "                                state = " + to_string(item.second) + ";\n";
                    code += "                                break;\n";
                }

            }
        }
        code += "                            default:\n";
        code += "                                laststate = state;\n";
        code += "                                state = -1;\n";
        code += "                                break;\n";
        code += "                        }\n";
        code += "                        break;\n";
    }
    code += "                    default:\n";
    code += "                        laststate = state;\n";
    code += "                        state = -1;\n";
    code += "                        break;\n";
    code += "                }\n";
    code += "                idx++;\n";
    code += "            }\n";
    code += "\n";
    code += "            if (state == -1) {\n";
    code += "                if (";
    int cnt = 0;
    for (int i : minimize_end) {
        code += "laststate == " + to_string(i);
        if (++cnt != minimize_end.size()) code += " || ";
    }
    code += ") {\n";
    code += "                    outfile <<\"\"<< endmap[laststate] << \" -> \" << tokenstring  << endl;\n";
    code += "                    idx--;\n";
    code += "                } else {\n";
    code += "                    outfile << \"Invalid token: \" << tokenstring << endl;\n";
    code += "                }\n";
    code += "            } else {\n";
    code += "                if (";
    cnt = 0;
    for (int i : minimize_end) {
        code += "state == " + to_string(i);
        if (++cnt != minimize_end.size()) code += " || ";
    }
    code += ") {\n";
    code += "                    outfile <<\"\"<< endmap[state] << \" -> \" << tokenstring  << endl;\n";
    code += "                } else {\n";
    code += "                    outfile << \"Invalid token: \" << tokenstring << endl;\n";
    code += "                }\n";
    code += "            }\n";
    code += "        }\n";
    code += "\n";
    code += "    infile.close();\n";
    code += "    outfile.close();\n";
    code += "    return 0;\n";
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

string DFA_graph::mapToString(const unordered_map<char, string>& mp) {
    string res;
    for (const auto& p : mp) {
        res += p.first;
        res += ':';
        res += p.second;
        res += " ";
    }
    return res;
}
string DFA_graph::mapToString(const map<char, string>& mp) {
    string res;
    for (const auto& p : mp) {
        res += p.first;
        res += ':';
        res += p.second;
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

void print_NFA(NFA_graph NFA)
{
    GRAPH result = NFA.get_graph();
    cout << "start:" << NFA.get_start() << " end:" << NFA.get_end() << endl;
    int count = 0;
    for (auto a : result)
    {
        cout << " node:" << count << " ";
        for (auto b : a)
        {
            char key = b.first;
            cout << "vertex: " << key << " ";
            cout << "arrive: ";
            for (auto c : a[key])
            {
                cout << c << " ";
            }
        }
        count++;
        cout << endl;
    }
    cout << "--------------------------------------------------------" << endl;
}

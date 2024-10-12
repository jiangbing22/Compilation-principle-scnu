#pragma once
#include"mutils.h"
#include"NFA.h"
#define DFA_GRAPH std::vector<pair<vector<int>,unordered_map<char,vector<int>>>>
class DFA_graph
{
public:
    void build_from_NFA(NFA_graph NFA);
    void minimize();
    int get_start() { return start; };
    set<int> get_end() { return end; };
    set<int> get_minimize_end() { return minimize_end; };
    DFA_GRAPH get_Graph() { return Graph; };
    size_t size() const
    {
        return Graph.size();
    }

    unordered_map<string, int> state_map;
    unordered_set<char> get_key() { return DFA_key_set; };
    unordered_map<int, unordered_map<char, int>> get_minimizeGraph() { return minimizeGraph; };
    string vectorToString(vector<int>& t);
    string setToString(set<int>& t);
private:
    int start;
    set<int> end;
    DFA_GRAPH Graph;
    set<int> minimize_end;
    unordered_map<int, unordered_map<char, int>> minimizeGraph;
    unordered_set<char> DFA_key_set;
    vector<int> stringToIntVector(string s);
    string mapToString(const unordered_map<char, int>& mp);
    pair<vector<int>, unordered_map<char, vector<int>>>& operator[](int n);
};
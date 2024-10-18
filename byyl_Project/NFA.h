#pragma once
#include"RE.h"
#define GRAPH std::vector<unordered_map<char, vector<int>>>

class NFA_graph
{
public:
    NFA_graph()
    {
        Graph.resize(1);
        start = end = 0;
    }
    void init(char a);
    string endtype;
    int size() const
    {
        return Graph.size();
    }
    unordered_map <char, vector<int>>& operator[](int n);

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
    unordered_set<char> calculator = { '*', '+', '?' , '|' ,'&','\\'};
};



#ifndef TO_DFA_H
#define TO_DFA_H
#include <unordered_map>
#include <stack>
#include <string>
#include<unordered_set>
#include<iostream>
#include<queue>
#include<vector>
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
    RE(){};
    void create(string initial)
    {
        re=initial;
        init();
        to_post();
    }
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
    unordered_map<char, vector<int>>& operator[](int n);
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

    unordered_map<string, int> state_map;//�жϼ����Ƿ��Ѿ�����
    unordered_set<char> get_key() { return DFA_key_set; };
    unordered_map<int, unordered_map<char, int>> get_minimizeGraph(){ return minimizeGraph; };
private:
    int start;
    set<int> end;
    DFA_GRAPH Graph;
    set<int> minimize_end;
    unordered_map<int,unordered_map<char,int>> minimizeGraph;
    unordered_set<char> DFA_key_set;
    string vectorToString(vector<int>& t);
    string setToString(set<int>& t);
    vector<int> stringToIntVector(string s);
    string mapToString(const unordered_map<char, int>& mp);
    pair<vector<int>,unordered_map<char, vector<int>>>& operator[](int n);
};
#endif // TO_DFA_H
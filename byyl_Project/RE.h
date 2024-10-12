#pragma once
#include "mutils.h"
using namespace std;
class RE {
public:
    RE(string initial) : re(initial) {
        initial.erase(remove(initial.begin(), initial.end(),' '), initial.end());
        rBracket();
        addConcat();
        toPost();
    };
    string get_post() { return re_post; };
    string get_re() { return re; };
private:
    unordered_map<char, int> prior = {
        {'*', 100}, {'+', 100}, {'?', 100}, {'|', 60}, {'&', 70}
    };
    unordered_set<char> calculator = {
    '*', '+', '?' , '|' ,'&','(',')','[',']'
    };
    string re;
    string re_post;
    void rBracket();
    void addConcat();
    void toPost();
};


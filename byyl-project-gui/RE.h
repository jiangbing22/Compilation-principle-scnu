#pragma once
#include "mutils.h"
#include<string>
using namespace std;
class RE {
public:
    RE(string initial) : re(initial) {

        initial = trim(initial);
        rBracket();
        addConcat();
        toPost();
    };
    string get_post() { return re_post; };
    string get_re() { return re; };
private:
    std::string trim(const std::string& str) {
        auto start = str.begin();
        while (start != str.end() && std::isspace(*start)) {
            ++start;
        }
        auto end = str.end();
        do {
            --end;
        } while (std::distance(start, end) > 0 && std::isspace(*end));

        return std::string(start, end + 1);
    }
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


#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<unordered_map>
#include<unordered_set>
struct grammarNode
{
    std::string left;
    std::vector<std::string> right;
    std::string right2str()
    {
        std::string result;
        for (auto i : right)
        {
            result += i ;
        }
        return result;
    }
};
class grammar
{
private:
    void createExG();
    void createFirst();
    void createFollow();

public:
    std::string first;
    grammar(const std::string filepath);
    std::unordered_map<std::string,std::unordered_set<std::string>> firstMap;
    std::unordered_map<std::string,std::unordered_set<std::string>> followMap;
    std::unordered_map<std::string, int> itemMap;
    std::unordered_map<std::string, bool> nullMap;
    std::unordered_set<std::string> unendSet;
    std::unordered_set<std::string> endSet;
    std::vector<grammarNode> G;
    std::vector<grammarNode> ex_G;
};

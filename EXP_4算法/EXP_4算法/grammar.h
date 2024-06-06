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
};
class grammar
{
private:
	void createExG();
	void createFirst();
	void createFollow();
	std::string first;
public:
	grammar(const std::string filepath);
	std::unordered_map<std::string,std::unordered_set<std::string>> firstMap;
	std::unordered_map<std::string,std::unordered_set<std::string>> followMap;
	std::unordered_map<std::string, bool> nullMap;
	std::unordered_set<std::string> unendSet;
	std::vector<grammarNode> G;
	std::vector<grammarNode> ex_G;
};
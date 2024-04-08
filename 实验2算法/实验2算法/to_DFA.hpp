#include <unordered_map>
#include "string"
#include"list"
#include "vector"

class RE
{
public:
	RE(string RE)


private:
	std::unordered_map<char, int> prior = {
{'*', 100}, {'+' , 100}, {'?' , 100}, {'.' , 80}, {'|' , 60}, {')' , 40}, {'(' , 20}
	};
	string re;
	string re_post;



};
class NFA
{
public:

private:

	std::vector<std::list<char>> NFA_graph;
	std::string re_post(std::string re);




};
class DFA
{
public:


private:
   



};
std::string NFA::re_post(std::string re)
{

}


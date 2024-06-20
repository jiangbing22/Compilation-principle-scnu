#include"LALR.h"
#include<iostream>
int main()
{
	grammar gra("grammar.txt");
	for (auto i : gra.ex_G)
	{
		std::cout << i.left<<"->";
		for (auto j : i.right)
		{
			std:: cout << j << " ";
		}
		std::cout << "\n";
		
	}
	grammar g("grammar.txt");

	// ����firstMap����ӡÿ�����ս�������Ӧ��FIRST����
	std::cout << "FIRST���ϣ�" << std::endl;
	for (const auto& entry : g.firstMap) {
		const std::string& nonTerminal = entry.first;
		const std::unordered_set<std::string>& firstSet = entry.second;

		std::cout << "FIRST(" << nonTerminal << ") = { ";
		for (const auto& symbol : firstSet) {
			std::cout << symbol << " ";
		}
		std::cout << "}" << std::endl;
	}
	std::cout << "FOLLOW���ϣ�" << std::endl;
	for (const auto& entry : g.followMap) {
		const std::string& nonTerminal = entry.first;
		const std::unordered_set<std::string>& followSet = entry.second;

		std::cout << "FOLLOW(" << nonTerminal << ") = { ";
		for (const auto& symbol : followSet) {
			std::cout << symbol << " ";
		}
		std::cout << "}" << std::endl;
	}
	LALR lalr("grammar.txt");
	return 0;


}
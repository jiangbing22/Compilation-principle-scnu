#include"grammar.h"
#include<iostream>
int main()
{
	grammar gra("grammar.txt");
	for (auto i : gra.G)
	{
		std::cout << i.left<<"->";
		for (auto j : i.right)
		{
			std:: cout << j << " ";
		}
		std::cout << "\n";
		
	}

}
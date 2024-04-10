#include"to_DFA.hpp"
#include<iostream>
using namespace std;
int main()
{
	string init;
	cin >> init;
	RE temp(init);
	cout << temp.get_re() << endl;
	cout << temp.get_post();

}
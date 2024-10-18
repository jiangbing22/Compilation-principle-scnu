#include"DFA.h"

void print_NFA(NFA_graph NFA)
{
	GRAPH result = NFA.get_graph();
	cout << "start:" << NFA.get_start() << " end:" << NFA.get_end() << endl;
	int count = 0;
	for (auto a : result)
	{
		cout << " node:" << count << " ";
		for (auto b : a)
		{
			char key = b.first;
			cout << "vertex: " << key << " ";
			cout << "arrive: ";
			for (auto c : a[key])
			{
				cout << c << " ";
			}
		}
		count++;
		cout << endl;
	}
}
void print_DFA(DFA_graph DFA)
{
	DFA_GRAPH result = DFA.get_Graph();
	cout << "state_graph:  ";
	for (auto i : DFA.state_map)
	{
		for (auto j : i.first)
		{
			cout << j << " ";
		}
		cout << i.second << endl;
	}



	cout << "start:" << DFA.get_start() << " end:";
	for (auto i : DFA.get_end())
	{
		cout << i << " ";
	}
	cout << endl;
	int count = 0;
	for (auto a : result)
	{
		cout << " node:" << count << " ";
		cout << "numbers: ";
		for (auto b : a.first)
		{
			cout << b << " ";
		}
		for (auto c : a.second)
		{
			cout << "vertex:" << c.first << "   ";
			cout << "arrive:  ";
			for (auto c : a.second[c.first])
			{
				cout << c << " ";
			}
		}
		count++;
		cout << endl;
	}

}
void print_minimize(DFA_graph DFA)
{
	auto result = DFA.get_minimizeGraph();
	cout << "state_graph:  ";
	cout << "start:" << 0 << " end:";
	for (auto a : DFA.get_minimize_end())
	{
		cout << a << " ";
	}
	cout << endl;
	for (auto i : result)
	{
		if (i.second.empty())
		{
			continue;
		}
		cout << "node:" << i.first << " ";
		for (auto j : i.second)
		{
			cout << " vertex: " << j.first << " ";
			cout << "arrive: ";

			cout << j.second << " ";

		}
		cout << endl;
	}
}
int main()
{
	string init;
	getline(std::cin, init);
	RE temp(init);
	cout << "regex:" << temp.get_re() << endl;
	cout << "regex_post:" << temp.get_post() << endl;
	NFA_graph NFA;
	DFA_graph DFA;
	NFA.build_NFA(temp);
	print_NFA(NFA);
	cout << "-------------------------" << endl;
	DFA.build_from_NFA(NFA);
	print_DFA(DFA);
	cout << "-------------------------" << endl;
	DFA.minimize();
	print_minimize(DFA);
	cout << "-------------------------" << endl;
	cout << DFA.generateCode();


}
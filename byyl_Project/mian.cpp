#include"DFA.h"


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
	int num;
	cin >> num;
	vector<NFA_graph> NFAs;
	string init;
	for (int i = 0; i < num; i++)
	{
		cin >> init;
		cout << init;
		NFA_graph NFA;
		cin>>NFA.endtype;
		RE temp(init);
		cout << "regex:" << temp.get_re() << endl;
		cout << "regex_post:" << temp.get_post() << endl;

		NFA.build_NFA(temp);

		print_NFA(NFA);
		cout << "-------------------------" << endl;
		NFAs.push_back(NFA);
	}
	DFA_graph DFA;


	DFA.build_from_NFA(NFAs);
	print_NFA(DFA.total_NFA);
	cout << "-------------------------" << endl;
	print_DFA(DFA);
	cout << "-------------------------" << endl;
	DFA.minimize();
	print_minimize(DFA);
	cout << "-------------------------" << endl;
	cout << DFA.generateCode();


}
#include "parser.h"
#include"iostream"
int main()
{
	scaner c;
	scaner t;
	parser p;
	c.setsource("test.txt");
	t.setsource("test.txt");
	auto token = c.getToken();
	printToken(token, c.gettokenstring(), c);
	while (token != ENDFILE)
	{
		token = c.getToken();
		printToken(token, c.gettokenstring(), c);
	}
	p.parse(t);
	p.printTree();
	
	return 0;
}
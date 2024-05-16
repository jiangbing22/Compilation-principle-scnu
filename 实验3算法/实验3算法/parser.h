#pragma once
#include"scaner.h"
class parser
{
public:
	void parse(scaner &s);
	void printTree()
	{
		preOrderTraversal(parseroot);
	}
private:
	TreeNode* parseroot;
	TokenType token;
	char tokenString[MAXTOKENLEN+1];
	void match(TokenType expecte,scaner &s);
	void tokenError(scaner &s);
	void preOrderTraversal(TreeNode* node);
	
	TreeNode* stmt_sequence(scaner& s);
	TreeNode* statement(scaner& s);
	TreeNode* if_stmt(scaner& s);
	TreeNode* repeat_stmt(scaner& s);
	TreeNode* assign_stmt(scaner& s);
	TreeNode* read_stmt(scaner& s);
	TreeNode* write_stmt(scaner& s);
	TreeNode* regex_stmt(scaner& s);
	TreeNode* while_stmt(scaner& s);
	TreeNode* for_stmt(scaner& s);

	TreeNode* exp(scaner& s);
	TreeNode* simple_exp(scaner& s);
	TreeNode* term(scaner& s);
	TreeNode* powernum(scaner& s);
	TreeNode* factor(scaner& s);
	TreeNode* self_term(scaner& s);

	TreeNode* regex(scaner& s);
	TreeNode* concat(scaner& s);
	TreeNode* re_factor(scaner& s);
	TreeNode* re_term(scaner& s);

	
	TreeNode* repetition(scaner& s);
	TreeNode* reclass(scaner& s);
	TreeNode* rerange(scaner& s);

};


#pragma once
#include "global.h"
#define BUFLEN 256
#define MAXTOKENLEN 40
#define MAXREVERVEDWORDLEN 11
class scaner
{

public:
	scaner() {};
	void initial(int lineno, FILE* source, FILE* listing, FILE* code);
    TokenType getToken(void); /* end getToken */

	friend void printToken(TokenType token, const char* tokenString, scaner s);
	friend TreeNode* newStmtNode(StmtKind kind, scaner s);
	friend TreeNode* newExpNode(ExpKind kind, scaner s);
	friend char* copyString(const char* s, scaner c);
	friend void printSpaces(scaner c);


	void setsource(const char* s);
	void setlisting(const char* s);
	void setcode(const char* s);

	const char* gettokenstring() { return tokenString; };
	int getlineno() { return lineno; };
    FILE* listing = stdout;
    FILE* source=nullptr;

private:
	bool isregex = FALSE;
	int lineno;
	FILE* code=nullptr;
	std::unordered_set<char> reSymbols = {
	'|', '&', '(', ')', '?', '*', '+', '.', '\\','#','[',']','-'
	};
	bool isreSymbols(char c);
	/* EchoSource = TRUE causes the source program to
 * be echoed to the listing file with line numbers
 * during parsing
 */
	int EchoSource;
	/* TraceScan = TRUE causes token information to be
	 * printed to the listing file as each token is
	 * recognized by the scanner
	 */
	int TraceScan;
	/* TraceParse = TRUE causes the syntax tree to be
	 * printed to the listing file in linearized form
	 * (using indents for children)
	 */
	int TraceParse;

	/* TraceAnalyze = TRUE causes symbol table inserts
	 * and lookups to be reported to the listing file
	 */
	int TraceAnalyze;

	/* TraceCode = TRUE causes comments to be written
	 * to the TM code file as code is generated
	 */
	int TraceCode;

	/* Error = TRUE prevents further passes if an error occurs */
	int Error;
	typedef enum
	{
		START, INASSIGN, INCOMMENT, INNUM, INID, DONE, INREGEX, INREGEXEQ, INLT, INGT, INPLUS, INMINUS,INRECHAR
	}
	StateType;
	struct
	{
		char str[MAXREVERVEDWORDLEN+1];
		TokenType tok;
	} reservedWords[MAXRESERVED]
		= { {"if",IF},{"then",THEN},{"else",ELSE},{"end",END},
		   {"repeat",REPEAT},{"until",UNTIL},{"read",READ},
            {"write",WRITE},{"while",WHILE},{"endwhile",ENDWHILE},{"for",FOR} };
	/* lexeme of identifier or reserved word */
	char tokenString[MAXTOKENLEN + 1];
	char lineBuf[BUFLEN]; /* holds the current line */
	int linepos = 0; /* current position in LineBuf */
	int bufsize = 0; /* current size of buffer string */
	int EOF_flag = FALSE; /* corrects ungetNextChar behavior on EOF */
    int getNextChar(void);
	void ungetNextChar(void);
	TokenType reservedLookup(char* s);
};


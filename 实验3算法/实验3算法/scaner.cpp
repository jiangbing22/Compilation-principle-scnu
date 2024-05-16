#include "scaner.h"
#define _CRT_SECURE_NO_WARNINGS
/* corrects ungetNextChar behavior on EOF */

TokenType scaner::getToken(void)
{  /* index for storing into tokenString */
    int tokenStringIndex = 0;
    /* holds current token to be returned */
    TokenType currentToken;
    /* current state - always begins at START */
    StateType state = START;
    /* flag to indicate save to tokenString */
    int save;
    while (state != DONE)
    {
        int c = getNextChar();
        save = TRUE;
        if (!isregex)
        {
            switch (state)
            {
            case START:
                if (isdigit(c))
                    state = INNUM;
                else if (isalpha(c))
                    state = INID;
                else if (c == ':')
                    state = INASSIGN;
                else if ((c == ' ') || (c == '\t') || (c == '\n'))
                    save = FALSE;
                else if (c == '{')
                {
                    save = FALSE;
                    state = INCOMMENT;
                }
                //����������ʽ��ֵ״̬.
                else if (c == '=')
                {
                    state = INREGEXEQ;
                }
                else if (c == '$')
                {
                    state = INREGEX;
                }
                //������ַ������״̬
                else if (c == '+')
                {
                    state = INPLUS;
                }
                else if (c == '-')
                {
                    state = INMINUS;
                }
                else if (c == '<')
                {
                    state = INLT;
                }
                else if (c == '>')
                {
                    state = INGT;
                }
                else
                {
                    state = DONE;
                    switch (c)
                    {
                    case EOF:
                        save = FALSE;
                        currentToken = ENDFILE;
                        break;
                        // case '=':
                        //   currentToken = EQ;
                        // break;
                        // case '<':
                        //   currentToken = LT;
                        //   break;
                        // case '+':
                        //   currentToken = PLUS;
                        //   break;
                        // case '-':
                        //   currentToken = MINUS;
                        // break;
                    case '^'://���������
                        currentToken = POWER;
                        break;
                    case '%'://���������
                        currentToken = MOD;
                        break;
                    case '*':
                        currentToken = TIMES;
                        break;
                    case '/':
                        currentToken = OVER;
                        break;
                    case '(':
                        currentToken = LPAREN;
                        break;
                    case ')':
                        currentToken = RPAREN;
                        break;
                    case ';':
                        currentToken = SEMI;
                        break;
                    default:
                        currentToken = ERROR;
                        break;
                    }
                }
                break;
            case INCOMMENT:
                save = FALSE;
                if (c == EOF)
                {
                    state = DONE;
                    currentToken = ENDFILE;
                }
                else if (c == '}') state = START;
                break;
            case INASSIGN:
                state = DONE;
                if (c == '=')
                    currentToken = ASSIGN;
                else
                { /* backup in the input */
                    ungetNextChar();
                    save = FALSE;
                    currentToken = ERROR;
                }
                break;
            case INNUM:
                if (!isdigit(c))
                { /* backup in the input */
                    ungetNextChar();
                    save = FALSE;
                    state = DONE;
                    currentToken = NUM;
                }
                break;
            case INID:
                if (!isalpha(c))
                { /* backup in the input */
                    ungetNextChar();
                    save = FALSE;
                    state = DONE;
                    currentToken = ID;
                }
                break;
            case INREGEXEQ://����������ʽ��ֵ״̬
                if (c == '=')
                {
                    state = DONE;
                    currentToken = RE_EQ;
                }
                else
                {
                    ungetNextChar();
                    save = FALSE;
                    state = DONE;
                    currentToken = EQ;
                }
                break;
            case INREGEX://����������ʽ״̬
                ungetNextChar();
                isregex = TRUE;
                state = DONE;
                currentToken = DOLLAR;
                break;
                //�������������״̬
            case INPLUS:
                if (c == '+')
                {
                    state = DONE;
                    currentToken = INCREMENT;
                }
                else
                {
                    ungetNextChar();
                    save = FALSE;
                    state = DONE;
                    currentToken = PLUS;
                }
                break;
            case INMINUS:
                if (c == '-')
                {
                    state = DONE;
                    currentToken = DECREMENT;
                }
                else
                {
                    ungetNextChar();
                    save = FALSE;
                    state = DONE;
                    currentToken = MINUS;
                }
                break;
            case INLT:
                if (c == '=')
                {
                    state = DONE;
                    currentToken = LT_EQ;
                }
                else if (c == '>')
                {
                    state = DONE;
                    currentToken = NOT_EQ;
                }
                else
                {
                    ungetNextChar();
                    save = FALSE;
                    state = DONE;
                    currentToken = LT;
                }
                break;
            case INGT:
                if (c == '=')
                {
                    state = DONE;
                    currentToken = GT_EQ;
                }
                else
                {
                    ungetNextChar();
                    save = FALSE;
                    state = DONE;
                    currentToken = GT;
                }
                break;

            case DONE:
            default: /* should never happen */
                fprintf(listing, "Scanner Bug: state= %d\n", state);
                state = DONE;
                currentToken = ERROR;
                break;
            }
        }
        else
        {
            switch (state)
            {
            case START:
                if (c == '$')
                {
                    isregex = FALSE;
                    currentToken = DOLLAR;
                    state = DONE;
                }
                else if (!isreSymbols(c))
                {
                    state = DONE;
                    currentToken = RECHAR;
                }
                else if ((c == ' ') || (c == '\t') || (c == '\n'))
                {
                    save = FALSE;
                }
                else
                {
                    state = DONE;
                    switch (c)
                    {
                    case '#'://���������
                        currentToken = CLOSURE;
                        break;
                    case '|'://���������
                        currentToken = OR;
                        break;
                    case '&':
                        currentToken = AND;
                        break;
                    case '?':
                        currentToken = OPTIONAL;
                        break;
                    case '(':
                        currentToken = LPAREN;
                        break;
                    case ')':
                        currentToken = RPAREN;
                        break;
                    case '[':
                        currentToken = LBRACKET;
                        break;
                    case ']':
                        currentToken = RBRACKET;
                        break;
                    case '.':
                        currentToken = ANYCHAR;
                        break;
                    case '-':
                        currentToken = RANGE;
                        break;
                    default:
                        currentToken = ERROR;
                        break;
                    }
                }
                break;
            case INRECHAR:
                if (isreSymbols(c))
                {
                    ungetNextChar();
                    save = FALSE;
                    state = DONE;
                    currentToken = RECHAR;
                }
                break;
            case DONE:
                
            
                

            default:
                fprintf(listing, "Scanner Bug: state= %d\n", state);
                state = DONE;
                currentToken = ERROR;
                break;
            }

        }
        if ((save) && (tokenStringIndex <= MAXTOKENLEN)) 
        {
            tokenString[tokenStringIndex++] = (char)c;
        }
        if (state == DONE)
        {
           tokenString[tokenStringIndex] = '\0';
           if (currentToken == ID)
           {
               currentToken = reservedLookup(tokenString);
           }
        }
        
    }
    if (TraceScan) {
        fprintf(listing, "\t%d: ", lineno);
        printToken(currentToken, tokenString,*this);
    }
    return currentToken;
}

void scaner::setsource(const char* s)
{
    fopen_s(&source,s, "r");
    if (source == nullptr) {
        perror("Error opening source");
        return;
    }
}

void scaner::setlisting(const char* s)
{
    fopen_s(&listing,s, "r");
    if (listing == nullptr) {
        perror("Error opening listing");
        return;
    }
}

void scaner::setcode(const char* s)
{
    fopen_s(&code,s, "r");
    if (code == nullptr) {
        perror("Error opening code");
        return;
    }
}

bool scaner::isreSymbols(char c)
{
    if (reSymbols.find(c) != reSymbols.end())
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int scaner::getNextChar(void)
{
    if (!(linepos < bufsize))
    {
        lineno++;
        if (fgets(lineBuf, BUFLEN - 1, source))
        {
            if (EchoSource) fprintf(listing, "%4d: %s", lineno, lineBuf);
            bufsize = strlen(lineBuf);
            linepos = 0;
            return lineBuf[linepos++]; 
        }
        else
        {
            EOF_flag = TRUE;
            return EOF;
        }
    }
    else return lineBuf[linepos++];
}

void scaner::ungetNextChar(void)
{
    if (!EOF_flag) linepos--;
}

TokenType scaner::reservedLookup(char* s)
{
    int i;
    for (i = 0; i < MAXRESERVED; i++)
        if (!strcmp(s, reservedWords[i].str))
            return reservedWords[i].tok;
    return ID;
}

void printToken(TokenType token, const char* tokenString,scaner s) {
    FILE* listing = s.listing;
    switch (token) {
        // ������
    case IF:
    case THEN:
    case ELSE:
    case END:
    case REPEAT:
    case UNTIL:
    case READ:
    case WRITE:
    case WHILE:
    case ENDWHILE:
    case FOR:
    case TO:
    case DOWNTO:
        fprintf(listing, "Reserved word: %s\n", tokenString);
        break;
        // ��ֵ����
    case ASSIGN:
        fprintf(listing, ":=\n");
        break;
        // �Ƚ������
    case EQ:
        fprintf(listing, "=\n");
        break;
    case LT:
        fprintf(listing, "<\n");
        break;
    case LT_EQ:
        fprintf(listing, "<=\n");
        break;
    case GT:
        fprintf(listing, ">\n");
        break;
    case GT_EQ:
        fprintf(listing, ">=\n");
        break;
    case NOT_EQ:
        fprintf(listing, "<>\n");
        break;
        // ���������
    case PLUS:
        fprintf(listing, "+\n");
        break;
    case MINUS:
        fprintf(listing, "-\n");
        break;
    case TIMES:
        fprintf(listing, "*\n");
        break;
    case OVER:
        fprintf(listing, "/\n");
        break;
    case MOD:
        fprintf(listing, "%%\n"); // ʹ�������ٷֺ�����ʾһ���ٷֺ�
        break;
    case POWER:
        fprintf(listing, "^\n");
        break;
        // �߼������
    case OR:
        fprintf(listing, "or (|)\n");
        break;
    case AND:
        fprintf(listing, "and (&)\n");
        break;
        // ������ʽ���
    case RANGE:
        fprintf(listing, "char range  (-)\n");
        break;
    case RE_EQ:
        fprintf(listing, "regex equal (==)\n");
        break;
    case RECHAR:
        fprintf(listing, "regex character: %s\n",tokenString);
        break;
    case CLOSURE:
        fprintf(listing, "closure (#)\n");
        break;
    case OPTIONAL:
        fprintf(listing, "optional (?)\n");
        break;
    case DOLLAR:
        fprintf(listing, "end of line ($)\n");
        break;
    case LBRACKET:
        fprintf(listing, "left bracket ([)\n");
        break;
    case RBRACKET:
        fprintf(listing, "right bracket (])\n");
        break;
    case ANYCHAR:
        fprintf(listing, "any character (.)\n");
        break;
        // ��������
    case LPAREN:
        fprintf(listing, "Left Parenthesis (\n");
        break;
    case RPAREN:
        fprintf(listing, "Right Parenthesis )\n");
        break;
    case SEMI:
        fprintf(listing, "Semicolon (;)\n");
        break;
        // �����ͼ��������
    case INCREMENT:
        fprintf(listing, "Increment (++)\n");
        break;
    case DECREMENT:
        fprintf(listing, "Decrement (--)\n");
        break;
        // �ļ�����
    case ENDFILE:
        fprintf(listing, "End of File\n");
        break;
        // ������
    case ERROR:
        fprintf(listing, "Error: %s\n", tokenString);
        break;
        // ��ʶ��������
    case ID:
        fprintf(listing, "Identifier: %s\n", tokenString);
        break;
    case NUM:
        fprintf(listing, "Number: %s\n", tokenString);
        break;
        // Ĭ�����
    default:
        fprintf(listing, "Unknown token: %d\n", token);
    }
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode* newStmtNode(StmtKind kind, scaner s)
{
    FILE* listing = s.listing;
    int lineno = s.lineno;
    TreeNode* t = new TreeNode;
    int i;
    if (t == NULL)
        fprintf(listing, "Out of memory error at line %d\n", lineno);
    else {
        for (i = 0; i < MAXCHILDREN; i++) t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = StmtK;
        t->kind.stmt = kind;
        t->lineno = lineno;
    }
    return t;
}

/* Function newExpNode creates a new expression
 * node for syntax tree construction
 */
TreeNode* newExpNode(ExpKind kind, scaner s)
{
    FILE* listing = s.listing;
    int lineno = s.lineno;
    TreeNode* t = new TreeNode;
    int i;
    if (t == NULL)
        fprintf(listing, "Out of memory error at line %d\n", lineno);
    else {
        for (i = 0; i < MAXCHILDREN; i++) t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = ExpK;
        t->kind.exp = kind;
        t->lineno = lineno;
        t->type = Void;
    }
    return t;
}
/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char* copyString(const char* s, scaner c)
{
    FILE* listing = c.listing;
    int lineno = c.lineno;
    int n;
    char* t;
    if (s == NULL) return NULL;
    n = strlen(s) + 1;
    t = new char[n];
    if (t == NULL)
        fprintf(listing, "Out of memory error at line %d\n", lineno);
    else strcpy_s(t,n,s);
    return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
void printSpaces(scaner c)
{
    FILE* listing = c.listing;
    int i;
    for (i = 0; i < indentno; i++)
        fprintf(listing, " ");
}

/* procedure printTree prints a syntax tree to the
 * listing file using indentation to indicate subtrees
 */
 //void printTree(TreeNode* tree)
 //{
 //    int i;
 //    INDENT;
 //    while (tree != NULL) {
 //        printSpaces();
 //        if (tree->nodekind == StmtK)
 //        {
 //            switch (tree->kind.stmt) {
 //            case IfK:
 //                fprintf(listing, "If\n");
 //                break;
 //            case RepeatK:
 //                fprintf(listing, "Repeat\n");
 //                break;
 //            case AssignK:
 //                fprintf(listing, "Assign to: %s\n", tree->attr.name);
 //                break;
 //            case ReadK:
 //                fprintf(listing, "Read: %s\n", tree->attr.name);
 //                break;
 //            case WriteK:
 //                fprintf(listing, "Write\n");
 //                break;
 //            default:
 //                fprintf(listing, "Unknown ExpNode kind\n");
 //                break;
 //            }
 //        }
 //        else if (tree->nodekind == ExpK)
 //        {
 //            switch (tree->kind.exp) {
 //            case OpK:
 //                fprintf(listing, "Op: ");
 //                printToken(tree->attr.op, "\0");
 //                break;
 //            case ConstK:
 //                fprintf(listing, "Const: %d\n", tree->attr.val);
 //                break;
 //            case IdK:
 //                fprintf(listing, "Id: %s\n", tree->attr.name);
 //                break;
 //            default:
 //                fprintf(listing, "Unknown ExpNode kind\n");
 //                break;
 //            }
 //        }
 //        else fprintf(listing, "Unknown node kind\n");
 //        for (i = 0; i < MAXCHILDREN; i++)
 //            printTree(tree->child[i]);
 //        tree = tree->sibling;
 //    }
 //    UNINDENT;
 //}

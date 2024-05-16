#include "parser.h"
#include<iostream>
#include<QDebug>
TreeNode* parser::parse(scaner &s)
{
  
    token = s.getToken(); // ��ȡ��һ���ʷ���Ԫ
    parseroot = stmt_sequence(s); // ����������У������ֵ��t
    if (token != ENDFILE) // �����ǰ�ʷ���Ԫ�����ļ�������־
    {
        std::cout<<"Code ends before file\n"; // �����﷨����
    }
    return parseroot;
}

void parser::preOrderTraversal(const TreeNode* node) {
    if (node == NULL) {
        return;
    }
    // ���ʵ�ǰ�ڵ�
    // ������Ը�����Ҫ���д��������ӡ�ڵ���Ϣ���������������
    printf("Node - Line: %d, Kind: %d, ", node->lineno, node->nodekind);
    if (node->nodekind == StmtK) {
        // ��������ڵ㣬��ӡ�������
        printf("Stmt Kind: %d\n", node->kind.stmt);
    }
    else if (node->nodekind == ExpK) {
        // ����Ǳ��ʽ�ڵ㣬��ӡ���ʽ����
        printf("Exp Kind: %d, ", node->kind.exp);
        if (node->kind.exp == IdK ) {
            // ����Ǳ�ʶ����������ӡ������Ϣ
            printf("Value: %s\n", node->attr.name);
        }
        else if (node->kind.exp == OpK) {
            // ����ǲ���������ӡ����������
            printf("Operator: %d\n", node->attr.op);
        }
        else if (node->kind.exp == RecK) {
            // �����������ʽ
            printf("rechar: %s\n", node->attr.name);
        }
        else if (node->kind.exp == ConstK)
        {
            printf("Value: %d\n", node->attr.val);
        }
    }

    // �ݹ�ر��������ӽڵ�
    for (int i = 0; i < MAXCHILDREN && node->child[i] != NULL; i++) {
        preOrderTraversal(node->child[i]);
    }

    // ��������ֵܽڵ㣬��������
    if (node->sibling != NULL) {
        preOrderTraversal(node->sibling);
    }
}

void parser::match(TokenType expected,scaner &s)
{
    if (token == expected)
    {
        token = s.getToken();
        strcpy_s(tokenString,MAXTOKENLEN+1,s.gettokenstring());
    }
    else
    {
        tokenError(s);
    }
}
void parser::tokenError(scaner &s)
{
    FILE* listing = s.listing;
    fprintf(listing, "tokenError: tokenstring: %s lineno: %d\n",s.gettokenstring(), s.getlineno());
    //std::cout << "tokenError: tokenstring:" <<std::string(tokenString)<<"lineno:" <<s.getlineno()<< std::endl;
}

TreeNode* parser::stmt_sequence(scaner& s)
{
    TreeNode* t = statement(s); // ���Խ���һ����䣬���������ֵ��t
    TreeNode* p = t; // ��t��ֵ����p�����ڹ����������
    while ((token != ENDFILE) && (token != RPAREN) &&
        (token != ELSE) && (token != UNTIL)&&token!=ENDWHILE) // �������ļ�������)��ELSE��UNTILʱ
    {
        TreeNode* q; // ����һ����ʱTreeNodeָ��q
        match(SEMI,s); // ƥ��ֺţ���ʾ������
        q = statement(s); // �ٴγ��Խ���һ����䣬���������ֵ��q
        if (q != NULL) // ���q����NULL
        {
            if (t == NULL) t = p = q; // ���t��NULL��˵�����ǵ�һ����䣬��q��ֵ��t��p
            else // ����˵��t����NULL����ǰ���Ѿ��������
            {
                p->sibling = q; // ����ǰ���p���ֵ�ָ��ָ�������q
                p = q; // ��p�ƶ�����һ�����q
            }
        }
    }
    return t; // ���ص�һ������ָ��t
}

TreeNode* parser::statement(scaner& s)
{
    TreeNode* t = NULL; // ��ʼ�����ڵ�tΪNULL
    switch (token) // ���ݵ�ǰ�ʷ���Ԫ������
    {
    case IF: t = if_stmt(s); break; // �����IF�������������
    case REPEAT: t = repeat_stmt(s); break; // �����REPEAT������ѭ�����
    case ID: t = assign_stmt(s); break; // �����ID�������Ǹ�ֵ���
    case READ: t = read_stmt(s); break; // �����READ�����������
    case WRITE: t = write_stmt(s); break; // �����WRITE������д���
    case WHILE: t = while_stmt(s); break;
    case FOR: t = for_stmt(s); break;
    case ANYCHAR : t = regex_stmt(s); break;
    default: 
        tokenError(s); // ��ӡ��ǰ�ʷ���Ԫ
        token = s.getToken(); // ��ȡ��һ���ʷ���Ԫ
        break;
    } /* end case */
    return t; // ���ؽ��������ڵ�t
}

TreeNode* parser::if_stmt(scaner& s)
{
    TreeNode* t = newStmtNode(IfK,s); // ����һ���µ�IF���ڵ�
    match(IF,s); // ƥ��IF
    match(LPAREN, s);
    if (t != NULL) t->child[0] = exp(s); // ���t��Ϊ�գ��������ʽ��ΪIF��������
    match(RPAREN,s);
    match(LPAREN, s);
    qDebug()<<tokenString<<token;
    if (t != NULL) t->child[1] = stmt_sequence(s); // ���t��Ϊ�գ��������������ΪIF�������֧
    if (token == ELSE) // �����һ���ʷ���Ԫ��ELSE
    {
        match(ELSE,s); // ƥ��ELSE
        if (t != NULL) t->child[2] = stmt_sequence(s); // ���t��Ϊ�գ��������������ΪIF���ļٷ�֧
    }
    match(RPAREN,s); // ƥ��END
    return t; // ����IF���ڵ�t
}

TreeNode* parser::repeat_stmt(scaner& s)
{
    TreeNode* t = newStmtNode(RepeatK,s); // ����һ���µ�REPEAT���ڵ�
    match(REPEAT,s); // ƥ��REPEAT
    if (t != NULL) t->child[0] = stmt_sequence(s); // ���t��Ϊ�գ��������������ΪREPEAT����ѭ����
    match(UNTIL,s); // ƥ��UNTIL
    if (t != NULL) t->child[1] = exp(s); // ���t��Ϊ�գ��������ʽ��ΪREPEAT������ֹ����
    return t; // ����REPEAT���ڵ�t
}

TreeNode* parser::assign_stmt(scaner& s)
{
    TreeNode* t = newStmtNode(AssignK,s); // ����һ���µĸ�ֵ���ڵ�
    TreeNode* p = newExpNode(IdK,s);
    if ((p != NULL) && (token == ID)) // ���t��Ϊ���ҵ�ǰ�ʷ���Ԫ��ID
        p->attr.name = copyString(tokenString,s); // ����ID���ַ�������ֵ����������
    match(ID,s); // ƥ��ID
    match(ASSIGN,s); // ƥ�丳ֵ����ASSIGN
    if (t != NULL) t->child[0] = p; // ���t��Ϊ�գ��������ʽ��Ϊ��ֵ����ֵ
    if (t != NULL) t->child[1] = exp(s);
    return t; // ���ظ�ֵ���ڵ�t
}

TreeNode* parser::read_stmt(scaner& s)
{
    TreeNode* t = newStmtNode(ReadK,s);
    TreeNode* p = newExpNode(IdK,s);
    match(READ, s);
    if ((t != nullptr) && (token== ID)) {
        p->attr.name = copyString(tokenString,s);
        t->child[0]=p;
    }
    match(ID,s);
    return t;
}

TreeNode* parser::write_stmt(scaner& s)
{
    TreeNode* t = newStmtNode(WriteK,s);
    match(WRITE,s);
    if (t != nullptr) t->child[0] = exp(s);
    return t;
}

TreeNode* parser::regex_stmt(scaner& s)
{
    TreeNode* stmtNode = newStmtNode(RegexK, s);
    TreeNode* IDNode = newExpNode(IdK, s);
    match(ANYCHAR, s); // ƥ�俪ͷ�� .
    IDNode->attr.name = copyString(tokenString, s);
    match(ID, s); 
    match(RE_EQ, s); // ƥ�� '==' �еĵ�һ���Ⱥ�
    TreeNode* regexTree = regex(s); // ����������ʽ�������﷨��
    if (stmtNode != nullptr) {
        stmtNode->child[0] = IDNode;
        stmtNode->child[1] = regexTree;// ��������ʽ����Ϊ����
    }

    return stmtNode;
}

TreeNode* parser::while_stmt(scaner& s)
{
    TreeNode* t = newStmtNode(WhileK,s);
    match(WHILE,s);
    match(LPAREN,s);
    if (t != nullptr) t->child[0] = exp(s);
    match(RPAREN,s);
    if (t != nullptr) t->child[1] = stmt_sequence(s);
    match(ENDWHILE,s);
    return t;
}

TreeNode* parser::for_stmt(scaner& s)
{
    TreeNode* t = newStmtNode(ForK, s);
    qDebug()<<token<<"for";
    match(FOR,s);
    match(LPAREN, s);
    
    if (t != nullptr) t->child[0] = assign_stmt(s);
    match(SEMI, s);
    if (t != nullptr) t->child[1] = exp(s);
    match(SEMI, s);
    if (t != nullptr) t->child[2] = self_term(s);
    match(RPAREN, s);

    match(LPAREN, s);
    if (t != nullptr) t->child[3]=stmt_sequence(s);
    match(RPAREN, s);
    
    
    return t;
}

TreeNode* parser::exp(scaner& s)
{
    TreeNode* t = simple_exp(s); // �����򵥱��ʽ�������ֵ��t
    if ((token == LT) ||token==LT_EQ||token==GT||token==GT_EQ|| (token == EQ)||token==NOT_EQ) // �����ǰ�ʷ���Ԫ��С�ڻ����
    {
        TreeNode* p = newExpNode(OpK,s); // ����һ���µĲ��������ʽ�ڵ�
        if (p != NULL) // ���p��Ϊ��
        {
            p->child[0] = t; // ��t��Ϊ�����������ӽڵ�
            p->attr.op = token; // ���ò�����
            t = p; // �����������ʽ�ڵ㸳ֵ��t
        }
        match(token,s); // ƥ�䵱ǰ�Ĵʷ���Ԫ
        if (t != NULL) {// ���t��Ϊ��
            t->child[1] = simple_exp(s);
        }            // �����򵥱��ʽ����Ϊ�����������ӽڵ�
    }

    return t; // ���ر��ʽ�ڵ�t
}

TreeNode* parser::simple_exp(scaner& s)
{
    TreeNode* t = term(s); // ����������ֵ��t
    while ((token == PLUS) || (token == MINUS)) // ��ǰ�ʷ���Ԫ�ǼӺŻ����ʱ
    {
        TreeNode* p = newExpNode(OpK,s); // ����һ���µĲ��������ʽ�ڵ�
        if (p != NULL) // ���p��Ϊ��
        {
            p->child[0] = t; // ��t��Ϊ�����������ӽڵ�
            p->attr.op = token; // ���ò�����
            t = p; // �����������ʽ�ڵ㸳ֵ��t
            match(token,s); // ƥ�䵱ǰ�Ĵʷ���Ԫ
            t->child[1] = term(s); // �������Ϊ�����������ӽڵ�
        }
    }
    return t;
}

TreeNode* parser::term(scaner& s)
{
    TreeNode* t = powernum(s); // �������ӣ������ֵ��t
    while ((token == TIMES) || (token == OVER)||(token==MOD)) // ��ǰ�ʷ���Ԫ�ǳ˺Ż����ʱ
    {
        TreeNode* p = newExpNode(OpK,s); // ����һ���µĲ��������ʽ�ڵ�
        if (p != NULL) // ���p��Ϊ��
        {
            p->child[0] = t; // ��t��Ϊ�����������ӽڵ�
            p->attr.op = token; // ���ò�����
            t = p; // �����������ʽ�ڵ㸳ֵ��t
            match(token,s); // ƥ�䵱ǰ�Ĵʷ���Ԫ
            p->child[1] = powernum(s); // �������ӣ���Ϊ�����������ӽڵ�
        }
    }
    return t;
}

TreeNode* parser::powernum(scaner& s)
{
    TreeNode* t = factor(s);
    while ((token == POWER) ) // ��ǰ�ʷ���Ԫ�ǼӺŻ����ʱ
    {
        TreeNode* p = newExpNode(OpK,s); // ����һ���µĲ��������ʽ�ڵ�
        if (p != NULL) // ���p��Ϊ��
        {
            p->child[0] = t; // ��t��Ϊ�����������ӽڵ�
            p->attr.op = token; // ���ò�����
            t = p; // �����������ʽ�ڵ㸳ֵ��t
            match(token,s); // ƥ�䵱ǰ�Ĵʷ���Ԫ
            t->child[1] = factor(s); // �������Ϊ�����������ӽڵ�
        }
    }
    return t;
}

TreeNode* parser::factor(scaner& s)
{
        TreeNode * t = NULL; // ��ʼ�����ӽڵ�tΪNULL
        const char* tokenString = s.gettokenstring();
    switch (token) // ���ݵ�ǰ�ʷ���Ԫ������
    {
    case NUM : // ���������
        t = newExpNode(ConstK,s); // ����һ���µĳ������ʽ�ڵ�
        if ((t!=NULL) && (token==NUM)) // ���t��Ϊ���ҵ�ǰ�ʷ���Ԫ������
            t->attr.val = atoi(tokenString); // �������ַ���ת��Ϊ����ֵ
        match(NUM,s); // ƥ������
        break;
    case ID : // ����Ǳ�ʶ��
        t = newExpNode(IdK,s); // ����һ���µı�ʶ�����ʽ�ڵ�
        if ((t!=NULL) && (token==ID)) // ���t��Ϊ���ҵ�ǰ�ʷ���Ԫ�Ǳ�ʶ��
            t->attr.name = copyString(tokenString,s); // ���Ʊ�ʶ���ַ���
        match(ID,s); // ƥ���ʶ��
        break;
    case LPAREN : // �����������
        match(LPAREN,s); // ƥ��������
        t = exp(s); // �������ʽ
        match(RPAREN,s); // ƥ��������
        break;
    case INCREMENT:
        t = self_term(s);
        break;
    case DECREMENT:
        t = self_term(s);
        break;
    default: // �����ǰ�ʷ���Ԫ�������������
        tokenError(s);
        token = s.getToken(); // ��ȡ��һ���ʷ���Ԫ
        break;
    }
    return t; 
}

TreeNode* parser::self_term(scaner& s)
{
    TreeNode* t= NULL;
    TreeNode* p = NULL;
    t = newExpNode(OpK, s);
    switch (token)
    {
    case INCREMENT:
        match(token, s);
        p = newExpNode(IdK, s);
        p->attr.name = copyString(tokenString, s);
        t->attr.op = INCREMENT;
        t->child[0] = p;
        match(ID,s);
        break;
    case DECREMENT:
        match(token, s);
        p = newExpNode(IdK, s);
        p->attr.name = copyString(tokenString,s);
        t->attr.op = DECREMENT;
        t->child[0] = p;
        match(ID, s);
        break;
    default:
        tokenError(s);
        token = s.getToken();
        break;
    }
    return t;
}

TreeNode* parser::regex(scaner& s)
{
    match(DOLLAR, s);
    TreeNode* result= concat(s);
    while (token == OR)
    {
        TreeNode* temp = newExpNode(OpK,s);
        if (temp != NULL) {
            temp->attr.op = token;
            temp->child[0] = result;
            result = temp;
            match(token, s);
            temp->child[1] = concat(s);
        }
    }
    match(DOLLAR, s);
    return result;
}

TreeNode* parser::concat(scaner& s)
{
    TreeNode* result = re_factor(s);
    while (token == RECHAR || token == LBRACKET || token == ANYCHAR || token == LPAREN || token == AND)
    {
        TreeNode* temp = newExpNode(OpK, s);
        if (token != AND) {
            if (temp != NULL) {
                temp->attr.op = AND;
                temp->child[0] = result;
                result = temp;
                temp->child[1] = re_factor(s);
            }
        }
        else
        {
            if (temp != NULL) {
                temp->attr.op = AND;
                temp->child[0] = result;
                result = temp;
                match(token, s);
                temp->child[1] = re_factor(s);
            }
        }
    }
    return result;
}

TreeNode* parser::re_factor(scaner& s)
{
    TreeNode* result = re_term(s);
    if (token == CLOSURE || token == OPTIONAL)
    {
        TreeNode* temp = newExpNode(OpK, s);
        temp->attr.op = token;
        match(token, s);
        temp->child[0] = result;
        result = temp;
    }
    return result;
}
TreeNode* parser::re_term(scaner& s)
{
    TreeNode* result;
    TreeNode* temp;
    switch (token)
    {
    case RECHAR:
        temp = newExpNode(RecK, s);
        temp->attr.name=copyString(tokenString, s);
        result = temp;
        match(token, s);
        break;
    case LBRACKET:
        result = reclass(s);
        break;
    case ANYCHAR:
        temp = newExpNode(RecK, s);
        temp->attr.name = copyString(tokenString, s);
        result = temp;
        match(token, s);
        break;
    case LPAREN:
        match(LPAREN, s); // ƥ��������
        result = concat(s); // �������ʽ
        match(RPAREN, s); // ƥ��������
        break;
    default:
        result = nullptr;
        tokenError(s);
    }
    return result;
}
TreeNode* parser::reclass(scaner& s)
{
    TreeNode* result=nullptr;
    match(LBRACKET, s);
    while (token == RECHAR)
    {
        char start = tokenString[0];
        char end='\0';
        TreeNode* temp = newExpNode(OpK, s);
        temp->attr.op = AND;
        match(RECHAR, s);
        if (token == RANGE)
        {
            match(RANGE, s);
            end = tokenString[0];
            match(RECHAR, s);
        }
        TreeNode* tempstr = newExpNode(RecK, s);
        char* str = new char[4];
        str[0] = start;
        str[1] = '-';
        str[2] = end;
        str[3] = '\0';
        tempstr->attr.name = str;
        temp->child[0] = tempstr;
        if (result == NULL)
        {
            result = temp;
        }
        else
        {
            temp->child[1] = result;
            result = temp;
        }
    }
    match(RBRACKET, s);
    return result;
}




#include "parser.h"
#include<iostream>
#include<QDebug>
TreeNode* parser::parse(scaner &s)
{
  
    token = s.getToken(); // 获取第一个词法单元
    parseroot = stmt_sequence(s); // 解析语句序列，结果赋值给t
    if (token != ENDFILE) // 如果当前词法单元不是文件结束标志
    {
        std::cout<<"Code ends before file\n"; // 报告语法错误
    }
    return parseroot;
}

void parser::preOrderTraversal(const TreeNode* node) {
    if (node == NULL) {
        return;
    }
    // 访问当前节点
    // 这里可以根据需要进行处理，例如打印节点信息、进行语义分析等
    printf("Node - Line: %d, Kind: %d, ", node->lineno, node->nodekind);
    if (node->nodekind == StmtK) {
        // 如果是语句节点，打印语句种类
        printf("Stmt Kind: %d\n", node->kind.stmt);
    }
    else if (node->nodekind == ExpK) {
        // 如果是表达式节点，打印表达式种类
        printf("Exp Kind: %d, ", node->kind.exp);
        if (node->kind.exp == IdK ) {
            // 如果是标识符或常量，打印额外信息
            printf("Value: %s\n", node->attr.name);
        }
        else if (node->kind.exp == OpK) {
            // 如果是操作符，打印操作符类型
            printf("Operator: %d\n", node->attr.op);
        }
        else if (node->kind.exp == RecK) {
            // 如果是正则表达式
            printf("rechar: %s\n", node->attr.name);
        }
        else if (node->kind.exp == ConstK)
        {
            printf("Value: %d\n", node->attr.val);
        }
    }

    // 递归地遍历所有子节点
    for (int i = 0; i < MAXCHILDREN && node->child[i] != NULL; i++) {
        preOrderTraversal(node->child[i]);
    }

    // 如果存在兄弟节点，继续遍历
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
    TreeNode* t = statement(s); // 尝试解析一个语句，并将结果赋值给t
    TreeNode* p = t; // 将t的值赋给p，用于构建语句链表
    while ((token != ENDFILE) && (token != RPAREN) &&
        (token != ELSE) && (token != UNTIL)&&token!=ENDWHILE) // 当不是文件结束、)、ELSE或UNTIL时
    {
        TreeNode* q; // 声明一个临时TreeNode指针q
        match(SEMI,s); // 匹配分号，表示语句结束
        q = statement(s); // 再次尝试解析一个语句，并将结果赋值给q
        if (q != NULL) // 如果q不是NULL
        {
            if (t == NULL) t = p = q; // 如果t是NULL，说明这是第一个语句，将q赋值给t和p
            else // 否则，说明t不是NULL，即前面已经有语句了
            {
                p->sibling = q; // 将当前语句p的兄弟指针指向新语句q
                p = q; // 将p移动到下一个语句q
            }
        }
    }
    return t; // 返回第一个语句的指针t
}

TreeNode* parser::statement(scaner& s)
{
    TreeNode* t = NULL; // 初始化语句节点t为NULL
    switch (token) // 根据当前词法单元的类型
    {
    case IF: t = if_stmt(s); break; // 如果是IF，解析条件语句
    case REPEAT: t = repeat_stmt(s); break; // 如果是REPEAT，解析循环语句
    case ID: t = assign_stmt(s); break; // 如果是ID，可能是赋值语句
    case READ: t = read_stmt(s); break; // 如果是READ，解析读语句
    case WRITE: t = write_stmt(s); break; // 如果是WRITE，解析写语句
    case WHILE: t = while_stmt(s); break;
    case FOR: t = for_stmt(s); break;
    case ANYCHAR : t = regex_stmt(s); break;
    default: 
        tokenError(s); // 打印当前词法单元
        token = s.getToken(); // 获取下一个词法单元
        break;
    } /* end case */
    return t; // 返回解析的语句节点t
}

TreeNode* parser::if_stmt(scaner& s)
{
    TreeNode* t = newStmtNode(IfK,s); // 创建一个新的IF语句节点
    match(IF,s); // 匹配IF
    match(LPAREN, s);
    if (t != NULL) t->child[0] = exp(s); // 如果t不为空，解析表达式作为IF语句的条件
    match(RPAREN,s);
    match(LPAREN, s);
    qDebug()<<tokenString<<token;
    if (t != NULL) t->child[1] = stmt_sequence(s); // 如果t不为空，解析语句序列作为IF语句的真分支
    if (token == ELSE) // 如果下一个词法单元是ELSE
    {
        match(ELSE,s); // 匹配ELSE
        if (t != NULL) t->child[2] = stmt_sequence(s); // 如果t不为空，解析语句序列作为IF语句的假分支
    }
    match(RPAREN,s); // 匹配END
    return t; // 返回IF语句节点t
}

TreeNode* parser::repeat_stmt(scaner& s)
{
    TreeNode* t = newStmtNode(RepeatK,s); // 创建一个新的REPEAT语句节点
    match(REPEAT,s); // 匹配REPEAT
    if (t != NULL) t->child[0] = stmt_sequence(s); // 如果t不为空，解析语句序列作为REPEAT语句的循环体
    match(UNTIL,s); // 匹配UNTIL
    if (t != NULL) t->child[1] = exp(s); // 如果t不为空，解析表达式作为REPEAT语句的终止条件
    return t; // 返回REPEAT语句节点t
}

TreeNode* parser::assign_stmt(scaner& s)
{
    TreeNode* t = newStmtNode(AssignK,s); // 创建一个新的赋值语句节点
    TreeNode* p = newExpNode(IdK,s);
    if ((p != NULL) && (token == ID)) // 如果t不为空且当前词法单元是ID
        p->attr.name = copyString(tokenString,s); // 复制ID的字符串到赋值语句的属性中
    match(ID,s); // 匹配ID
    match(ASSIGN,s); // 匹配赋值符号ASSIGN
    if (t != NULL) t->child[0] = p; // 如果t不为空，解析表达式作为赋值语句的值
    if (t != NULL) t->child[1] = exp(s);
    return t; // 返回赋值语句节点t
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
    match(ANYCHAR, s); // 匹配开头的 .
    IDNode->attr.name = copyString(tokenString, s);
    match(ID, s); 
    match(RE_EQ, s); // 匹配 '==' 中的第一个等号
    TreeNode* regexTree = regex(s); // 解析正则表达式，构建语法树
    if (stmtNode != nullptr) {
        stmtNode->child[0] = IDNode;
        stmtNode->child[1] = regexTree;// 将正则表达式树作为子树
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
    TreeNode* t = simple_exp(s); // 解析简单表达式，结果赋值给t
    if ((token == LT) ||token==LT_EQ||token==GT||token==GT_EQ|| (token == EQ)||token==NOT_EQ) // 如果当前词法单元是小于或等于
    {
        TreeNode* p = newExpNode(OpK,s); // 创建一个新的操作符表达式节点
        if (p != NULL) // 如果p不为空
        {
            p->child[0] = t; // 将t作为操作符的左子节点
            p->attr.op = token; // 设置操作符
            t = p; // 将操作符表达式节点赋值给t
        }
        match(token,s); // 匹配当前的词法单元
        if (t != NULL) {// 如果t不为空
            t->child[1] = simple_exp(s);
        }            // 解析简单表达式，作为操作符的右子节点
    }

    return t; // 返回表达式节点t
}

TreeNode* parser::simple_exp(scaner& s)
{
    TreeNode* t = term(s); // 解析项，结果赋值给t
    while ((token == PLUS) || (token == MINUS)) // 当前词法单元是加号或减号时
    {
        TreeNode* p = newExpNode(OpK,s); // 创建一个新的操作符表达式节点
        if (p != NULL) // 如果p不为空
        {
            p->child[0] = t; // 将t作为操作符的左子节点
            p->attr.op = token; // 设置操作符
            t = p; // 将操作符表达式节点赋值给t
            match(token,s); // 匹配当前的词法单元
            t->child[1] = term(s); // 解析项，作为操作符的右子节点
        }
    }
    return t;
}

TreeNode* parser::term(scaner& s)
{
    TreeNode* t = powernum(s); // 解析因子，结果赋值给t
    while ((token == TIMES) || (token == OVER)||(token==MOD)) // 当前词法单元是乘号或除号时
    {
        TreeNode* p = newExpNode(OpK,s); // 创建一个新的操作符表达式节点
        if (p != NULL) // 如果p不为空
        {
            p->child[0] = t; // 将t作为操作符的左子节点
            p->attr.op = token; // 设置操作符
            t = p; // 将操作符表达式节点赋值给t
            match(token,s); // 匹配当前的词法单元
            p->child[1] = powernum(s); // 解析因子，作为操作符的右子节点
        }
    }
    return t;
}

TreeNode* parser::powernum(scaner& s)
{
    TreeNode* t = factor(s);
    while ((token == POWER) ) // 当前词法单元是加号或减号时
    {
        TreeNode* p = newExpNode(OpK,s); // 创建一个新的操作符表达式节点
        if (p != NULL) // 如果p不为空
        {
            p->child[0] = t; // 将t作为操作符的左子节点
            p->attr.op = token; // 设置操作符
            t = p; // 将操作符表达式节点赋值给t
            match(token,s); // 匹配当前的词法单元
            t->child[1] = factor(s); // 解析项，作为操作符的右子节点
        }
    }
    return t;
}

TreeNode* parser::factor(scaner& s)
{
        TreeNode * t = NULL; // 初始化因子节点t为NULL
        const char* tokenString = s.gettokenstring();
    switch (token) // 根据当前词法单元的类型
    {
    case NUM : // 如果是数字
        t = newExpNode(ConstK,s); // 创建一个新的常量表达式节点
        if ((t!=NULL) && (token==NUM)) // 如果t不为空且当前词法单元是数字
            t->attr.val = atoi(tokenString); // 将数字字符串转换为整数值
        match(NUM,s); // 匹配数字
        break;
    case ID : // 如果是标识符
        t = newExpNode(IdK,s); // 创建一个新的标识符表达式节点
        if ((t!=NULL) && (token==ID)) // 如果t不为空且当前词法单元是标识符
            t->attr.name = copyString(tokenString,s); // 复制标识符字符串
        match(ID,s); // 匹配标识符
        break;
    case LPAREN : // 如果是左括号
        match(LPAREN,s); // 匹配左括号
        t = exp(s); // 解析表达式
        match(RPAREN,s); // 匹配右括号
        break;
    case INCREMENT:
        t = self_term(s);
        break;
    case DECREMENT:
        t = self_term(s);
        break;
    default: // 如果当前词法单元都不是上述情况
        tokenError(s);
        token = s.getToken(); // 获取下一个词法单元
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
        match(LPAREN, s); // 匹配左括号
        result = concat(s); // 解析表达式
        match(RPAREN, s); // 匹配右括号
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




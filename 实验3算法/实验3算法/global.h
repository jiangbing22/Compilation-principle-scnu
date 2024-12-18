#pragma once
/****************************************************/
/* File: globals.h                                  */
/* Global types and vars for TINY compiler          */
/* must come before other include files             */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/
#include <unordered_set>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 13

typedef enum
{
    /* book-keeping tokens */
    ENDFILE, ERROR,
    /* reserved words */
    IF, THEN, ELSE, END, REPEAT, UNTIL, READ, WRITE,
    /*扩充的保留字：for语句，while语句*/
    WHILE, ENDWHILE, FOR, TO, DOWNTO,
    /* multicharacter tokens 扩充正则表达式*/
    ID, NUM, REGEX,RECHAR,
    /* special symbols */
    ASSIGN, EQ, LT, PLUS, MINUS, TIMES, OVER, LPAREN, RPAREN, SEMI,
    /* 扩充增加的符号：<(小于)、>(大于)、<=(小于等于)、>=(大于等于)、<>(不等于)，
     * 正则表达式赋值(==),或(|) 、连接(&)、闭包(*)、括号( ) 、可选运算符号（？）,标记符$,中括号[],任意字符(.),范围(-)
     * ++（前置自增1）、 --（前置自减1），求余%、乘方^
     */
    LT_EQ, GT, GT_EQ, NOT_EQ, RE_EQ, OR, AND, CLOSURE, OPTIONAL,DOLLAR,LBRACKET,RBRACKET,ANYCHAR,RANGE,
    INCREMENT, DECREMENT, MOD, POWER
} TokenType;

//FILE* source; /* source code text file */
//extern FILE* listing; /* listing output text file */
//extern FILE* code; /* code text file for TM simulator */
//extern int lineno; /* source line number for listing */
/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/
typedef enum { StmtK, ExpK } NodeKind;
typedef enum { IfK, RepeatK, AssignK, ReadK, WriteK, WhileK, ForK, RegexK } StmtKind;
typedef enum { OpK, ConstK, IdK,RecK} ExpKind;
/* ExpType is used for type checking */
typedef enum { Void, Integer, Boolean } ExpType;

#define MAXCHILDREN 4

typedef struct treeNode {
    struct treeNode* child[MAXCHILDREN]; // 指向子节点的指针数组，可以有多个子节点
    struct treeNode* sibling;             // 指向同级兄弟节点的指针，形成链表
    int lineno;                            // 记录产生该节点的源代码行号，用于错误报告
    NodeKind nodekind;                     // 定义了节点的种类，区分语句节点和表达式节点
    union {                                // 联合体，用于存储特定于节点种类的额外信息
        StmtKind stmt;                     // 如果是语句节点，存储语句的种类
        ExpKind exp;                       // 如果是表达式节点，存储表达式的种类
    } kind;
    union {                                // 另一个联合体，用于存储节点的属性
        TokenType op;                      // 如果节点代表操作符，存储操作符的类型
        int val;                           // 如果节点代表常量，存储该常量的整数值
        char* name;                       // 如果节点代表标识符或正则表达式字符，存储该标识符的字符串
    } attr;
    ExpType type;                          // 用于存储表达式节点的类型信息，用于类型检查
} TreeNode;

/**************************************************/
/***********   Flags for tracing       ************/
/**************************************************/




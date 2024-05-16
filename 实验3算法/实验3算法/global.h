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
    /*����ı����֣�for��䣬while���*/
    WHILE, ENDWHILE, FOR, TO, DOWNTO,
    /* multicharacter tokens ����������ʽ*/
    ID, NUM, REGEX,RECHAR,
    /* special symbols */
    ASSIGN, EQ, LT, PLUS, MINUS, TIMES, OVER, LPAREN, RPAREN, SEMI,
    /* �������ӵķ��ţ�<(С��)��>(����)��<=(С�ڵ���)��>=(���ڵ���)��<>(������)��
     * ������ʽ��ֵ(==),��(|) ������(&)���հ�(*)������( ) ����ѡ������ţ�����,��Ƿ�$,������[],�����ַ�(.),��Χ(-)
     * ++��ǰ������1���� --��ǰ���Լ�1��������%���˷�^
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
    struct treeNode* child[MAXCHILDREN]; // ָ���ӽڵ��ָ�����飬�����ж���ӽڵ�
    struct treeNode* sibling;             // ָ��ͬ���ֵܽڵ��ָ�룬�γ�����
    int lineno;                            // ��¼�����ýڵ��Դ�����кţ����ڴ��󱨸�
    NodeKind nodekind;                     // �����˽ڵ�����࣬�������ڵ�ͱ��ʽ�ڵ�
    union {                                // �����壬���ڴ洢�ض��ڽڵ�����Ķ�����Ϣ
        StmtKind stmt;                     // ��������ڵ㣬�洢��������
        ExpKind exp;                       // ����Ǳ��ʽ�ڵ㣬�洢���ʽ������
    } kind;
    union {                                // ��һ�������壬���ڴ洢�ڵ������
        TokenType op;                      // ����ڵ������������洢������������
        int val;                           // ����ڵ���������洢�ó���������ֵ
        char* name;                       // ����ڵ�����ʶ����������ʽ�ַ����洢�ñ�ʶ�����ַ���
    } attr;
    ExpType type;                          // ���ڴ洢���ʽ�ڵ��������Ϣ���������ͼ��
} TreeNode;

/**************************************************/
/***********   Flags for tracing       ************/
/**************************************************/




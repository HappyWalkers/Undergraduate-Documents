#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define success 0
#define fail -1

typedef struct infoin
{ //子链信息
    int row;
} infoin;
typedef struct nodein
{ //子链节点
    infoin row;
    struct nodein *next;
} nodein;
typedef struct infoout
{ //主链信息
    nodein *headin;
    char *word;
} infoout;
typedef struct nodeout
{ //主链节点
    infoout word;
    struct nodeout *next;
} nodeout;

int Initout(nodeout *headout);
int lengthout(nodeout *headout);
int lengthin(nodein* headin);
int insertout(nodeout *headout, infoout word,int pos);
int InitIn(nodein* headin);
int insertin(nodein* headin,infoin row,int pos);
int printin(nodein *head);
int Inquireout(nodeout *head, int pos,char* word[]);
int printout(nodeout* head);
int getword(char **str, char *word); //在函数中修改str传不回去，使用指向指针的指针
int isKeyWord(char *word);
int add(nodeout *head, char *word, int row); //将行号加入二重链表
int wordPrint(nodeout *head);
int read(nodeout *head);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define success 0
#define fail -1

typedef struct infoin
{ //������Ϣ
    int row;
} infoin;
typedef struct nodein
{ //�����ڵ�
    infoin row;
    struct nodein *next;
} nodein;
typedef struct infoout
{ //������Ϣ
    nodein *headin;
    char *word;
} infoout;
typedef struct nodeout
{ //�����ڵ�
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
int getword(char **str, char *word); //�ں������޸�str������ȥ��ʹ��ָ��ָ���ָ��
int isKeyWord(char *word);
int add(nodeout *head, char *word, int row); //���кż����������
int wordPrint(nodeout *head);
int read(nodeout *head);

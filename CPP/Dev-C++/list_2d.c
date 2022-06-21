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
int Initout(nodeout *headout)
{
    if (headout == NULL)
    {
        printf("malloc fail in main for headout\n");
        return fail;
    }
    headout->next = NULL;
    return success;
}
int lengthout(nodeout *headout)
{
    int len = 0;
    nodeout *p = headout;
    while (p != NULL)
    {
        len++;
        p = p->next;
    }
    return len-1;//不计算头节点
}
int lengthin(nodein* headin)
{
    int len = 0;
    nodein *p = headin;
    while (p != NULL)
    {
        len++;
        p = p->next;
    }
    return len-1;//不计算头节点
}
int insertout(nodeout *headout, infoout word,int pos)
{
    if (pos > lengthout(headout)+1 || pos < 0)
    {
        printf("illegal position in Insert\n");
        return fail;
    }
    nodeout *p = headout;
    for (int i = pos; i > 1; i--)
    {
        p = p->next;
    }

    nodeout *x = (nodeout *)malloc(sizeof(nodeout));
    if (x == NULL)
    {
        printf("malloc fail in Insert");
        return fail;
    }
    x->word=word;
    x->next = p->next;
    p->next = x;
    return success;
}
int InitIn(nodein* headin)
{
    if (headin == NULL)
    {
        printf("malloc fail in main for headin\n");
        return fail;
    }
    headin->next = NULL;
    return success;
}
int insertin(nodein* headin,infoin row,int pos)
{
    if (pos > lengthin(headin)+1 || pos < 0)
    {
        printf("illegal position in Insert\n");
        return fail;
    }
    nodein *p = headin;
    for (int i = pos; i > 1; i--)
    {
        p = p->next;
    }

    nodein *x = (nodein *)malloc(sizeof(nodein));
    if (x == NULL)
    {
        printf("malloc fail in Insert");
        return fail;
    }
    x->row=row;
    x->next = p->next;
    p->next = x;
    return success;
}
int printin(nodein *head)
{
    nodein *p = head;
    printf("this list has nodes: %d\n", lengthin(head));
    printf("the node from head to tail is:\n");
    while (p->next != NULL)
    {
        p = p->next;
        printf("row:%d\n",p->row.row);
    }
    return success;
}
int Inquireout(nodeout *head, int pos,char* word[])
{
    if (pos > lengthout(head) || pos < 0)
    {
        printf("illegal position in Inquire\n");
        return fail;
    }
    nodeout *p = head;
    for (int i = pos; i > 0; i--)
    {
        p = p->next;
    }
    *word=p->word.word;
    return success;
}
int printout(nodeout* head)
{
    nodeout *p = head;
    printf("this list has nodes: %d\n", lengthout(head));
    printf("the node from head to tail is:\n");
    while (p->next != NULL)
    {
        p = p->next;
        printf("word:%s\n",p->word.word);
        printf("point:%p\n",p->word.word);
    }
    return success;
}
// int main()
// {
//     nodeout *headout = (nodeout *)malloc(sizeof(nodeout));
//     Initout(headout);
//     nodein* headin=(nodein*)malloc(sizeof(nodein));
//     InitIn(headin);

//     infoin row={1};
//     insertin(headin,row,1);
//     infoin row2={2};
//     insertin(headin,row2,2);

//     printin(headin);
//     printf("lengthin:%d\n",lengthin(headin));

//     infoout word={headin,"hh"};
//     nodein* headin2=(nodein*)malloc(sizeof(nodein));
//     InitIn(headin2);
//     infoout word2={headin2,"what"};

//     insertout(headout,word,1);
//     insertout(headout,word2,2);

//     char* word_inquire;
//     Inquireout(headout,1,&word_inquire);
//     printf("word:%s\n",word_inquire);

//     printout(headout);
//     printf("lengthout:%d\n",lengthout(headout));

//     printin(headout->next->word.headin);
//     return 0;
// }


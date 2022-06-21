#include <stdio.h>
#include <stdlib.h>
typedef struct node //节点
{
    int data;
    struct node *next;
} node;
int length(node *head)
{ //返回链表长度，算上头节点
    int len = 0;
    node *p = head;
    while (p != NULL)
    {
        len++;
        p = p->next;
    }
    return len;
}
void Init(node *head)
{                                        //带头节点
    if (head == NULL)
    {
        printf("malloc fail in main\n");
        return;
    }
    head->data = 0; //头节点存链长，且头节点不计入链长
    // printf("%d",head->data);
    head->next = NULL;
}
void Insert(node *head, int e, int pos)
{                                      //在第pos个节点后插入新节点
    if (pos > length(head) || pos < 0) //不合法位置
    {
        printf("illegal position in Insert\n");
        return;
    }
    node *p = head;
    for (int i = pos; i > 1; i--) //找到插入位置
    {
        p = p->next;
    }

    node *x = (node *)malloc(sizeof(node)); //要插入的节点
    if (x == NULL)
    {
        printf("malloc fail in Insert");
        return;
    }
    x->data = e;
    x->next = p->next;
    p->next = x;
    head->data++;
}
void Delete(node *head, int *e, int pos)
{                                      //删除第pos个节点
    if (pos > length(head) || pos < 0) //非法位置
    {
        printf("illegal position in Delete\n");
        return;
    }
    node *p = head;//当前指针
    node *p_pre;//当前指针的前驱
    for (int i = pos; i >= 1; i--) //找到位置
    {
        p_pre = p;
        p = p->next;
    }
    p_pre->next = p->next;//将当前节点从链表中断开
    *e = p->data;//用e带出删掉的值
    free(p);
    head->data--;
}
void Inquire(node *head, int *e, int pos) //查询第pos个节点位置
{
    if (pos > length(head) || pos < 0)
    {
        printf("illegal position in Inquire\n");
        return;
    }
    node *p = head;
    for (int i = pos; i >= 1; i--)//找位置
    {
        p = p->next;//下一个
    }
    *e = p->data;//用e带出查询结果
    printf("查询结果————第%d个节点的值为：%d",pos,*e);
}
void print(node *head) //将链表从头到尾打印
{
    node *p = head;
    printf("当前链表有节点：%d个\n", head->data);
    printf("链表节点从头到尾分别为：\n");
    while (p->next != NULL)
    {
        p = p->next;
        printf("%d\n", p->data);
    }
}
void main()
{
    node* head = (node *)malloc(sizeof(node)); //在主函数中申请头节点
    Init(head); //初始化
    int *e;
    Insert(head, 10, 1); //插入
    Insert(head, 28, 2);
    Insert(head, 30, 1);
    // printf("hh");
    print(head);
    Delete(head, e, 2); //删除
    print(head);
    Inquire(head, e, 2); //查询
}
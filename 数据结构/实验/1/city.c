#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
typedef struct info//节点中的信息
{
    char *name;
    double x;
    double y;
} info;
typedef struct node//节点
{
    info city;
    struct node *next;
} node;
int length(node *head)//返回链长度
{
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
{                     //带头节点
    head->next = NULL;
}
void Insert(node *head, info city, int pos)
{ //在第pos个节点后插入新节点
    if (pos > length(head) || pos < 0)//非法位置
    {
        printf("illegal position in Insert\n");
        return;
    }
    node *p = head;
    for (int i = pos; i > 1; i--)//找到位置
    {
        p = p->next;
    }

    node *x = (node *)malloc(sizeof(node));//申请节点
    if (x == NULL)
    {
        printf("malloc fail in Insert");
        return;
    }
    x->city = city;
    x->next = p->next;
    p->next = x;
}
void Delete(node *head, info *city, int pos)
{ //删除第pos个节点
    if (pos > length(head) || pos < 0)//非法位置
    {
        printf("illegal position in Delete\n");
        return;
    }
    node *p = head;
    node *p_pre = head;
    for (int i = pos; i > 0; i--)//找到位置
    {
        p_pre = p;
        p = p->next;
    }
    p_pre->next = p->next;
    *city = p->city;
    free(p);
}
void Inquire(node *head, info *city, int pos)//查询第pos个节点的信息
{
    if (pos > length(head) || pos < 0)//非法位置
    {
        printf("illegal position in Inquire\n");
        return;
    }
    node *p = head;
    for (int i = pos; i > 0; i--)//找到位置
    {
        p = p->next;
    }
    *city = p->city;
    printf("the result of Inquire is: name:%s  x:%f  y:%f\n",
    city->name,city->x,city->y);
}
void Inquire2(node *head, info *city) //return x,y according to name in city
{
    node *p = head;
    while (p != NULL)//遍历链表
    {
        if (strcmp(city->name, p->city.name) == 0)//判断当前节点城市名与传入参数city中的城市名是否相同
        {
            city->x = p->city.x;
            city->y = p->city.y;
            printf("the address of the %s is (%f,%f)\n", city->name,
                   city->x, city->y);
            return;
        }
        p = p->next;
    }
    printf("fail to find %s\n",city->name);//还没返回说明没找到
}
void print(node *head)//从头到尾打印该链表
{
    node *p = head;
    printf("当前链表有节点：%d个\n", length(head)-1);
    printf("链表节点从头到尾分别为：\n");
    while (p->next != NULL)//遍历
    {
        p = p->next;
        printf("name:%s   ", p->city.name);
        printf("x:%f    ", p->city.x);
        printf("y:%f\n", p->city.y);
    }
}
double dis(info city1,info city2){//返回两城市间距离
    return sqrt(pow((city1.x-city2.x),2)+pow((city1.y-city2.y),2));
}
void Inquire_all(node* head,info point,double distance,node* new_head){//查询所有与point的距离在distance范围内的城市
    node* p=head;
    while(p->next!=NULL){//遍历
        p=p->next;
        double disReal=dis(point,p->city);
        if(disReal<distance){//判断是否在distance范围内
            Insert(new_head,p->city,1);
        }
    }
}
void main()
{
    node *head = (node *)malloc(sizeof(node));//在主函数内申请头节点
    if (head == NULL)
    {
        printf("malloc fail in main\n");
        return;
    }
    Init(head);//初始化
    info city1 = {"hefei", 1, 1};
    Insert(head, city1, 1);//插入
    info city2 = {"nanjing", 2, 2};
    Insert(head, city2, 2);
    info city3 = {"shanghai", 3, 3};
    Insert(head, city3, 3);
    print(head);//打印
    info city4;
    Delete(head, &city4, 2);//删除
    print(head);
    Inquire(head, &city4, 2);//查询

    info city = {"hefei"};
    Inquire2(head, &city);//根据城市名查询

    info point={NULL,0,0};
    node* new_head=(node*)malloc(sizeof(node));//用头节点为new_head的链表带出所有满足条件的城市
    if(new_head==NULL){
        printf("malloc fail in main\n");
        return;
    }
    Init(new_head);
    Inquire_all(head,point,2,new_head);//查询在distance范围内的城市
    print(new_head);
}
#include <stdio.h>
#include <stdlib.h>

//栈
#define maxsize 2//栈的空间
#define full 1
#define notfull -1
#define empty 0
#define notempty 1
#define ok 0
#define fail 1
#define underflow -1
typedef int ElemType;
typedef struct//栈
{
    ElemType *base;//基指针
    ElemType top; //下标
} stack;
void Init(stack *s)
{                                                             //初始化函数
    s->base = (ElemType *)malloc(maxsize * sizeof(ElemType)); //申请空间
    if (s == NULL)
    {
        printf("malloc fail in Init");
        return;
    }
    s->top = 0;//初始化时下标为0
}
void push(stack *s, ElemType e)
{ //压栈
    if (s->top == maxsize)
    { //溢出
        printf("stack is overflow");
        return;
    }
    *(s->base + s->top) = e; //压入
    s->top++;                //栈顶上移
}
int pop(stack *s)
{ //出栈
    if (s->top == 0)
    { //空栈
        printf("stack is underflow");
        return 0;
    }
    s->top--;                   //栈顶下移
    return *(s->base + s->top); //返回移出的值
}
int isfull(stack s)//是否满栈
{
    if (s.top == maxsize)
    {
        return full;
    }
    else
    {
        return notfull;
    }
}
int isempty(stack s)//是否空栈
{
    if (s.top == 0)
    {
        return empty;
    }
    else
    {
        return notempty;
    }
}
void stack_print(stack *s)
{ //从栈顶到栈底打印栈
    printf("stack:\n");
    for (int i = s->top - 1; i >= 0; i--)
    {
        printf("%d\n", *(s->base + i));
    }
}

//队列
typedef int QElemType;
typedef struct QNode
{ //节点
    QElemType data;
    struct QNode *next; //链队列
} QNode;
typedef struct
{
    QNode *front; //头指针，带空头节点
    QNode *rear;  //尾指针
} LinkQueue;
int InitQueue(LinkQueue *q)
{                                                        //初始化
    q->front = q->rear = (QNode *)malloc(sizeof(QNode)); //申请空间，front指向头节点（空的）
    if (q->front == NULL)
    { //若是申请失败
        printf("malloc fail in InitQueue");
        return fail;
    }
    q->front->next = NULL; //空队的头节点下一个自然为空
    return ok;
}
int EnQueue(LinkQueue *q, QElemType e)
{                                              //插入
    QNode *p = (QNode *)malloc(sizeof(QNode)); //将要插入的节点
    if (p == NULL)
    {
        printf("malloc fail in EnQueue");
        return fail;
    }
    p->data = e;       //p的值为e
    p->next = NULL;    //在尾部插入，其下一个为空
    q->rear->next = p; //接到尾节点的下一个
    q->rear = p;       //p为新的尾节点
    return ok;
}
int DeQueue(LinkQueue *q, QElemType *e)
{ //删除
    if (q->front == q->rear)
    { //空队无法删除
        printf("underflow\n");
        return underflow;
    }
    QNode *p = q->front->next; //需要删除的节点
    *e = p->data;              //用e带出删掉的值
    q->front->next = p->next;  //将要删除的节点从链中断开
    if (q->rear = p)
    {                       //加入原来队中只有一个节点
        q->rear = q->front; //删完后为空队，头节点与尾节点指到一起
    }
    free(p);
    return ok;
}
int queue_isempty(LinkQueue q)//判断是否空队
{
    if (q.front == q.rear)
    {
        return empty;
    }
    else
    {
        return notempty;
    }
}
int queue_print(LinkQueue q)
{                       //打印队列，从队头到队尾
    QNode *p = q.front; //头节点为空， 不需要打印
    while (1)
    {
        p = p->next;             //下一个节点
        printf("%d\n", p->data); //打印值
        if (p == q.rear)
        { //到队尾退出
            break;
        }
    }
}

//park
static int pos_walk = 0;//静态全局变量，用于记录可以获得的 便道的停车位置
int arrive(stack *park, stack *time, LinkQueue *walk, int license, int arrival)//若有车到达
{
    if (isfull(*park) == notfull)//若停车场还有位置
    {
        push(park, license);//将车牌号和到达时间压入栈
        push(time, arrival);
        printf("got NO.%d position in park\n", park->top);//输出在停车场中的位置
    }
    else if (isfull(*park) == full)//若停车场已满，新来的车停入便道
    {
        pos_walk++;//便道进入一辆车
        EnQueue(walk, license);//将车牌号压入便道栈
        printf("got NO.%d position in sidewalk\n", pos_walk);//输出在便道中的位置
    }
    return ok;
}
int depart(stack *park, stack *time, LinkQueue *walk, int license, int arrival)//若有车要离开
{                       
    stack temp_license; //用来存暂时退开的车
    Init(&temp_license);
    stack temp_time;
    Init(&temp_time);
    while (1)//1号车离开，先将2号车存入另外一个栈，pop(1),push(2)
    {                                         
        int med_license = pop(park); //取出的车牌号
        int med_time = pop(time);//被取出车的进入时间
        if (med_license != license)
        { //不是要离开的车，就存入另一个栈
            push(&temp_license, med_license);
            push(&temp_time, med_time);
            continue;
        }
        else if (med_license == license)//是要离开的车，输出停车时间和停车费，并将另外一个栈的车还回来
        {                                       
            int park_time = arrival - med_time; //停车时间
            int moneyEvery = 10;                //每单位时间停车费
            int money = park_time * moneyEvery; //停车费
            printf("the car of %d have parked for %d time\n", license,park_time);//输出停车时间
            printf("fees is %d\n", money);//输出停车费
            while (isempty(temp_license) == notempty)//若temp未空，就一直出栈
            { //从temp还回暂时退开的车
                push(park, pop(&temp_license));
                push(time, pop(&temp_time));
            }
            break; //还完车就算这辆车成功离开
        }
    }
    //离开一辆车后，若便道上有车等待，则车进入停车场
    if (queue_isempty(*walk) == notempty)//若便道上有车等待
    {
        QElemType e;
        DeQueue(walk, &e);//从便道驶出一辆车
        pos_walk--;//便道停车位置减一
        push(park, e);       //走一辆车就进一辆车
        push(time, arrival); //其进入停车场时间就是上一辆车离开的时间
    }
    return ok;
}
int read(stack *park, stack *time, LinkQueue *walk)//读入数据，并处理
{
    while (1)
    {
        char order;//A或D或E
        int license;//车牌号
        int arrival;//到达时间
        scanf("%c,%d,%d", &order, &license, &arrival);
        if (order == 'A')//若有车到达
        {
            arrive(park, time, walk, license, arrival);
        }
        else if (order == 'D')//若有车离开
        {
            depart(park, time, walk, license, arrival);
        }
        else if (order == 'E')//模拟结束
        {
            break;
        }
    }
    return ok;
}
//主函数
int main()
{
    stack park;//停车场
    Init(&park);
    stack time;//进入停车场的时间
    Init(&time);
    LinkQueue walk;//便道
    InitQueue(&walk);
    read(&park, &time, &walk);//读入处理数据
    return 0;
}
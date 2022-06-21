#include <stdio.h>
#include <stdlib.h>
#define queuesize 100
#define overflow 1
#define underflow -1
#define ok 0
typedef int ElemType;
typedef struct squeue
{
    ElemType sq[queuesize];
    ElemType front;
    ElemType rear;
} queue;
int en_cycque(queue *q, ElemType x)
{                                      //入队
    int i = (q->rear + 1) % queuesize; //循环队列
    if ((i == q->front))
    {                         //空出一个不用
        printf("overflow\n"); //溢出
        return overflow;
    }
    q->sq[q->rear] = x; //写入,rear指向队列最后一个元素后面的位置
    q->rear = i;        //尾指针移动
    return ok;
}
int dl_cycque(queue *q, ElemType *x)
{ //出队
    if (q->front == q->rear)
    { //空队
        printf("underflow\n");
        return underflow;
    }
    *x = q->sq[q->front];                  //用x带出
    q->front = (q->front + 1) % queuesize; //头指针后移，从队头删除
    return ok;
}
int print(queue *q)//打印队列
{
    if (q->front == q->rear)//溢出
    {
        printf("underflow\n");
        return underflow;
    }
    else if ((q->rear + 1) % queuesize == q->front)//空队
    {
        printf("overflow");
        return overflow;
    }
    else if (q->rear > q->front)//若队尾指针在队头指针后面
    {
        for (int i = q->front; i < q->rear; i++)//遍历打印
        {
            printf("%d\n", q->sq[i]);
        }
    }
    else if (q->rear < q->front)//若队尾指针在队头指针前面
    {
        for (int i = q->front; i <= queuesize; i++)
        {
            printf("%d\n", q->sq[i]);
        }
        for (int i = 0; i < q->rear; i++)
        {
            printf("%d\n", q->sq[i]);
        }
    }
}
int main()
{
    queue q;//生成循环队列
    q.front=0;//使队头队尾皆为0
    q.rear=0;
    en_cycque(&q, 1);
    en_cycque(&q, 2);
    en_cycque(&q, 3);
    print(&q);
    int e;//带出删掉的元素
    dl_cycque(&q,&e);
    // printf("%d\n",e);//查看删掉的元素
    print(&q);
    return 0;
}
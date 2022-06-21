#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct node//节点，双向循环链表
{
    int num;
    struct node *pre;
    struct node *next;
} node;
void Init(node *head, int n)//初始化
{
    //n是num的位数，其符号代表num的符号，位数
    head->next = head;
    head->pre = head;
    head->num = n;
}
void Insert(node *head, int e, int pos)
{ //插在第pos个节点之后
    node *s = (node *)malloc(sizeof(node));//申请节点
    if (s == NULL)
    {
        printf("malloc fail in Insert");
        return;
    }
    s->num = e;
    node *p = head;
    for (int i = pos; i > 1; i--)//找位置
    {
        p = p->next;
    }
    s->next = p->next;//插入
    p->next = s;
    s->next->pre = s;
    s->pre = p;
}
int length(node *head)//返回链表长度
{
    node *p = head;
    int len = 1;
    while (p->next != head)//遍历
    {
        len++;
        p = p->next;
    }
    return len;
}
void read(node *head, int m)//从键盘读入数据
{
    int e;
    int n = abs(m);//去掉符号
    switch (n % 4)
    {
    case 1://若是1/5/9之类的
        scanf("%1d", &e);//首位只存一位数字
        Insert(head, e, length(head));
        for (int i = abs(n - 1) / 4; i > 0; i--)//假如是9，需要三个节点存储，（除首位外)每个节点存储一个四位数
        {
            scanf("%4d", &e);
            Insert(head, e, length(head));
        }
        break;
    case 2://若是2/6/10之类的
        scanf("%2d", &e);//首位存两位数字
        Insert(head, e, length(head));
        for (int i = abs(n - 1) / 4; i > 0; i--)
        {
            scanf("%4d", &e);
            Insert(head, e, length(head));
        }
        break;
    case 3:
        scanf("%3d", &e);
        Insert(head, e, length(head));
        for (int i = abs(n - 1) / 4; i > 0; i--)
        {
            scanf("%4d", &e);
            Insert(head, e, length(head));
        }
        break;
    case 0://若是四的整数倍
        for (int i = abs(n - 1) / 4 + 1; i > 0; i--)//每个节点存一个四位数
        {
            scanf("%4d", &e);
            Insert(head, e, length(head));
        }
        break;
    }
}
void print(node *head)//打印，更清楚的算法应该是找到第一个有效数字，其之前的0都部输出，其之后的空位需要补0
{
    node *p = head;//头指针
    p = p->next;//head不需要打印
    if(length(head)==2){//若是只有一个节点，即在四位数以内，直接打印即可，不需要补0
        printf("%d", p->num);
    }
    else if(length(head)>2 && p->num!=0){//若不只四位数，在首位不为0的情况下，才打印
        printf("%d", p->num);
    }
    int flag=0;//用来判断是否到达有效数字（数电的思想），看其从开头到现在是否一直为0，是则flag>0
    if(p->num==0 && length(head)>2){//若不只四位数，在首位为0的情况下，flag==1
        flag=1;
    }
    while (p->next != head)//遍历链表
    {
        p = p->next;
        if(flag>0 && p->num==0){//如果当前位为0，且之前一直没到有效数字
            flag++;//flag加一，说明已经有新的一位为0了
            if(flag==abs(head->num)){//如果从开头到结尾都是0，那至少打印一位数字
                printf("%d",p->num);
                return;
            }
            continue;//尚未找到有效数字时，就不打印
        }
        else if(flag>0 && p->next==head){//到了最后一位尚未打印，那么至少打印最后一位
            printf("%d",p->num);
            return;
        }
        else{//找到有效数字就将flag置0，其后的数字需要补0
            flag=0;
        }
        if (abs(p->num) >= 0 && abs(p->num) <= 9)//一位数字补三个0
        {
            printf("000%d", p->num);
        }
        else if (abs(p->num) >= 10 && abs(p->num) <= 99)//两位数字补两个0
        {
            printf("00%d", p->num);
        }
        else if (abs(p->num) >= 100 && abs(p->num) <= 999)
        {
            printf("0%d", p->num);
        }
        else
        {
            printf("%d", p->num);
        }
    }
    printf("\n");
}
void add(node *head1, node *head2, node *ans)//加法和减法
{
    //对齐数字
    int m = (abs(head1->num) - 1) / 4 + 1;//计算以head1位头节点的链有几个节点
    int n = (abs(head2->num) - 1) / 4 + 1;
    int sub = m - n;
    if (sub > 0)//如果head1比较长，就给head2从首位开始补0
    {
        for (int i = sub; i > 0; i--)
        {
            Insert(head2, 0, 1);
        }
    }
    else if (sub < 0)
    {
        for (int i = abs(sub); i > 0; i--)
        {
            Insert(head1, 0, 1);
        }
    }
    int count = m > n ? m : n;//计算次数，看比较高的位数
    ans->num=count;//答案的位数
    //计算
    int flag = 0;//进位与借位标志
    node *p1 = head1->pre;//head1的末尾
    node *p2 = head2->pre;
    int answer = 0;//每个节点计算结果
    //两数皆为正数，加法
    if (head1->num > 0 && head2->num > 0)
    {
        for (int i = count; i > 0; i--)
        {
            answer = p1->num + p2->num + flag;//直接加，再加上进位标志
            if (answer > 9999)//溢出
            {
                flag = 1;//进位
                Insert(ans, answer % 10000, 1);
            }
            else if (answer >= 0)//未溢出
            {
                flag = 0;
                Insert(ans, answer, 1);
            }
            p1 = p1->pre;//计算更高位
            p2 = p2->pre;
        }
        if (flag == 1)//如果最高位的加法还有进位
        {
            Insert(ans, 1, 1);//增加一个更高位
        }
    }
    //两数皆为负数，算完加法，添个负号即可
    else if (head1->num < 0 && head2->num < 0)
    {
        for (int i = count; i > 0; i--)
        {
            answer = abs(p1->num) + abs(p2->num) + flag;//当加法算
            if (answer > 9999)
            {
                flag = 1;
                Insert(ans, answer % 10000, 1);
            }
            else if (answer >= 0)
            {
                flag = 0;
                Insert(ans, answer, 1);
            }
            p1 = p1->pre;
            p2 = p2->pre;
        }
        if (flag == 1)//最高位有进位
        {
            Insert(ans, -1, 1);//只需要在意最高位的符号，其为负即整个长数为负数（输出的时候）
        }
        else
        {
            ans->next->num = -ans->next->num;//最高位置为负数
        }
    }
    //一正一负，减法，需考虑借位
    else 
    {
        for (int i = count; i > 0; i--)
        {
            answer = ((head1->num) / abs(head1->num)) * p1->num + ((head2->num) / abs(head2->num)) * p2->num + flag;//带符号的加法
            if (answer >= 0)//结果为非负数
            {
                flag = 0;//不用借位
                Insert(ans, answer, 1);
            }
            if (answer < 0)//结果为负数，插入的其实为补码
            {
                flag = -1;//借位
                if (i == 1)//算到最后一次（最高位）时，插入对应位数的补码
                {
                    if (answer == 0)//零直接插0
                        Insert(ans, 0, 1);
                    if (answer > 0 && answer < 10)//一位数
                        Insert(ans, 10 + answer, 1);
                    if (answer >= 10 && answer < 100)//两位数
                        Insert(ans, 100 + answer, 1);
                    if (answer >= 100 && answer < 1000)
                        Insert(ans, 1000 + answer, 1);
                    if (answer >= 1000 && answer < 10000)
                        Insert(ans, 10000 + answer, 1);
                }
                else//其他位，直接补上用10000的补
                {
                    Insert(ans, 10000 + answer, 1);
                }
            }
            p1 = p1->pre;//计算更高位
            p2 = p2->pre;
        }
        if (flag == -1)//算到最高位还需借位的话，说明之前的（包括最高位）都是补码，需要计算补码的原码
        {
            node *p = ans;
            for (int i = count; i > 0; i--)
            {
                p = p->next;
                if (i == 1)//最低位没有被更低位借位，直接用10000求补
                    p->num = 10000 - p->num;
                if (i == count)//最高位，用对应位数的来求补码
                {
                    if (p->num > 0 && p->num < 10)
                        p->num =  p->num-9;//因为是负数，所以减9
                    if (p->num >= 10 && p->num < 100)
                        p->num = p->num-99;
                    if (p->num >= 100 && p->num < 1000)
                        p->num = p->num-999;
                    if (p->num >= 1000 && p->num < 10000)
                        p->num = p->num-9999;
                }
                else//其他位数被更低位借去了1，so用9999减
                    p->num = 9999 - p->num;
            }
        }
    }
}
int main()//主函数
{
    node *head1 = (node *)malloc(sizeof(node));//第一个数字的头节点
    if (head1 == NULL)
    {
        printf("malloc fail in main");
        return 0;
    }
    printf("please enter the number of digits you will enter,whose symbol stands for the number's symbol: ");
    int n;
    scanf("%d", &n);//读入数字的位数，其符号代表第一个数字的符号
    if(n==0){
        printf("illegal number");
        return 0;
    }
    Init(head1, n);//初始化
    printf("please enter the first number: ");
    read(head1, n);//read读入第一个数字
    // print(head1);

    node *head2 = (node *)malloc(sizeof(node));//第二个数字的头节点
    if (head2 == NULL)
    {
        printf("malloc fail in main");
        return 0;
    }
    printf("please enter the number of digits you will enter,whose symbol stands for the number's symbol: ");
    int m;
    scanf("%d", &m);
    if(m==0){
        printf("illegal number");
        return 0;
    }
    Init(head2, m);
    printf("please enter the second number: ");
    read(head2, m);
    // print(head2);

    node *ans = (node *)malloc(sizeof(node));//结果的头节点
    if (ans == NULL)
    {
        printf("malloc fail in ans of main");
        return 0;
    }
    Init(ans, 0);//初始化
    add(head1, head2, ans);//计算结果
    printf("the sum of these numbers is: ");
    print(ans);//打印结果
}
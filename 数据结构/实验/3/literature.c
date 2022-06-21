#include "list_2d.c"

//literature
int getword(char **str, char *word)//得到这个字符串str的第一个word，并从str中删掉它，找不到word就返回fail,找到返回success
{                                   
    //在函数中修改str传不回去，使用指向指针的指针str
    //两个非字母之间的即视为一个word
    memset(word, 0, 20 * sizeof(char));//清空
    if (strlen(*str) == 0) //str为空时返回fail
    {
        return fail;
    }
    int i = 0;//记录str下标
    int pos = 0;//记录word下标
    while (1)//找出word
    {
        if ((*(*str + i) >= 'A' && *(*str + i) <= 'Z') || (*(*str + i) >= 'a' && *(*str + i) <= 'z'))
        {
            word[pos++] = *(*str + i); //若是字母就连接到word中去
            i++;
        }
        else
        {
            break; //不是字母就选取结束
        }
    }
    *str = *str + i; //删掉取出的word（对指针的修改需要十分注意）
    if (strlen(*str) == 0)
    { //str第一次为空是刚取完时，故成功
        return success;
    }
    *str = *str + 1; //再删掉不是字母的那个字符
    return success;//成功返回
}
int isKeyWord(char *word)//若word在字符集中就返回success,否则返回fail
{ 
    char esp[][31]={"int","long","short","float","double","char","unsigned","signed","const",
    "void","volatile","enum","struct","union","if","else","goto","switch","case","do",
    "while","for","continue","break","return","default","typedef","auto","register",
    "extern","sizeof"};
    int flag=0;//标志，word为保留字就为1，否则为0
    for(int i=0;i<=31;i++){//遍历比较
        // printf("%s",esp[i]);
        if(strcmp(word,esp[i])==0){//找到相同的
            flag=1;
        }
    }
    if (flag==1)//在保留字中返回success
    {
        return success;
    }
    else//不在保留字中返回fail
    {
        return fail;
    }
}
int add(nodeout *head, char *word, int row) //将word和行号加入二重链表
{//先遍历主链看是否已有该word，有则直接加入子链，否则先在主链创建节点，再加入子链
    int flag = 0;//标志，word已在主链中为1，否则为0
    nodeout *p = head;//工作指针
    int i = 0;//查询主链的下标
    while (p->next!=NULL)//遍历寻找
    {
        p = p->next;
        i++;
        char* word_inquire=(char*)malloc(sizeof(char));//带出inquire的结果
        if(word_inquire==NULL)
        {
            printf("malloc fail in add for word_inquire\n");
            return fail;
        }
        Inquireout(head,i,&word_inquire);//查询
        if (strcmp(word,word_inquire)==0)//比较
        {
            flag = 1;//找到相同，说明word在主链中
            break;//退出循环
        }
    }
    if (flag == 1)//若在主链中
    {
        infoin rowin = {row};
        insertin(p->word.headin, rowin, lengthin(p->word.headin) + 1);//直接插入到对应子链
    }
    else//若不在主链中
    {
        nodein *headin = (nodein *)malloc(sizeof(nodein));
        InitIn(headin);
        infoin rowin = {row};
        insertin(headin,rowin,lengthin(headin)+1);//先创建子链并插入到子链中
        char* tmp=(char*)malloc(20*sizeof(char));//不能把word直接插入，因为word是一个指针，在其他地方修改会导致此处被改变，建议const
        if(tmp==NULL){
            printf("malloc fail in add for tmp");
            return fail;
        }
        strcpy(tmp,word);//用tmp代替word
        infoout wordout = {headin, tmp};
        insertout(head, wordout, lengthout(head)+1);//插入主链
    }
}
int deal(char **str, int row, nodeout *head, char *word)//处理读入的字符串
{                                         
    char *temp = *str;                    //由于*str在getword中被修改，因此存下
    while (getword(str, word) == success) //从str中取出一个word,若还能找到词
    {
        if (isKeyWord(word) == success) //若该词在保留字集中
        {
            add(head, word, row); //就将词和行号加入链表
        }
        else if (isKeyWord(word) == fail) //若该词不在保留字集中
        {
            continue; //就接着寻找
        }
    }
    *str = temp;          //处理完一行，改回*str
}
int read(nodeout *head)//从文件读入数据，记录行号到链表，最后看链表长度即可知道出现次数，输出的时候再去重
{ 
    char filename[]="./literature.c";//相对地址
    FILE *fp = fopen(filename, "r");//打开文件
    if (fp == NULL)
    {
        printf("fail to open file\n");
        return fail;
    }
    //先读一行到str，取出单词，看是否在保留字符集中，是则加入到链中，否则继续扫描
    int row = 0;//当前行号
    //为了修改str可传回，使用指向指针的指针
    char **str = (char **)malloc(sizeof(char *)); //先为str申请空间
    if (str == NULL)
    {
        printf("malloc fail in read for str");
        return fail;
    }
    *str = (char *)malloc(150 * sizeof(char));//再为*str申请空间，假设一行不超过150个字节
    if (*str == NULL)
    {
        printf("malloc fail in read for *str\n");
        return fail;
    }
    char *word = (char *)malloc(20 * sizeof(char));//从str中取出的word，假设word字长不超过20
    if (word == NULL)
    {
        printf("malloc fail in read for word\n");
        return fail;
    }

    while (!feof(fp))//一直到把文件读完
    {
        row++;//行数增加
        fgets(*str, 150, fp);//读入一行到str
        deal(str, row, head, word);//处理数据
    }
    free(word);//释放空间
    word = NULL;
    free(*str);
    *str = NULL;
    free(str);
    str = NULL;
    fclose(fp);
}
int wordprint(nodeout* head){//打印统计结果
    nodeout *p = head;
    printf("In this text, words and their rows are:\n");
    while (p->next != NULL)//遍历主链打印结果
    {
        p = p->next;
        printf("%10s appears %3d times: ",p->word.word,lengthin(p->word.headin));//打印word
        nodein* pin=p->word.headin;
        int row_many=0;//记录输出的上个行数
        while(pin->next!=NULL){////遍历子链打印行号
            pin=pin->next;
            if(pin->row.row==row_many){//若改行号已经打印过
                continue;//就查看下一个
            }else {//若没打印过
                printf("%d ",pin->row.row);//就打印
                row_many=pin->row.row;//记录这个刚打印的行号
            }
        }
        printf("\n");//打完一行
    }
    return success;
}
//主函数
int main()
{
    nodeout *head = (nodeout *)malloc(sizeof(nodeout)); //在主函数中申请头节点
    Initout(head);                                      //初始化
    read(head);//读入并处理数据
    wordprint(head);//打印结果
    return 0;
}
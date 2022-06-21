#include "list_2d.c"

//literature
int getword(char* wordx,char **str,nodeout* headout) //在函数中修改str传不回去，使用指向指针的指针
{                                   //得到这个字符串的第一个word，并删掉它，找不到word就返回fail,找到返回success
    //两个非字母之间的即视为一个word
    printf("before memset\n");
    printout(headout);
    printf("\n");
    
    printf("wordx:%p\n",wordx);
//    printf("%p\n",&(headout->next->word.word));
    
    memset(wordx, 0, 20*sizeof(char));//bug,鍐呭瓨婧㈠嚭
    
    printf("after memset\n");
    printout(headout);
    printf("\n");
    if (strlen(*str) == 0) //str为空时返回fail
    {
        return fail;
    }
    int i = 0;
    int pos = 0;
    printf("before while\n");
    printout(headout);
    printf("\n");
    while (1)
    {
        if ((*(*str + i) >= 'A' && *(*str + i) <= 'Z') || (*(*str + i) >= 'a' && *(*str + i) <= 'z'))
        {
            wordx[pos++] = *(*str + i); //若是字母就连接到word中去
            i++;
        }
        else
        {
            break; //不是字母就选取结束
        }
    }
    printf("after while\n");
    printout(headout);
    printf("\n");
     printf("word:");
     printf("%s\n", wordx);
    *str = *str + i; //删掉取出的word
    if (strlen(*str) == 0)
    { //str第一次为空是刚取完时，故成功
        return success;
    }
    *str = *str + 1; //再删掉不是字母的那个字符
    // printf("str:");
    // printf("%s", *str);
    return success;
}
int isKeyWord(char *word)
{ //若word在字符集中就返回success,否则返回fail
    //类型说明保留字:int,long,short,float,double,char,unsigned,signed,const,void,volatile,enum,struct,union
    //语句定义保留字:if,else,goto,switch,case,do,while,for,continue,break,return,default,typedef
    // 存储类说明保留字:auto,register,extern,
    // static长度运算符保留字:sizeof
    // printf("%s\n",word);
    char esp[][31]={"int","long","short","float","double","char","unsignes","signed","const",
    "void","volatile","enum","struct","union","if","else","goto","switch","case","do",
    "while","for","continue","break","return","default","typedef","auto","register",
    "extern","sizeof"};
    int flag=0;
    for(int i=0;i<31;i++){
        // printf("%s",esp[i]);
        if(strcmp(word,esp[i])==0){
            flag=1;
            break;
        }
    }
    if (flag==1)
    {
        return success;
    }
    else
    {
        return fail;
    }
    return success;
}
int add(nodeout *head, char* word, int row) //将行号加入二重链表
{//先遍历主链看是否已有该word，有则直接加入子链，否则先在主链创建节点，再加入子链
//printout(head);
    int flag = 0;
    // printf("%p\n",head);
    nodeout *p = head;
    int i = 0;
    // printf("this word:%s\n",word);
    // printf("flag:%d\n",flag);
    while (p->next!=NULL)
    {
        p = p->next;
        i++;
        char* word_inquire=(char*)malloc(sizeof(char));
        if(word_inquire==NULL)
        {
            printf("malloc fail in add for word_inquire\n");
            return fail;
        }
        Inquireout(head,i,&word_inquire);
        printf("inquire result of %d is: %s\n",i,word_inquire);
        if (strcmp(word,word_inquire)==0)
        {
            flag = 1;
            break;
        }
    }
    // printf("flag:%d\n",flag);
    if (flag == 1)
    {
        infoin rowin = {row};
        insertin(p->word.headin, rowin, lengthin(p->word.headin) + 1);
//        printf("word:%s\n",p->word.word);
        printin(p->word.headin);
        printf("if successly exe\n");
    }
    else
    {
        nodein *headin = (nodein *)malloc(sizeof(nodein));
        InitIn(headin);
        infoin rowin = {row};
        insertin(headin,rowin,lengthin(headin)+1);
        char* temp=(char*)malloc(20*sizeof(char));
        strcpy(temp,word);
        infoout wordout = {headin, temp};
        insertout(head, wordout, lengthout(head)+1);
        printout(head);
        printin(headin);
        printf("else successly exe\n");
    }
    // printf("%p\n",head);
//    printout(head);
    printf("\n");
    return success;
}
int wordPrint(nodeout *head)
{ //输出每个保留字出现的字数和出现的行号
    printf("\n");
    return success;
}
int deal(char **str, int row, nodeout *head)
{                                         //处理读入的字符串
    char *temp = *str;                    //由于*str在getword中被修改，因此存
//	char *word = (char *)malloc(20 * sizeof(char));
//    if (word == NULL)
//    {
//        printf("malloc fail in read for word\n");
//        return fail;
//    }
char word[20];
    memset(word,0,sizeof(char));
    printf("deal_word:%p\n",word);
//    printout(head);
    while (getword(word,str,head)==success) //若还能找到词
    {
        if (isKeyWord(word) == success) //若该词在保留字集中
        {
            printf("%d\n",isKeyWord(word));
            add(head, word, row); //就将行号加入链表
        }
        else if (isKeyWord(word) == fail) //若该词不在保留字集中
        {
            printf("%d\n",isKeyWord(word));
            continue; //就接着寻找
        }
    }
    *str = temp;          //处理完一行，改回*str
//    free(word);
//    word=NULL;
    return success;
}
int read(nodeout *head)
{ //从文件读入数据，记录行号到链表，最后看链表长度即可知道出现次数，输出的时候再去重
    char filename[] = "C:\\Users\\mashed potato\\Desktop\\list.c";
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("fail to open file\n");
        return fail;
    }
    //先读一行到str，取出单词，看是否在保留字符集中，是则加入到链中，否则继续扫描
    int row = 0;

    char **str = (char **)malloc(sizeof(char *)); //为了修改str可传回，使用指向指针的指针
    if (str == NULL)
    {
        printf("malloc fail in read for str");
        return fail;
    }
    *str = (char *)malloc(150 * sizeof(char));
    if (*str == NULL)
    {
        printf("malloc fail in read for *str\n");
        return fail;
    }
    // memset(*str,0,150*sizeof(char));
    // char *word = (char*)calloc(20,sizeof(char)); //存放分出的词
    
    while (!feof(fp))
    {
        row++;
         printf("%d", row);
        fgets(*str, 150, fp);
        // fflush(fp);
        // printf("%s", *str);
        deal(str, row, head);
//        printf("when deal is over:\n");
//        printout(head);
    }
    free(*str);
    *str = NULL;
    free(str);
    str = NULL;
    fclose(fp);
    return success;
}
//主函数
int main()
{
    nodeout *head = (nodeout *)malloc(sizeof(nodeout)); //在主函数中申请头节点
    Initout(head);                                      //初始化
    read(head);
    printout(head);
    wordPrint(head);
    return 0;
}

#include "list_2d.c"

//literature
int getword(char* wordx,char **str,nodeout* headout) //�ں������޸�str������ȥ��ʹ��ָ��ָ���ָ��
{                                   //�õ�����ַ����ĵ�һ��word����ɾ�������Ҳ���word�ͷ���fail,�ҵ�����success
    //��������ĸ֮��ļ���Ϊһ��word
    printf("before memset\n");
    printout(headout);
    printf("\n");
    
    printf("wordx:%p\n",wordx);
//    printf("%p\n",&(headout->next->word.word));
    
    memset(wordx, 0, 20*sizeof(char));//bug,内存溢出
    
    printf("after memset\n");
    printout(headout);
    printf("\n");
    if (strlen(*str) == 0) //strΪ��ʱ����fail
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
            wordx[pos++] = *(*str + i); //������ĸ�����ӵ�word��ȥ
            i++;
        }
        else
        {
            break; //������ĸ��ѡȡ����
        }
    }
    printf("after while\n");
    printout(headout);
    printf("\n");
     printf("word:");
     printf("%s\n", wordx);
    *str = *str + i; //ɾ��ȡ����word
    if (strlen(*str) == 0)
    { //str��һ��Ϊ���Ǹ�ȡ��ʱ���ʳɹ�
        return success;
    }
    *str = *str + 1; //��ɾ��������ĸ���Ǹ��ַ�
    // printf("str:");
    // printf("%s", *str);
    return success;
}
int isKeyWord(char *word)
{ //��word���ַ����оͷ���success,���򷵻�fail
    //����˵��������:int,long,short,float,double,char,unsigned,signed,const,void,volatile,enum,struct,union
    //��䶨�屣����:if,else,goto,switch,case,do,while,for,continue,break,return,default,typedef
    // �洢��˵��������:auto,register,extern,
    // static���������������:sizeof
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
int add(nodeout *head, char* word, int row) //���кż����������
{//�ȱ����������Ƿ����и�word������ֱ�Ӽ��������������������������ڵ㣬�ټ�������
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
{ //���ÿ�������ֳ��ֵ������ͳ��ֵ��к�
    printf("\n");
    return success;
}
int deal(char **str, int row, nodeout *head)
{                                         //���������ַ���
    char *temp = *str;                    //����*str��getword�б��޸ģ���˴�
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
    while (getword(word,str,head)==success) //�������ҵ���
    {
        if (isKeyWord(word) == success) //���ô��ڱ����ּ���
        {
            printf("%d\n",isKeyWord(word));
            add(head, word, row); //�ͽ��кż�������
        }
        else if (isKeyWord(word) == fail) //���ôʲ��ڱ����ּ���
        {
            printf("%d\n",isKeyWord(word));
            continue; //�ͽ���Ѱ��
        }
    }
    *str = temp;          //������һ�У��Ļ�*str
//    free(word);
//    word=NULL;
    return success;
}
int read(nodeout *head)
{ //���ļ��������ݣ���¼�кŵ�������������ȼ���֪�����ִ����������ʱ����ȥ��
    char filename[] = "C:\\Users\\mashed potato\\Desktop\\list.c";
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("fail to open file\n");
        return fail;
    }
    //�ȶ�һ�е�str��ȡ�����ʣ����Ƿ��ڱ����ַ����У�������뵽���У��������ɨ��
    int row = 0;

    char **str = (char **)malloc(sizeof(char *)); //Ϊ���޸�str�ɴ��أ�ʹ��ָ��ָ���ָ��
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
    // char *word = (char*)calloc(20,sizeof(char)); //��ŷֳ��Ĵ�
    
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
//������
int main()
{
    nodeout *head = (nodeout *)malloc(sizeof(nodeout)); //��������������ͷ�ڵ�
    Initout(head);                                      //��ʼ��
    read(head);
    printout(head);
    wordPrint(head);
    return 0;
}

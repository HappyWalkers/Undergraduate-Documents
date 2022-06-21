#include<iostream>
#include<io.h>
#include<string>
#include<fstream>
using namespace std;

ofstream outfile;
typedef struct{//哈夫曼树的节点
    char ch;
    int weight;
    int parent,lchild,rchild;
}HTNode;
typedef HTNode* HuffmanTree;
void swap(int* a,int* b){//交换数值
    int temp=*a;
    *a=*b;
    *b=temp;
}
void select(HuffmanTree ht,int n,int length,int* s1,int* s2){
    //在ht［1］~ht［i-1］的范围内选择两个parent为0且weight最小的结点
    //其序号分别赋值给s1、 s2返回
    //先将parent为0的挑出其下标组成数组，按weight排序，取前两位
    int* index=(int*)malloc((2*n-length)*sizeof(int));//数组
    int p=0;
    for(int i=1;i<=length;i++){//将parent为0的挑出其下标组成数组
        if(ht[i].parent==0){
            index[p++]=i;
        }
    }
    for(int i=0;i<2*n-length;i++){//选择排序
        for(int j=i+1;j<2*n-length;j++){
            if(ht[index[i]].weight>ht[index[j]].weight){
                swap(&index[i],&index[j]);
            }
        }
    }
    *s1=index[0];
    *s2=index[1];
}
HuffmanTree CrtHuffmanTree(int* weight,int n,char* charset){//创建哈夫曼树
    HuffmanTree ht;
    int ArrayLength=2*n-1;//树长
    ht=(HuffmanTree)malloc((ArrayLength+1)*sizeof(HTNode));
    for(int i=0;i<=n;i++){//叶子节点初始化
        ht[i].ch=charset[i];
        ht[i].weight=weight[i];
        ht[i].parent=0;
        ht[i].lchild=0;
        ht[i].rchild=0;
    }
    for(int i=n+1;i<=ArrayLength;i++){//其他节点初始化
        ht[i].ch=0;
        ht[i].weight=0;
        ht[i].parent=0;
        ht[i].lchild=0;
        ht[i].rchild=0;
    }
    int s1=0;
    int s2=0;
    for(int i=n+1;i<=ArrayLength;i++){
        select(ht,n,i-1,&s1,&s2);//挑出weight最小的两个下标
        // printf("%d %d %d\n",i,s1,s2);
        ht[s1].parent=i;//叶子的父节点
        ht[s2].parent=i;
        ht[i].lchild=s1;//父节点的孩子节点
        ht[i].rchild=s2;
        ht[i].weight=ht[s1].weight+ht[s2].weight;//父节点的weight
    }
    return ht;
}

void printHuffmanTree(HuffmanTree ht,int n){//打印哈夫曼树的表格
    printf("char\tweight\tparent\tlchild\trchild\n");
    for(int i=1;i<=2*n-1;i++){
        printf("%c\t%d\t%d\t%d\t%d\n",ht[i].ch,ht[i].weight,ht[i].parent,
        ht[i].lchild,ht[i].rchild);
    }
}

void cHc(HuffmanTree ht,int index,string code){//递归计算哈夫曼编码
    if(ht[index].lchild==0 && ht[index].rchild==0){//到达树叶就输出
        // cout<<ht[index].ch<<"\t"<<code<<endl;
        outfile<<ht[index].ch<<"\t"<<code<<endl;
        return;
    }
    cHc(ht,ht[index].lchild,code+"0");//左边加0
    cHc(ht,ht[index].rchild,code+"1");//右边加1
}

void calcHuffmanCode(HuffmanTree ht,int n){ //计算哈夫曼编码
    string left="0";
    string right="1";
    cHc(ht,ht[2*n-1].lchild,left);//左边0
    cHc(ht,ht[2*n-1].rchild,right);//右边1
}

template<typename t> int find_element_in_array(t dest,t array[],int array_size){//寻找数组中dest的位置，没找到就返回-1
    for(int i=0;i<array_size;i++){
        if(dest==array[i]){
            return i;
        }
    }
    cout<<"did not find char in array"<<endl;
    return -1;
}

void enCoding()//用hfmTree.txt中的代码对ToBeTran.txt中的内容进行编码，并输出到CodeFile
{
    //打开文件
    ifstream hfmTree;
    hfmTree.open("./hfmTree.txt",ios::in);
    ifstream ToBeTran;
    ToBeTran.open("./ToBeTran.txt",ios::in);
    ofstream codeFile;
    codeFile.open("./CodeFile.txt",ios::out);

    char ch[36];
    string ch_code[36];
    int i=0;
    while(!hfmTree.eof()){
        hfmTree>>ch[i]>>ch_code[i];//从文件中读取编码到数组
        i++;
    }

    char temp;
    while(!ToBeTran.eof()){
        ToBeTran>>temp;
        if(find_element_in_array(temp,ch,sizeof(ch)/sizeof(char))==-1)continue;
        codeFile<<ch_code[find_element_in_array(temp,ch,sizeof(ch)/sizeof(char))];//根据数组中的编码，将字符替换为01存入文件

    }
    hfmTree.close();//关闭文件
    ToBeTran.close();
    codeFile.close();
}

void deCoding()//跟据hfmTree.txt,将CodeFile.txt中的代码翻译到TextFile.txt中
{
    ifstream hfmTree;//打开文件
    hfmTree.open("./hfmTree.txt",ios::in);
    ifstream codeFile;
    codeFile.open("./CodeFile.txt",ios::in);
    ofstream textFile;
    textFile.open("./TextFile.txt",ios::out);

    char ch[36];
    string ch_code[36];
    int i=0;
    while(!hfmTree.eof()){
        hfmTree>>ch[i]>>ch_code[i];//从文件读入编码
        i++;
    }

    string code;
    getline(codeFile,code);
    string temp;
    temp=code[0];
    int j=0;
    while(true){//根据数组中的编码，将01..译为字符
        if(j>=code.length())break;
        if(find_element_in_array(temp,ch_code,sizeof(ch_code)/sizeof(string))==-1){
            temp=temp+code[++j];
        }else{
            textFile<<ch[find_element_in_array(temp,ch_code,sizeof(ch_code)/sizeof(string))];
            temp=code[++j];
        }
    }
    hfmTree.close();//关闭文件
    codeFile.close();
    textFile.close();
}

void print_and_write()//将codeFile.txt打印到终端，并写入到CodePrint.txt中
{
    ifstream codeFile;//打开文件
    codeFile.open("./CodeFile.txt",ios::in);
    ofstream codePrint;
    codePrint.open("./CodePrint.txt",ios::out);

    string code;
    getline(codeFile,code);//读入编码
    for(int i=0;i<code.length();i++){
        cout<<code[i];
        codePrint<<code[i];
        if((i+1)%50==0){//每输出50个字符，换行
            cout<<endl;
            codePrint<<endl;
        }
    }
}
int main(){
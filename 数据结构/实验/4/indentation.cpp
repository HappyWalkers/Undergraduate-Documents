#include<iostream>
using namespace std;
typedef struct
{ //树节点的数据
    char data;
} TElemType;

typedef struct BiTNode
{ //二叉树节点
    TElemType data;
    struct BiTNode *lchild, *rchild; //左右孩子节点
} BiTNode;

void grow(BiTNode *root, TElemType le, TElemType re)
{                                                      //从节点长出左右子树
    root->lchild = (BiTNode *)malloc(sizeof(BiTNode)); //左子
    if (root->lchild == NULL)
    {
        printf("malloc fail in grow for root->lchild\n");
        return;
    }
    root->rchild = (BiTNode *)malloc(sizeof(BiTNode)); //右子
    if (root->rchild == NULL)
    {
        printf("malloc fail in grow for root->lchild\n");
        return;
    }
    root->lchild->data = le; //le为左子的数据
    root->lchild->lchild = NULL;
    root->lchild->rchild = NULL;
    root->rchild->data = re; //re为右子的数据
    root->rchild->lchild = NULL;
    root->rchild->rchild = NULL;
}

//凹入表打印树结构

void printHelp(BiTNode *p, string ss)//递归打印

{
    if (p == NULL)
        return;
    ss += "   ";//每往下一层就加一个空位
    printHelp(p->rchild, ss);
    cout << ss << p->data.data << endl;//中序遍历
    printHelp(p->lchild, ss);
}

//凹入表打印

void print(BiTNode *root)//打印树

{
    string ss = "";
    printHelp(root, ss);
}

int main()
{
    BiTNode root; //树根
    TElemType rootE = {'r'};
    root.data = rootE;
    root.lchild = NULL;
    root.rchild = NULL;

    TElemType a = {'a'}; //测试
    TElemType b = {'b'};
    TElemType c = {'c'};
    TElemType d = {'d'};
    TElemType e = {'e'};
    TElemType f = {'f'};
    grow(&root, a, b);
    grow(root.lchild, c, d);
    grow(root.rchild, e, f);

    print(&root);
    return 0;
}
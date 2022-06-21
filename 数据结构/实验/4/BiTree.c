#include<stdio.h>
#include<stdlib.h>
typedef struct{//树节点的数据
    char data;
}TElemType;
typedef struct BiTNode{//二叉树节点
    TElemType data;
    struct BiTNode *lchild,*rchild;//左右孩子节点
}BiTNode;
void Visit(TElemType e){//访问节点数据
    printf("%c\n",e.data);
}
void PreOrder(BiTNode* T){//先序遍历
    if(T==NULL){//空则返回
        return;
    }
    Visit(T->data);//先访问根节点
    PreOrder(T->lchild);//再以先序访问左子树
    PreOrder(T->rchild);//最后以先序访问右子树
}
void InOrder(BiTNode* T){//中序遍历
    if(T==NULL){
        return;
    }
    InOrder(T->lchild);
    Visit(T->data);
    InOrder(T->rchild);
}
void AftOrder(BiTNode* T){//后序遍历
    if(T==NULL){
        return;
    }
    AftOrder(T->lchild);
    AftOrder(T->rchild);
    Visit(T->data);
}
BiTNode* GetTreeNode(TElemType item,BiTNode* lptr,BiTNode* rptr){//连接树节点，返回根
    BiTNode* T=(BiTNode*)malloc(sizeof(BiTNode));//根
    if(T==NULL){
        printf("malloc fail in GetTreeNode for T\n");
        return NULL;
    }
    T->data=item;//根的数据
    T->lchild=lptr;
    T->rchild=rptr;
    return T;
}
BiTNode* CopyTree(BiTNode* T){//复制树
    if(T==NULL){//空则返回
        return NULL;
    }
    BiTNode* newT=(BiTNode*)malloc(sizeof(BiTNode));//根
    if(newT==NULL){
        printf("malloc fail in CopyTree for newT\n");
        return NULL;
    }
    BiTNode* newlptr=(BiTNode*)malloc(sizeof(BiTNode));//左子
    if(newlptr==NULL){
        printf("malloc fail in CopyTree for newlptr\n");
        return NULL;
    }
    BiTNode* newrptr=(BiTNode*)malloc(sizeof(BiTNode));//右子
    if(newrptr==NULL){
        printf("malloc fail in CopyTree for newrptr");
        return NULL;
    }

    if(T->lchild!=NULL){//左子树不为空就复制左子树
        newlptr=CopyTree(T->lchild);
    }
    else{
        newlptr=NULL;//否则置空
    }
    if(T->rchild!=NULL){
        newrptr=CopyTree(T->rchild);//as
    }
    else{
        newrptr=NULL;//as
    }
    newT=GetTreeNode(T->data,newlptr,newrptr);//将复制好的左子树和右子树连接到根节点上
    return newT;
}
void grow(BiTNode* root,TElemType le,TElemType re){//从节点长出左右子树
    root->lchild=(BiTNode*)malloc(sizeof(BiTNode));//左子
    if(root->lchild==NULL){
        printf("malloc fail in grow for root->lchild\n");
        return;
    }
    root->rchild=(BiTNode*)malloc(sizeof(BiTNode));//右子
    if(root->rchild==NULL){
        printf("malloc fail in grow for root->lchild\n");
        return;
    }
    root->lchild->data=le;//le为左子的数据
    root->lchild->lchild=NULL;
    root->lchild->rchild=NULL;
    root->rchild->data=re;//re为右子的数据
    root->rchild->lchild=NULL;
    root->rchild->rchild=NULL;
}
int main(){
    BiTNode root;//树根
    TElemType rootE={'r'};
    root.data=rootE;
    root.lchild=NULL;
    root.rchild=NULL;

    TElemType a={'a'};//测试
    TElemType b={'b'};
    TElemType c={'c'};
    TElemType d={'d'};
    TElemType e={'e'};
    TElemType f={'f'};
    grow(&root,a,b);
    grow(root.lchild,c,d);
    grow(root.rchild,e,f);

    printf("PreOrder\n");
    PreOrder(&root);
    printf("InOrder\n");
    InOrder(&root);
    printf("AftOrder\n");
    AftOrder(&root);

    printf("PreOrder of CopyTree\n");
    PreOrder(CopyTree(&root));
    return 0;
}
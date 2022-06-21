#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_VERTEX_NUM 30//图的最大顶点数目

//队列
#define ok 0
#define fail 1
#define underflow -1
typedef int QElemType;
typedef struct QNode
{ //节点
    QElemType data;
    struct QNode *next; //链队列
} QNode;
typedef struct
{
    QNode *front; //头指针，带空头节点
    QNode *rear;  //尾节点
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
#define empty 0
#define notempty 1
int isempty(LinkQueue q){
    if(q.front==q.rear){
        return empty;
    }else{
        return notempty;
    }
}

//图
typedef char vertexType;//顶点数据类型
typedef enum{DG,DN,UDG,UDN}GraphKind;//图的类型
typedef struct  arcNode{//边
    int adjvex;//边上数据，指向其父节点下一个邻接点在顶点数组中的位置
    struct arcNode *nextarc;//指向下一条边
}arcNode;

typedef struct vnode{//顶点
    vertexType vexData;//顶点数据
    arcNode *firstarc;//指向第一个邻接点的边
}vnode;

typedef struct{//图
    vnode* vertices;//顶点数组
    int vexnum,arcnum;//顶点数目，边的数目
    GraphKind kind;//图类型
}alGraph;

void printVertices(alGraph* g){//打印邻接表
    for(int i=0;i<g->vexnum;i++){//遍历顶点数组
        printf("%c ",g->vertices[i].vexData);
        //遍历每个顶点的所有边
        arcNode* a=(arcNode*)malloc(sizeof(arcNode));
        a=g->vertices[i].firstarc;
        while(a!=NULL){
            printf("%d ",a->adjvex);
            a=a->nextarc;
        }
        printf("\n");
    }
}

int locateVex(alGraph* g,char vex){//确定点vex在邻接表中的位置
    for(int i=0;i<g->vexnum;i++){//遍历比较
        if(g->vertices[i].vexData==vex){
            return i;
        }
    }
    printf("vex not exist in locateVex:%c\n",vex);
    return -1;//没找到返回-1
}

void CreateGraph(alGraph* g){//先序输入图
    printf("输入顶点数，边数和图类\n");
    scanf("%d%d%d",&(g->vexnum),&(g->arcnum),&(g->kind));
    g->vertices=(vnode*)malloc(g->vexnum*sizeof(vnode));
// printf("%d %d %d",g->vexnum,g->arcnum,g->kind);

    printf("输入顶点\n");
    for(int i=0;i<g->vexnum;i++){
        printf("第%d个顶点：\n",i+1);
        getchar();//清掉回车
        g->vertices[i].vexData=getchar();
        // putchar(g->vertices[i].vexData);
        g->vertices[i].firstarc=NULL;//尾部置空
    }

    // printVertices(g);
    printf("输入边\n");
    for(int i=0;i<g->arcnum;i++){
        char sv;
        char tv;
        getchar();//清掉回车
        printf("第%d条边：\n",i+1);
        scanf("%c%c",&sv,&tv);
        // printf("%c,%c\n",sv,tv);
        int s=locateVex(g,sv);
        int t=locateVex(g,tv);

        arcNode* pi=(arcNode*)malloc(sizeof(arcNode));
        pi->adjvex=t;
        pi->nextarc=g->vertices[s].firstarc;//头插法
        g->vertices[s].firstarc=pi;

        if(g->kind==UDG || g->kind==UDN){//若是无向图或无向网，在边的另一端也要加入边
            arcNode* pj=(arcNode*)malloc(sizeof(arcNode));
            pj->adjvex=s;
            pj->nextarc=g->vertices[t].firstarc;//头插法
            g->vertices[t].firstarc=pj;
        }
    }
    // printVertices(g);
}

int* createVisted(int size){//返回一个size大小的置0数组
    int* visited=(int*)malloc(size*sizeof(int));
    memset(visited,0,size*sizeof(int));
    return visited;
}

void visit(vertexType v){//访问顶点数据
    printf("%c",v);
}

int firstAdjVex(alGraph* g,int v){//返回某顶点的第一个邻接点
    if(g->vertices[v].firstarc==NULL)return -1;//无邻接点时，返回-1
    return g->vertices[v].firstarc->adjvex;
}

int nextAdjVex(alGraph* g,int v,int w){//返回某顶点的w之后的一个邻接点，v是当前父节点,w为上一个访问的邻接点
    arcNode* a=(arcNode*)malloc(sizeof(arcNode));
    a=g->vertices[v].firstarc;
    if(a==NULL)return -1;
    while(a->adjvex!=w){//遍历寻找w
        if(a==NULL)return -1;//到底返回-1
        a=a->nextarc;
    }
    if(a->nextarc==NULL)return -1;//若是最后一个点，返回-1
    return a->nextarc->adjvex;//找到就返回下一个邻接点
}
void DFS(alGraph* g,int v,int* visited){//深度优先遍历
    visited[v]=1;//已访问，置1
    visit(g->vertices[v].vexData);
    for(int w=firstAdjVex(g,v);w!=-1;w=nextAdjVex(g,v,w)){//遍历所有邻接点，深度优先访问它们
        // printf("#%d#",w);
        if(visited[w]==0){
            DFS(g,w,visited);
        }
    }
}

void DFS_unconnected(alGraph* g,int v,int* visited){//非连通图的深度优先遍历
    for(int i=0;i<g->vexnum;i++){//遍历该图所有点，对未访问的顶点，深度优先遍历
        // printf("%d",i);
        if(visited[i]==0){
            DFS(g,i,visited);
        }
        // printf("hhh");
    }
    printf("\n");
}

void BFS(alGraph* g,int v,int* visited,LinkQueue* q){//广度优先遍历
    visited[v]=1;
    visit(g->vertices[v].vexData);
    EnQueue(q,v);//入队要访问的顶点
    while(isempty(*q)==notempty){//当队列不为空时
        int u;
        DeQueue(q,&u);//从队列取出要访问的点，置为u
        for(int w=firstAdjVex(g,u);w!=-1;w=nextAdjVex(g,u,w)){//遍历u的所有邻接点
            if(visited[w]==0){//若未访问就访问
                visited[w]=1;
                visit(g->vertices[w].vexData);
                EnQueue(q,w);//将u的邻接点入队
            }
        }
    }
}

void BFS_unconnected(alGraph* g,int v,int* visited){//非连通图的广度优先遍历
    LinkQueue* q=(LinkQueue*)malloc(sizeof(LinkQueue));//设置一个队列，用来存放将要访问的顶点
    InitQueue(q);
    for(int v=0;v<g->vexnum;v++){//遍历该图所有点，广度优先访问
        if(visited[v]==0){
            BFS(g,v,visited,q);
        }
    }
}
 int main(){//测试
     alGraph* g=(alGraph*)malloc(sizeof(alGraph));
     if(g==NULL){
         printf("malloc fail in main for g\n");
         return -1;
     }
     CreateGraph(g);
    //  printVertices(g);//查看邻接表
     printf("输入遍历起点：\n");
     getchar();//清掉回车
     char start=getchar();
     printf("深度优先遍历结果：\n");
    //  DFS(g,locateVex(g,start),createVisted(g->vexnum));
     DFS_unconnected(g,locateVex(g,start),createVisted(g->vexnum));
     printf("广度优先遍历结果：\n");
    //  BFS(g,locateVex(g,start),createVisted(g->vexnum));
    BFS_unconnected(g,locateVex(g,start),createVisted(g->vexnum));
     return 0;
 }
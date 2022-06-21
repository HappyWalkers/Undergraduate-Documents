#include<iostream>
#include<string>
#include<cstring>
using namespace std;
#define MAX_VERTEX_NUM 30//图的最大顶点数目

//图
typedef char vertexType;//顶点数据类型
typedef enum{DG,DN,UDG,UDN}GraphKind;// 定义图的类型 { 有向图, 有向网,无向图, 无向网}
typedef struct  arcNode{//边
    int adjvex;//边上数据，指向其父节点下一个邻接点在顶点数组中的位置
    int weight;//边权重
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
            printf("%d&%d ",a->adjvex,a->weight);
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

    printf("输入顶点\n");
    for(int i=0;i<g->vexnum;i++){
        printf("第%d个顶点：\n",i+1);
        getchar();//清掉回车
        g->vertices[i].vexData=getchar();
        g->vertices[i].firstarc=NULL;//尾部置空
    }

    printf("输入边和权重\n");
    for(int i=0;i<g->arcnum;i++){
        char sv;
        char tv;
        int w;
        getchar();//清掉回车
        printf("第%d条边和权重：\n",i+1);
        scanf("%c%c",&sv,&tv);
        scanf("%d",&w);
        int s=locateVex(g,sv);
        int t=locateVex(g,tv);

        arcNode* pi=(arcNode*)malloc(sizeof(arcNode));
        pi->adjvex=t;
        pi->weight=w;
        pi->nextarc=g->vertices[s].firstarc;//头插法
        g->vertices[s].firstarc=pi;

        if(g->kind==UDG || g->kind==UDN){//若是无向图或无向网，在边的另一端也要加入边
            arcNode* pj=(arcNode*)malloc(sizeof(arcNode));
            pj->adjvex=s;
            pj->weight=w;
            pj->nextarc=g->vertices[t].firstarc;//头插法
            g->vertices[t].firstarc=pj;
        }
    }
}

void visit(vertexType v){//访问顶点数据
    printf("%c",v);
}

int find_element_in_array(char dest,vnode array[],int array_size){//在数组中寻找元素位置，找到返回，没找到返回-1
    for(int i=0;i<array_size;i++){
        if(dest==array[i].vexData){
            return i;
        }
    }
    // cout<<"fail to find element"<<endl;
    return -1;
}


void prim(alGraph* g,char start){
    alGraph p;//用邻接表存最小生成树
    p.vertices=(vnode*)malloc(g->vexnum*sizeof(vnode));
    p.vertices[0].vexData=start;
    p.vertices[0].firstarc=NULL;
    p.vexnum=1;
    p.arcnum=0;
    p.kind=UDN;
    while(true){
        if(p.vexnum==g->vexnum)break;//Vnew更新完则退出循环
        int min_weight=100;//假设所有边权重不超过100
        int min_index=0;
        int min_index_source=0;
        for(int i=0;i<p.vexnum;i++){//遍历Vnew所有边
            int index_find=find_element_in_array(p.vertices[i].vexData,g->vertices,g->vexnum);
            // cout<<index_find<<endl;
            if(index_find!=-1){//若在g中找到该点,遍历该点所有邻接边，查找权重最小的边
                arcNode* a=(arcNode*)malloc(sizeof(arcNode));
                a=g->vertices[index_find].firstarc;
                if(a==NULL)continue;
                while(true){
                    if(a==NULL)break;
                    if(a->weight<min_weight && find_element_in_array(g->vertices[a->adjvex].vexData,p.vertices,p.vexnum)==-1){//若找到更小权值的边（该边另一端点不在Vnew中）
                        min_weight=a->weight;
                        min_index=a->adjvex;
                        min_index_source=i;
                    }
                    a=a->nextarc;
                }
            }
        }
        //找到权重最小的之后，更新Vnew和Enew
        p.vertices[p.vexnum].vexData=g->vertices[min_index].vexData;
        p.vertices[p.vexnum].firstarc=NULL;

        arcNode* pi=(arcNode*)malloc(sizeof(arcNode));
        pi->adjvex=p.vexnum;
        pi->weight=min_weight;
        pi->nextarc=p.vertices[min_index_source].firstarc;//头插法
        p.vertices[min_index_source].firstarc=pi;

        if(p.kind==UDG || p.kind==UDN){//若是无向图或无向网，在边的另一端也要加入边
            arcNode* pj=(arcNode*)malloc(sizeof(arcNode));
            pj->adjvex=min_index_source;
            pj->weight=min_weight;
            pj->nextarc=p.vertices[p.vexnum].firstarc;//头插法
            p.vertices[p.vexnum].firstarc=pj;
        }
        p.vexnum++;
        // printVertices(&p);
    }
    printVertices(&p);
}
 int main(){//测试
     alGraph* g=(alGraph*)malloc(sizeof(alGraph));
     if(g==NULL){
         printf("malloc fail in main for g\n");
         return -1;
     }
     CreateGraph(g);
     printVertices(g);//查看邻接表
     printf("输入起点：\n");
     getchar();//清掉回车
     char start=getchar();
     cout<<"该图最小生成树为："<<endl;
     prim(g,start);
     return 0;
 }
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_VERTEX_NUM 20
typedef char vertexType;
typedef enum{DG,DN,UDG,UDN}GraphKind;
typedef struct  arcNode{
    int adjvex;
    struct arcNode *nextarc;
}arcNode;

typedef struct vnode{
    vertexType vexData;
    arcNode *firstarc;
}vnode;

typedef struct{
    vnode* vertices;
    int vexnum,arcnum;
    GraphKind kind;
}alGraph;

int locateVex(alGraph* g,char vex){//确定点vex在邻接表中的位置
    for(int i=0;i<g->vexnum;i++){
        if(g[i].vertices->vexData==vex){
            return i;
        }
    }
    printf("vex not exist in locateVex\n");
    return -1;
}
void CreateGraph(alGraph* g){
    printf("输入顶点数，边数和图类\n");
    scanf("%d %d %d",&g->vexnum,&g->arcnum,&g->kind);

    printf("输入顶点\n");
    for(int i=0;i<g->vexnum;i++){
        scanf("%c",&(g[i].vertices->vexData));
        g[i].vertices->firstarc=NULL;
    }

    printf("输入边\n");
    for(int i=0;i<g->arcnum;i++){
        char sv;
        char tv;
        scanf("%c%c",&sv,&tv);
        int s=locateVex(g,sv);
        int t=locateVex(g,tv);

        arcNode pi;
        pi.adjvex=t;
        pi.nextarc=g[s].vertices->firstarc;
        g[s].vertices->firstarc=&pi;

        if(g->kind==UDG || g->kind==UDN){
            arcNode pj;
            pj.adjvex=s;
            pj.nextarc=g[t].vertices->firstarc;
            g[t].vertices->firstarc=&pj;
        }
    }
}

void DFS(){
    ;
}

void BFS(){
    ;
}

 int main(){
     alGraph* g=(alGraph*)malloc(sizeof(alGraph));
     if(g==NULL){
         printf("malloc fail in main for g\n");
         return -1;
     }
     CreateGraph(g);
     return 0;
 }

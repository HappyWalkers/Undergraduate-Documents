#include <iostream>
#include <string>
#include <cstring>
using namespace std;
#define MAX_VERTEX_NUM 30 //图的最大顶点数目

//图
typedef char vertexType; //顶点数据类型
typedef enum
{
    DG,
    DN,
    UDG,
    UDN
} GraphKind; // 定义图的类型 { 有向图, 有向网,无向图, 无向网}
typedef struct arcNode
{                            //边
    int adjvex;              //边上数据，指向其父节点下一个邻接点在顶点数组中的位置
    int weight;              //边权重
    struct arcNode *nextarc; //指向下一条边
} arcNode;

typedef struct vnode
{                       //顶点
    vertexType vexData; //顶点数据
    string info;        //顶点信息
    arcNode *firstarc;  //指向第一个邻接点的边
} vnode;

typedef struct
{                       //图
    vnode *vertices;    //顶点数组
    int vexnum, arcnum; //顶点数目，边的数目
    GraphKind kind;     //图类型
} alGraph;

void printVertices(alGraph *g)//打印邻接表
{ 
    for (int i = 0; i < g->vexnum; i++)//遍历顶点数组
    { 
        printf("%c ", g->vertices[i].vexData);
        //遍历每个顶点的所有边
        arcNode *a = (arcNode *)malloc(sizeof(arcNode));
        a = g->vertices[i].firstarc;
        while (a != NULL)
        {
            printf("%d&%d ", a->adjvex, a->weight);
            a = a->nextarc;
        }
        printf("\n");
    }
}

int locateVex(alGraph *g, char vex)//确定点vex在邻接表中的位置
{ 
    for (int i = 0; i < g->vexnum; i++)
    { //遍历比较
        if (g->vertices[i].vexData == vex)
        {
            return i;
        }
    }
    printf("vex not exist in locateVex:%c\n", vex);
    return -1; //没找到返回-1
}

void CreateGraph(alGraph *g)//先序输入图
{ 
    printf("输入顶点数，边数和图类\n");
    scanf("%d%d%d", &(g->vexnum), &(g->arcnum), &(g->kind));
    g->vertices = (vnode *)malloc(g->vexnum * sizeof(vnode));

    printf("输入顶点\n");
    for (int i = 0; i < g->vexnum; i++)
    {
        printf("第%d个顶点：\n", i + 1);
        getchar(); //清掉回车
        g->vertices[i].vexData = getchar();
        g->vertices[i].firstarc = NULL; //尾部置空
    }

    printf("输入边和权重\n");
    for (int i = 0; i < g->arcnum; i++)
    {
        char sv;
        char tv;
        int w;
        getchar(); //清掉回车
        printf("第%d条边和权重：\n", i + 1);
        scanf("%c%c", &sv, &tv);
        scanf("%d", &w);
        int s = locateVex(g, sv);
        int t = locateVex(g, tv);

        arcNode *pi = (arcNode *)malloc(sizeof(arcNode));
        pi->adjvex = t;
        pi->weight = w;
        pi->nextarc = g->vertices[s].firstarc; //头插法
        g->vertices[s].firstarc = pi;

        if (g->kind == UDG || g->kind == UDN)//若是无向图或无向网，在边的另一端也要加入边
        { 
            arcNode *pj = (arcNode *)malloc(sizeof(arcNode));
            pj->adjvex = s;
            pj->weight = w;
            pj->nextarc = g->vertices[t].firstarc; //头插法
            g->vertices[t].firstarc = pj;
        }
    }
}

void visit(vertexType v)//访问顶点数据
{ 
    printf("%c", v);
}

int find_char_in_vnode(char dest, vnode array[], int array_size)//在vnode数组中找dest（char），找到返回位置，没找到返回-1
{
    for (int i = 0; i < array_size; i++)//遍历寻找
    {
        if (dest == array[i].vexData)
        {
            return i;
        }
    }
    // cout<<"fail to find element"<<endl;
    return -1;
}

void prim(alGraph *g, char start)//prim算法，求最小生成树
{
    alGraph p; //用邻接表存最小生成树
    p.vertices = (vnode *)malloc(g->vexnum * sizeof(vnode));
    p.vertices[0].vexData = start;
    p.vertices[0].firstarc = NULL;
    p.vexnum = 1;
    p.arcnum = 0;
    p.kind = UDN;
    while (true)
    {
        if (p.vexnum == g->vexnum)//Vnew更新完则退出循环
            break;            
        int min_weight = 100; //假设所有边权重不超过100
        int min_index = 0;
        int min_index_source = 0;
        for (int i = 0; i < p.vexnum; i++)//遍历Vnew所有边
        { 
            int index_find = find_char_in_vnode(p.vertices[i].vexData, g->vertices, g->vexnum);
            // cout<<index_find<<endl;
            if (index_find != -1)//若在g中找到该点,遍历该点所有邻接边，查找权重最小的边
            { 
                arcNode *a = (arcNode *)malloc(sizeof(arcNode));
                a = g->vertices[index_find].firstarc;
                if (a == NULL)
                    continue;
                while (true)
                {
                    if (a == NULL)
                        break;
                    if (a->weight < min_weight && find_char_in_vnode(g->vertices[a->adjvex].vexData, p.vertices, p.vexnum) == -1)//若找到更小权值的边（该边另一端点不在Vnew中）
                    { 
                        min_weight = a->weight;
                        min_index = a->adjvex;
                        min_index_source = i;
                    }
                    a = a->nextarc;
                }
            }
        }
        //找到权重最小的之后，更新Vnew和Enew
        p.vertices[p.vexnum].vexData = g->vertices[min_index].vexData;
        p.vertices[p.vexnum].firstarc = NULL;

        arcNode *pi = (arcNode *)malloc(sizeof(arcNode));
        pi->adjvex = p.vexnum;
        pi->weight = min_weight;
        pi->nextarc = p.vertices[min_index_source].firstarc; //头插法
        p.vertices[min_index_source].firstarc = pi;

        if (p.kind == UDG || p.kind == UDN)//若是无向图或无向网，在边的另一端也要加入边
        { 
            arcNode *pj = (arcNode *)malloc(sizeof(arcNode));
            pj->adjvex = min_index_source;
            pj->weight = min_weight;
            pj->nextarc = p.vertices[p.vexnum].firstarc; //头插法
            p.vertices[p.vexnum].firstarc = pj;
        }
        p.vexnum++;
        // printVertices(&p);
    }
    printVertices(&p);
}

template <typename t>
void print_array(t array[], int array_size)//模板，打印数组
{
    for (int i = 0; i < array_size; i++)
    {
        cout << array[i] << " ";
    }
}

template <typename t>
int find_element_in_array(t dest, t array[], int array_size)//模板，在数组中寻找元素，找到返回位置，没找到返回-1
{
    for (int i = 0; i < array_size; i++)
    {
        if (array[i] == dest)
        {
            return i;
        }
    }
    return -1;
}

void dijkstra(alGraph *g, char start)//dijkstra算法，求点start到其他所有点最短路径和最短距离
{
    int dis[g->vexnum];
    int infinity = 100; //假设所有边权重不超过100
    for (int i = 0; i < g->vexnum; i++)
    {
        if (i == find_char_in_vnode(start, g->vertices, g->vexnum))
        {
            dis[i] = 0; //start位赋值为0
        }
        else
        {
            dis[i] = infinity; //其他位先赋为无穷大
        }
    }
    arcNode *a = (arcNode *)malloc(sizeof(arcNode));
    a = g->vertices[find_char_in_vnode(start, g->vertices, g->vexnum)].firstarc;
    while (true) //初始化dis
    {
        if (a == NULL)
            break;
        dis[a->adjvex] = a->weight;
        a = a->nextarc;
    }
    // print_array(dis,g->vexnum);
    char T[g->vexnum];//已经找到最短路径的点的集合
    int T_index = 0;
    T[T_index++] = start;//T初始化
    char temp = start; //当前点
    string toTemp="";//当前路径
    toTemp=toTemp+temp;
    while (true)//寻找start到所有顶点路径和距离
    { 
        if (T_index == g->vexnum)
            break;
        int min_dis = infinity;
        int min_index = -1;
        for (int i = 0; i < g->vexnum; i++)//从V-T中找出min(dis)
        { 
            if (find_element_in_array(g->vertices[i].vexData, T, g->vexnum) == -1 && dis[i] < min_dis)
            {
                min_dis = dis[i];
                min_index = i;
            }
        }
        T[T_index++] = g->vertices[min_index].vexData;
        cout << toTemp << "->" << g->vertices[min_index].vexData << "=" << dis[min_index] << endl;//输出路径和距离
        arcNode *a2 = (arcNode *)malloc(sizeof(arcNode));
        a2 = g->vertices[min_index].firstarc;
        while (true)//查看与当前最小所连接的点，是否可发现 到其他顶点的更短路径
        { 
            if (a2 == NULL)
                break;
            if (dis[min_index] + a2->weight < dis[a2->adjvex])//若找到更短的路径到达
            {
                dis[a2->adjvex] = dis[min_index] + a2->weight;//更新最短距离
                if (temp != g->vertices[min_index].vexData)//若当前点变化，就更新
                {
                    temp = g->vertices[min_index].vexData;
                    toTemp = toTemp + "->" + temp;//当前路径更新延伸到当前点
                }
            }
            a2 = a2->nextarc;
        }
        // print_array(dis,g->vexnum);
    }
    // print_array(dis, g->vexnum);
}

int main() //测试
{
    alGraph *g = (alGraph *)malloc(sizeof(alGraph));
    if (g == NULL)
    {
        printf("malloc fail in main for g\n");
        return -1;
    }
    CreateGraph(g);
    printVertices(g); //查看邻接表
    printf("输入起点：\n");
    getchar(); //清掉回车
    char start = getchar();
    cout << "该图最小生成树为：" << endl;
    prim(g, start);
    cout << "从" << start << "到各点最短路径及最短距离为：" << endl;
    dijkstra(g, start);
    return 0;
}
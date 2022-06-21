#include <bits/stdc++.h>
using namespace std;
#define re register
#define F first
#define S second
typedef long long ll;
typedef pair<int, int> P;
const int N = 1e5 + 5, M = 2e6 + 5;
const int INF = 0x3f3f3f3f;

inline int read() {
    int X = 0,w = 0; char ch = 0;
    while(!isdigit(ch)) {w |= ch == '-';ch = getchar();}
    while(isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48),ch = getchar();
    return w ? -X : X;
}

struct edge{
	int to, nxt, w;//to为下一个点，nxt为下一个边，w为权值
}e[M];//用来存放表示边，当前边与反边相邻放置，反边用于反悔路径，求增广路

int head[N], tot = 1, vis[N];//head[u]为以u为起点所有边中的第一个
int n, m, s, t;
void addedge(int x, int y, int w){
	e[++tot].to = y; 
	e[tot].w = w;
	e[tot].nxt = head[x];//当前边的下一个边为head[x]
	head[x] = tot;
}
int dfs(int x, int flow){//寻找增广路：flow为此次增广的短板，由于不清楚短板是多少，所以动态更新
	vis[x] = 1;//将x存入已遍历档案
	if (x == t) return flow;//到达汇点，返回本次增广的流量（短板），开始回溯

	for (int i = head[x]; i; i = e[i].nxt){//当前边初始化为head[x]；尚未到达汇点，就一直循环；更新为当前边的下一个边
		int y = e[i].to, w = e[i].w;//y为当前边的下一个点，w为当前边的容量
		if (!vis[y] && w){//倘若y尚未被遍历 且 边上还有残余容量
			int k = dfs(y, min(flow, w));//从 当前最短板 和 当前边的容量 中选出小的，k为y的最大流
			if (k > 0){//如果尚未到达汇点
				e[i].w -= k; e[i ^ 1].w += k;//当前边的容量减去流量，为 当前边的反边（反边与当前边序号相邻） 加上流量
				return k;//返回这次流过的流量
			}
		}
	}

	return 0;//无法到达汇点，返回0
}
int main(){
	n = read(), m = read(), s = read(), t = read();//读入数据，m为边个数，s为起点，t为汇点（终点）
	for (int i = 1; i <= m; i++){
		int x = read(), y = read(), w = read();//起始点，到达点，权值
		addedge(x, y, w); addedge(y, x, 0);//链式前向星加点
	}
	int ans = 0, k;
	while (memset(vis, 0, sizeof(vis)) && (k = dfs(s, 0x3f3f3f3f))) ans += k;//不断寻找增广路：如果清空vis数组成功 并且 尚未到达汇点，那么对ans加上剩下的权值
	printf("%d\n", ans);//打印最大流
	return 0;
}
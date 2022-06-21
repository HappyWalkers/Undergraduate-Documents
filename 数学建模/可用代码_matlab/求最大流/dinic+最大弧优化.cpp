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
	int to, nxt, w;
}e[M];
int head[N], tot = 1, vis[N];
int n, m, s, t, dep[N];
void addedge(int x, int y, int w){
	e[++tot].to = y; e[tot].w = w; e[tot].nxt = head[x]; head[x] = tot;
}
bool bfs(){
	memset(dep, 0, sizeof(dep)); dep[s] = 1;
	queue <int> q; q.push(s);
	while (!q.empty()){
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = e[i].nxt){
			int y = e[i].to, w = e[i].w;
			if (w && !dep[y]){
				dep[y] = dep[x] + 1;
				q.push(y);
			}
		}
	}
	return dep[t];
}
int dfs(int x, int flow){
	if (x == t) return flow;
	int sum = 0;
	for (int i = head[x]; i; i = e[i].nxt){
		int y = e[i].to, w = e[i].w;
		if (w && dep[y] == dep[x] + 1){
			int t = dfs(y, min(flow, w));
			flow -= t; sum += t;
			e[i].w -= t; e[i ^ 1].w += t;	
		}
	}
	if (!sum) dep[x] = 0;
	return sum;
}
int main(){
	n = read(), m = read(), s = read(), t = read();
	for (int i = 1; i <= m; i++){
		int x = read(), y = read(), w = read();
		addedge(x, y, w); addedge(y, x, 0);
	}
	int ans = 0;
	while (bfs()) ans += dfs(s, 0x3f3f3f3f);
	printf("%d\n", ans);
	return 0;
}
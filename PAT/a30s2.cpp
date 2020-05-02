#include <bits/stdc++.h>
using namespace std;

const int N= 510;
const int INF = 1e9;
int n, m, st, ed;
int d[N];
int cost[N][N];
int c[N];
int g[N][N];
bool vis[N];
int pre[N];

void Dij() {
	memset(vis, 0, sizeof(vis));
	fill(c, c+N, INF);
	fill(d, d+N, INF);
	d[st] = 0;
	c[st] = 0;
	for(int i=0; i<n; ++i) pre[i] = i;
	
	for(int i=0; i<n; ++i) {
		//choose min d[u]
		int u = -1, MIN = INF;
		for(int j=0; j<n; ++j)
			if(!vis[j] && d[j] < MIN) { //剩下的未访问的结点中找最小的d 
				MIN = d[j];
				u = j;
			}
		//set true
		if(u == -1) return;
		vis[u] = true;
		//traverse
		for(int v=0; v<n; ++v) {
			if(!vis[v] && g[u][v] != INF) {
				if(d[u] + g[u][v] < d[v]) {
					d[v] = d[u] + g[u][v];
					c[v] = c[u] + cost[u][v];
					pre[v] = u;
				} else if (d[u] + g[u][v] == d[v]) {
					if(c[u] + cost[u][v] < c[v]) {
						c[v] = c[u] + cost[u][v];
						pre[v] = u;
					}
				}
			}
		}
	}
}

void print_path() {
	int p = ed;
	vector<int> v;
	while(pre[p] != p) {
		v.push_back(p);
		p = pre[p];
	}
	v.push_back(p);
	for(int i=v.size()-1; i>=0; --i) printf("%d ", v[i]);
}
int main() {
	fill(g[0], g[0]+N*N, INF); 
	scanf("%d%d%d%d", &n, &m, &st, &ed);
	for(int i=0; i<m; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		scanf("%d%d", &g[x][y], &cost[x][y]);
		g[y][x] = g[x][y];
		cost[y][x] = cost[x][y];
	}
	Dij();
	print_path();
	printf("%d %d", d[ed], c[ed]);
	return 0;
}

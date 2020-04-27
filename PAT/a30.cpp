#include <bits/stdc++.h>
using namespace std;
//邻接矩阵储存 
//T（n） = O（n*n） n为结点个数 
const int N = 510;
int e[N][N], dist[N], cost[N][N], pre[N], mincost[N];
bool visit[N];
const int inf = 1e9;

int main() {
	int n,m,s,d;
	scanf("%d%d%d%d", &n, &m, &s, &d);
	fill(e[0], e[0]+N*N, inf);
	fill(dist, dist+N, inf);
	//fill(mincost, mincost+N, inf);
	memset(visit,0,sizeof(visit));
	for(int i=0; i<m; ++i) {
		int a,b;
		scanf("%d%d", &a, &b);
		scanf("%d", &e[a][b]);
		e[b][a] = e[a][b];
		scanf("%d", &cost[a][b]);
		cost[b][a] = cost[a][b];
	}
	dist[s] = 0;
	mincost[s] = 0;
	pre[s] = -1;
	for(int i=0; i<n; ++i) {
		int u = -1, minn = inf;
		for(int j=0; j<n; ++j) {
			if(!visit[j] && dist[j]<minn) {
				u=j;
				minn=dist[j];
			}
		}
		//if(u == -1) break;
		visit[u] = true;
		for(int v=0; v<n; ++v) {
			if(!visit[v] && e[u][v] != inf) {
				if(dist[u]+e[u][v] < dist[v]) {
					dist[v] = dist[u] + e[u][v];
					mincost[v] = mincost[u] + cost[u][v];
					pre[v] = u;
				} else if(dist[u]+e[u][v] == dist[v]) {
					if(mincost[u] + cost[u][v] < mincost[v]) {
						mincost[v] = mincost[u]+cost[u][v];
						pre[v] = u;
					}
				}
			}
		}
	}
	vector<int> path;
	int f = d;
	do {
		path.push_back(f);
		f = pre[f];
	} while(f != -1);
	for(int i=path.size()-1; i>=0; i--) {
		printf("%d ", path[i]);
	}
	printf("%d %d", dist[d], mincost[d]);
	return 0;
}

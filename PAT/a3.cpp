#include <bits/stdc++.h>
using namespace std;

const int N = 510;
int e[N][N], weight[N], dist[N], num[N], w[N];
bool visit[N];
const int inf = 1e9;

int main() {
	int n, m, start, end;
	scanf("%d%d%d%d", &n, &m, &start, &end);
	for(int i=0; i<n; ++i)
		scanf("%d", &weight[i]);
	fill(e[0], e[0]+N*N, inf);
	fill(dist, dist+N, inf);
	memset(visit,0,sizeof(visit));
	int a, b, c;
	for(int i=0; i<m; ++i) {
		scanf("%d%d%d", &a,&b,&c);
		e[a][b] = c;
		e[b][a] = c;
	}
	dist[start] = 0;
	w[start] = weight[start];
	num[start] = 1;
	for(int i=0; i<n; ++i) {
		int u=-1, minn = inf;
		//找到最小的结点u 
		for(int j=0; j<n; ++j) {
			if(!visit[j] && dist[j]<minn) {
				u = j;
				minn = dist[j];
			}
		}
		if(u==-1) break;
		visit[u] = true;
		for(int v=0; v<n; ++v) {
			if(!visit[v] && e[u][v] != inf) {
				if(dist[u]+e[u][v] < dist[v]) {
					dist[v] = dist[u]+e[u][v];
					num[v] = num[u];
					w[v] = w[u]+weight[v];
				} else if(dist[u]+e[u][v] == dist[v]) {
					num[v] = num[v]+num[u];
					if(w[u]+weight[v]>w[v])
						w[v] = w[u]+weight[v];
				}
			}
		}
	}
	printf("%d %d", num[end], w[end]);
	return 0;
}

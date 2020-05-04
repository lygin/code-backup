#include <bits/stdc++.h>
using namespace std;

const int N = 10010;
const int INF = 1e9;

struct node {
	int v, dis;
	node(int v, int dis): v(v), dis(dis) {}
};
int n, m, st=1, sum = 0;
bool vis[N];
int d[N], c[N];
vector<node> G[N];

void Dij() {
	memset(vis, 0, sizeof(vis));
	fill(c, c+N, INF);
	fill(d, d+N, INF);
	d[st] = 0;
	c[st] = 0;
	for(int i=1; i<=n; ++i) {
		int u = -1, MIN = INF;
		for(int j=1; j<=n; ++j) {
			if(!vis[j] && d[j]<MIN) {
				MIN = d[j];
				u = j;
			}
		}
		if(u == -1) return;
		vis[u] = true;
		sum += c[u];
		for(int i=0; i<G[u].size(); ++i) {
			int v = G[u][i].v;
			int dis = G[u][i].dis;
			if(!vis[v]) {
				if(d[u] + dis < d[v]) {
					d[v] = d[u] + dis;
					c[v] = dis;		
				} else if(d[u] + dis == d[v] && dis < c[v]) {
					c[v] = dis;
				}
			}
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i=1; i<=m; ++i) {
		int a, b, L;
		scanf("%d%d%d", &a, &b, &L);
		G[a].push_back(node(b, L));
		G[b].push_back(node(a, L));
	}
	Dij();
	printf("%d", sum);
	return 0;
}

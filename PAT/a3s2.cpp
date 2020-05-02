#include <bits/stdc++.h>
using namespace std;

struct node {
	int v, dist;
	node (int v, int dist): v(v), dist(dist) {}
};
const int INF = 1e9;
const int N = 510;
vector<node> adj[N];
int weight[N];
bool visit[N] = {false};
int dist[N];
int num[N];
int w[N];

int n, m, st, ed;

void Dij() {
	dist[st] = 0;
	num[st] = 1;
	w[st] = weight[st];
	//
	for(int i=0; i<n; ++i) {
		int u=-1, MIN = INF;
		for(int j=0; j<n; ++j) {
			if(!visit[j] && dist[j] < MIN) {
				MIN = dist[j];
				u = j;
			}
		}
		//
		if(u == -1) return;
		visit[u] = true;
		//
		for(int i=0; i<adj[u].size(); ++i) {
			int v = adj[u][i].v;
			int L = adj[u][i].dist;
			if(!visit[v]) {
				if(dist[u] + L < dist[v]) {
					dist[v] = dist[u] + L;
					num[v] = num[u];
					w[v] = w[u] + weight[v];
				}
				else if(dist[u] + L == dist[v]) {
					if(w[u] + weight[v] > w[v]) {
						w[v] = w[u] + weight[v];
					}
					num[v] += num[u];
				}
			}
		}
	}
}

int main() {
	scanf("%d%d%d%d", &n, &m, &st, &ed);
	for(int i=0; i<n; ++i) scanf("%d", &weight[i]);
	for(int i=0; i<m; ++i) {
		int x, y, dist;
		scanf("%d%d%d", &x, &y, &dist);
		adj[x].push_back(node(y, dist));
		adj[y].push_back(node(x, dist));
	}
	
	fill(dist, dist+N, INF);
	memset(num, 0, sizeof(num));
	memset(w, 0, sizeof(w));
	Dij();
	
	printf("%d %d", num[ed], w[ed]);
}

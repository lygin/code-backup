#include <bits/stdc++.h>
using namespace std;

const int N = 510;
const int INF = 1e9;

int n, m, st, ed;
int d[N], t[N], G[N][N], num[N], T[N][N], pre[N];
bool vis[N];
vector<int> path1, path2; int resd, rest;

void Dij1() {
	fill(d, d+N, INF);
	fill(t, t+N, INF);
	fill(num, num+N, INF);
	memset(vis, 0, sizeof(vis));
	for(int i=0; i<n; ++i) pre[i] = i;
	d[st] = 0;
	t[st] = 0;
	num[st] = 0;
	//
	for(int i=0; i<n; ++i) {
		int u = -1, MIN = INF;
		for(int j=0; j<n; ++j) {
			if(!vis[j] && d[j] < MIN) {
				MIN = d[j];
				u = j;
			}
		}
		if(u == -1) return ;
		vis[u] = true;
		for(int v=0; v<n; ++v) {
			if(!vis[v] && G[u][v] != INF) {
				if(d[u] + G[u][v] < d[v]) {
					d[v] = d[u] + G[u][v];
					t[v] = t[u] + T[u][v];
					pre[v] = u;
				} else if(d[u] + G[u][v] == d[v]) {
					if(t[u] + T[u][v] < t[v]) {
						t[v] = t[u] + T[u][v];
						pre[v] = u;
					}
				}
			}
		}
	}
}

void Dij2() {
	fill(d, d+N, INF);
	fill(t, t+N, INF);
	fill(num, num+N, INF);
	memset(vis, 0, sizeof(vis));
	for(int i=0; i<n; ++i) pre[i] = i;
	d[st] = 0;
	t[st] = 0;
	num[st] = 0;
	//
	for(int i=0; i<n; ++i) {
		int u = -1, MIN = INF;
		for(int j=0; j<n; ++j) {
			if(!vis[j] && t[j] < MIN) {
				MIN = t[j];
				u = j;
			}
		}
		if(u == -1) return ;
		vis[u] = true;
		for(int v=0; v<n; ++v) {
			if(!vis[v] && T[u][v] != INF) {
				if(t[u] + T[u][v] < t[v]) {
					t[v] = t[u] + T[u][v];
					num[v] = num[u] + 1;
					pre[v] = u;
				} else if(t[u] + T[u][v] == t[v]) {
					if(num[u] + 1 < num[v]) {
						num[v] = num[u] + 1;
						pre[v] = u;
					}
				}
			}
		}
	}
}
void keep(vector<int> &v) {
	int p = ed;
	while(pre[p] != p) {
		v.push_back(p);
		p = pre[p];
	}
	v.push_back(p);
}
void print_path(vector<int> v) {
	for(int i=v.size()-1; i>=0; --i) {
		if(i != v.size()-1) printf(" -> ");
		printf("%d", v[i]);
	}
}

int main() {
	fill(G[0], G[0]+N*N, INF);
	fill(T[0], T[0]+N*N, INF);
	scanf("%d%d", &n, &m);
	for(int i=0; i<m; ++i) {
		int a, b, c, dis, e;
		scanf("%d%d%d%d%d", &a, &b, &c, &dis, &e);
		if(c == 1) {
			G[a][b] = dis;
			T[a][b] = e;
		} else {
			G[b][a] = G[a][b] = dis;
			T[b][a] = T[a][b] = e;
		}
	}
	scanf("%d%d", &st, &ed);
	Dij1();
	resd = d[ed];
	keep(path1);
	Dij2();
	rest = t[ed];
	keep(path2);
	if(path1 == path2) {
		printf("Distance = %d; Time = %d: ", resd, rest);
		print_path(path1);
	} else {
		printf("Distance = %d: ", resd);
		print_path(path1);
		printf("\n");
		printf("Time = %d: ", rest);
		print_path(path2);
	}
	return 0;
}

#include <bits/stdc++.h>
using namespace std;
const int N = 510;
vector<int> adj[N];
int n, m;
int vis[N] = {false};
void dfs(int s) {
	vis[s] = true;
	for(int i=0; i<adj[s].size(); ++i) {
		if(!vis[adj[s][i]]) dfs(adj[s][i]);
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i=0; i<m; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	int odd = 0;
	for(int i=1; i<=n; ++i) {
		if(i != 1) printf(" ");
		printf("%d", adj[i].size());
		if(adj[i].size() % 2) odd++;
	}
	int cnt = 0;
	for(int i=1; i<=n; ++i) {
		if(!vis[i]) {
			cnt++;
			dfs(i);
		}
	}
	if(cnt == 1 && odd == 0) {
		printf("\nEulerian");
	} else if(cnt == 1 && odd == 2) {
		printf("\nSemi-Eulerian");
	} else printf("\nNon-Eulerian");
	return 0;
}

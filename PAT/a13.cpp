#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
vector<int> adj[N];
bool vis[N] = {false};

void dfs(int node) {
	vis[node] = true;
	for(int i=0; i<adj[node].size(); ++i) {
		if(!vis[adj[node][i]]) dfs(adj[node][i]);
		//cout << adj[node][i];
	}
	//cout << endl;
}
int main() {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for(int i=0; i<m; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for(int i=0; i<k; ++i) {
		memset(vis, 0, sizeof(vis));
		int cnt = 0;
		int t;
		scanf("%d", &t);
		vis[t] = true;
		for(int j=1; j<=n; ++j) {
			if(!vis[j]) {
				dfs(j);
				cnt++;
			}
		}
		printf("%d\n", cnt-1);
	}
	return 0;
}

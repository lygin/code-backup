#include <bits/stdc++.h>
using namespace std;

const int N = 10010;
int maxh = 0, n;
vector<int> G[N];
set<int> res;
vector<int> tmp;
bool vis[N];

void dfs(int node, int h) {
	if(h > maxh) {
		tmp.clear();
		tmp.push_back(node);
		maxh = h; 
	} else if(h == maxh) {
		tmp.push_back(node);
	}
	vis[node] = true;
	for(int i=0; i<G[node].size(); ++i) {
		if(!vis[G[node][i]]) {
			dfs(G[node][i], h+1);
		}
	}
}

int main() {
	scanf("%d", &n);
	int a, b, cnt=0, s1;
	for(int i=0; i<n-1; ++i) {
		scanf("%d%d", &a, &b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	for(int i=1; i<=n; ++i) {
		if(!vis[i]) {
			dfs(i, 1);
			cnt++;
			if(tmp.size()) s1 = tmp[0];
			for(int i=0; i<tmp.size(); ++i) res.insert(tmp[i]);
		}
	}
	if(cnt >= 2) {
		printf("Error: %d components", cnt);
	} else {
		tmp.clear();
		maxh = 0;
		memset(vis, 0, sizeof(vis));
		dfs(s1, 1);
		for(int i=0; i<tmp.size(); ++i) res.insert(tmp[i]);
		for(auto it = res.begin(); it!=res.end(); ++it)
			printf("%d\n", *it);
	}
	return 0;
}

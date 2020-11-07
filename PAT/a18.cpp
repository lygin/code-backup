#include <bits/stdc++.h>
using namespace std;

const int INF = 1 << 30;
vector<int> path, ans;
vector<vector<int>> pre(510);
vector<int> w(510);
int need = INF, retn = INF;
int cmax;
void dfs(int v) {
	if(v == 0) {
		int total = 0;
		for(int i=path.size()-1; i>=0; --i) {
			total += w[path[i]];
		}
		int tmp= cmax/2*(path.size()-1)-total;
		int cur_need = tmp < 0? 0 : tmp;
		int cur_retn = tmp > 0? 0 : -tmp;
		if(cur_need < need) {
			ans = path;
			need = cur_need;
			retn = cur_retn;
		} else if(cur_need == need && cur_retn < retn) {
			ans = path;
			retn = cur_retn;
		}
		return ;
	}
	for(int i=0 ;i<pre[v].size(); ++i) {
		int nx = pre[v][i];
		path.push_back(nx);
		dfs(nx);
		path.pop_back();
	}
}
int main() {
	freopen("in.txt", "r", stdin);
	int n, ed, m, st = 0;
	cin >> cmax >> n >> ed >> m;
	vector<bool> vis(n+1, 0);
	vector<int> d(n+1, INF);
	vector<vector<array<int, 2>>> g(n+1);//v,dis

	d[st] = 0;
	//input
	for(int i=1; i<=n; ++i) {
		scanf("%d", &w[i]);
	}
	int a,b,c;
	for(int i=0; i<m; ++i) {
		scanf("%d%d%d", &a, &b, &c);
		g[a].push_back({b,c});
		g[b].push_back({a,c});
	}
	//dij
	for(int i=0; i<n; ++i) {//n times loop
		int u = -1, MIN = INF;
		for(int j=0; j<n; ++j) {
			if(!vis[j] && d[j] < MIN) {
				MIN = d[j];
				u = j;
			}
		}
		if(u == -1) return 0;
		vis[u] = true;
		for(int j=0; j<g[u].size(); ++j) {
			int v = g[u][j][0];
			int dis = g[u][j][1];
			if(!vis[v] && d[u] + dis < d[v]) {
				d[v] = d[u] + dis;
				pre[v].clear();
				pre[v].push_back(u);
			} else if(!vis[v] && d[u] + dis == d[v]) {
				pre[v].push_back(u);
			}
		}
	}
	//dfs
	path.push_back(ed);
	dfs(ed);
	printf("%d ", need);
	for(int i=ans.size()-1; i>=0; --i) {
		if(i != ans.size()-1) printf("->");
		printf("%d", ans[i]);
	}
	printf(" %d", retn);
	return 0;
}
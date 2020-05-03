#include <bits/stdc++.h>
using namespace std;

const int N = 210;
const int INF = 1e9;

int n, k, st, ed;
vector<int> pre[N];
bool vis[N];
int c[N], G[N][N], num[N], w[N];
vector<int> tempPath, path;
int resHap = 0;
string m[N];
map<string, int> m2;

void Dij(int s) {
	memset(vis, 0, sizeof(vis));
	fill(c, c+N, INF); 
	c[s] = 0;
	num[s] = 1;
	
	for(int i=1; i<=n; ++i) {
		int u = -1, MIN = INF;
		for(int j=1; j<=n; ++j) {
			if(!vis[j] && c[j] < MIN) {
				MIN = c[j];
				u = j;
			}
		}
		if(u == -1) return ;
		vis[u] = true;
		for(int v=1; v<=n; ++v) {
			if(!vis[v] && G[u][v] != INF) {
				if(c[u] + G[u][v] < c[v]) {
					c[v] = c[u] + G[u][v];
					num[v] = num[u];
					pre[v].clear();
					pre[v].push_back(u);
				} else if(c[u] + G[u][v] == c[v]) {
					num[v] += num[u];
					pre[v].push_back(u);
				}
			}
		}
	}
}

void dfs(int v) {
	if(v == st) {
		tempPath.push_back(v);
		int tempHap = 0;
		for(int i=tempPath.size()-1; i>=0; --i) {
			int id = tempPath[i];
			tempHap += w[id];
		}
		if(tempHap > resHap) {
			resHap = tempHap;
			path = tempPath;
		} else if(tempHap == resHap && tempPath.size() < path.size()) {
			path = tempPath;
		}
		tempPath.pop_back(); 
		return ;
	}
	tempPath.push_back(v);
	for(int i=0; i<pre[v].size(); ++i) dfs(pre[v][i]);
	tempPath.pop_back();
}

int main() {
	fill(G[0], G[0]+N*N, INF);
	string s;
	cin >> n >> k >> s;
	st = 1; m[1] = s; m2[s] = 1;
	w[1] = 0;
	for(int i=2; i<=n; ++i) {
		int L;
		cin >> s >> L;
		m[i] =  s; m2[s] = i;
		w[i] = L;
	}
	ed = m2["ROM"];
	for(int i=1; i<=k; ++i) {
		string s1, s2; int C;
		cin >> s1 >> s2 >> C;
		G[m2[s1]][m2[s2]] = G[m2[s2]][m2[s1]] = C;
	}
	
	Dij(st);
	dfs(ed);
	printf("%d %d %d %d\n", num[ed], c[ed], resHap, resHap/(path.size()-1));
	for(int i=path.size()-1; i>=0; --i) {
		if(i != path.size()-1) printf("->");
		int id = path[i];
		cout << m[id];
	}
	return 0;
}

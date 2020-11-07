#include <bits/stdc++.h>
using namespace std;
//单源有权最短路
//Djkstra+DFS 
const int N = 210;
const int INF = 1e9;

int n, k, st, ed;
vector<int> pre[N];
bool vis[N];
int G[N][N], d[N], w[N], num[N];
vector<int> tmpPath, path;
int tmpH=0, H=0, ttn=INF;
string m[N];//idWord
map<string, int> m2;//wordId

void Dij(int s) {
	memset(vis, 0, sizeof(vis));
	fill(d, d+N, INF); 
	d[st] = 0;
	num[st] = 1;
	for(int i=1; i<=n; ++i) {
		int u = -1, MIN = INF;
		for(int j=1; j<=n; ++j) {
			if(!vis[j] && d[j] < MIN) {
				MIN = d[j];
				u = j;
			}
		}
		if(u == -1) return ;
		vis[u] = true;
		for(int v=1; v<=n; ++v) {
			if(!vis[v] && G[u][v] != INF) {
				if(d[u] + G[u][v] < d[v]) {
					d[v] = d[u] + G[u][v];
					pre[v].clear();
					pre[v].push_back(u);
					num[v] = num[u];//num储存最短路径的条数 
				} else if(d[u] + G[u][v] == d[v]) {
					pre[v].push_back(u);
					num[v] += num[u];
				}
			}
		}
	}
}

void dfs(int u) {
	if(u == st) {
		if(tmpH > H) {
			H = tmpH;
			path = tmpPath;
			ttn = tmpPath.size();//记得更新ttn 
		} else if(tmpH == H && tmpPath.size() < ttn) {
			path = tmpPath;
			ttn = tmpPath.size();
		}
	}
	for(int i=0; i<pre[u].size(); ++i) {
		int v = pre[u][i];
		tmpPath.push_back(v);
		tmpH += w[v];
		dfs(v);
		tmpPath.pop_back();
		tmpH -= w[v];
	}
}

int main() {
	fill(G[0], G[0]+N*N, INF);
	string s;
	cin >> n >> k >> s;
	st = 1; m[1] = s; m2[s] = 1;
	w[st] = 0;
	//字符串哈希，构图 
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
	//DFS 
	tmpH += w[ed];
	tmpPath.push_back(ed);
	dfs(ed);
	printf("%d %d %d %d\n", num[ed], d[ed], H, H/(ttn-1));
	for(int i=path.size()-1; i>=0; --i) {
		if(i != path.size()-1) printf("->");
		int id = path[i];
		cout << m[id];
	}
	return 0;
}

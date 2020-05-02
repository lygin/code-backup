#include <bits/stdc++.h>
using namespace std;

const int N = 1020;
const int INF = 1e9;

int n, m, k, ds;
int res_v = -1, res_sum = INF, res_mdis = 0;
int vis[N], G[N][N], d[N];

int mystoi(string s) {
	if(s[0] == 'G') return n+stoi(s.substr(1));
	else return stoi(s);
}

void Dij(int s) {
	int cur_v = s, cur_sum = 0, cur_mdis = INF;
	//initail
	memset(vis, 0, sizeof(vis));
	fill(d, d+N, INF);
	d[s] = 0;
	//traverse
	for(int i=0; i<n+m; ++i) {
		//find min d[]
		int u = -1, MIN = INF;
		for(int j=1; j<=n+m; ++j)
			if(!vis[j] && d[j] < MIN) {
				MIN = d[j];
				u = j;
			}
		//set true
		if(u == -1) break ;
		vis[u] = true;
		//set adj vertex
		for(int v = 1; v<=n+m; ++v) {
			if(!vis[v] && G[u][v] != INF) {
				if(d[u] + G[u][v] < d[v]) d[v] = d[u]+G[u][v];
			}
		}
	}
	cur_mdis = d[1];
	for(int i=1; i<=n; ++i) {
		if(d[i] > ds) {
			cur_v = -1;
			break;
		} else {
			cur_sum += d[i];
			if(d[i] < cur_mdis) cur_mdis = d[i];
		}
	}
	if(cur_v != -1 && (cur_mdis > res_mdis || (cur_mdis == res_mdis && cur_sum < res_sum))) {
		res_v = cur_v;
		res_sum = cur_sum;
		res_mdis = cur_mdis;
	}
}

int main() {
	scanf("%d%d%d%d", &n, &m, &k, &ds);
	fill(G[0], G[0]+N*N, INF);
	for(int i=0; i<k; ++i) {
		string s1, s2;
		int L;
		cin >> s1 >> s2 >> L;
		int a1 = mystoi(s1), a2 = mystoi(s2);
		G[a1][a2] = G[a2][a1] = L;
		G[a1][a2] = G[a2][a1] = min(L, G[a1][a2]);
	}
	for(int i=n+1; i<=n+m; ++i) {
		Dij(i);
	}
	if(res_v == -1) printf("No Solution");
	else {
		string res = "G" + to_string(res_v-n);
		cout << res << endl;
		printf("%.1f %.1f", (float)res_mdis*1.0, res_sum*1.0/n);
	}
	return 0;
}

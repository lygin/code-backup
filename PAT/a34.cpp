#include <bits/stdc++.h>
using namespace std;

const int N = 2010;
int G[N][N];
bool vis[N] = {false};
map<string, int> res;
int n, K, cnt = 0;
map<int, string> m1;
map<string, int> m2;

void bfs(int s) {
	int totalW = 0;
	int totalN = 1;
	int head;
	int headHW = 0;
	queue<int> q;
	q.push(s);
	vis[s] = true;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		int tmpHW = 0;
		for(int v=0; v<cnt; ++v) {
			tmpHW += G[u][v];
			if(!vis[v] && G[u][v] != 0) {
				q.push(v);
				vis[v] = true;
				totalN++;
			}
		}
		if(tmpHW > headHW) {
			headHW = tmpHW;
			head = u;
		}
		totalW += tmpHW;
	}
	totalW >>= 1;
	if(totalN > 2 && totalW > K) {
		res[m1[head]] = totalN;
	}
}

int main() {
	memset(G[0], 0, sizeof(G));
	scanf("%d%d", &n, &K);
	string s1, s2;
	int len;
	for(int i=1; i<=n; ++i) {
		cin >> s1 >> s2 >> len;
		if(!m2.count(s1)) {
			m2[s1] = cnt;
			m1[cnt] = s1;
			cnt++;
		}
		if(!m2.count(s2)) {
			m2[s2] = cnt;
			m1[cnt] = s2;
			cnt++;
		}
		G[m2[s1]][m2[s2]] += len;
		G[m2[s2]][m2[s1]] += len; 	
	}
	for(int i=0; i<cnt; ++i) {
		if(!vis[i]) bfs(i);
	}
	printf("%d\n", res.size());
	for(auto it=res.begin(); it!=res.end(); ++it) {
		cout << it->first;
		printf(" %d\n", it->second);
	}
	return 0;
}

#include <bits/stdc++.h>
using namespace std;

const int N = 210;
const int INF = 1e9;
int n, k, st, ed;
int vis[N], c[N], num[N], cost[N][N], pre[N], weight[N], w[N], num2[N];
string m[N];
map<string, int> m2;

void Dij() {
	//initial
	memset(vis, 0, sizeof(vis));
	memset(w, 0, sizeof(w));
	fill(c, c+N, INF);
	fill(num, num+N, INF);
	for(int i=1; i<=n; ++i) pre[i] = i;
	c[st] = 0;
	w[st] = 0;
	num[st] = 0;
	num2[st] = 1;
	//traverse
	for(int i=1; i<=n; ++i) {
		//cout << num[m2["PRS"]] << endl;
		//find min d[]
		int u = -1, MIN = INF;
		for(int j=1; j<=n; ++j) {
			if(!vis[j] && c[j] < MIN) {
				MIN = c[j];
				u = j;
			}
		}
		//set true
		if(u == -1) return ;
		vis[u] = true;
		//set adj
		for(int v=1; v<=n; ++v) {
			if(!vis[v] && cost[u][v] != INF) {
				if(c[u] + cost[u][v] < c[v]) {
					c[v] = c[u] + cost[u][v];
					num[v] = num[u] +1;
					w[v] = w[u] + weight[v];
					pre[v] = u;
					num2[v] = num2[u];
				} else if(c[u] + cost[u][v] == c[v] ) {
					if(w[u] + weight[v] > w[v]) {
					w[v] = w[u] + weight[v];
					num[v] = num[u]+1;
					pre[v] = u;
					} else if( w[u] + weight[v] == w[v] && num[u] + 1 < num[v]) {
					num[v] = num[u]+1;
					pre[v] = u;
					}
					num2[v] += num2[u];
				}
			}
		}
	}
	
}

void print_res() {
	vector<int> v;
	int p = ed;
	v.push_back(p);
	do {
		p = pre[p];
		v.push_back(p);
	} while(pre[p] != p);
	int len = v.size()-1;
	printf("%d %d %d %d\n", num2[ed], c[ed], w[ed], w[ed]/len);
	for(int i=len; i>=0; --i) {
		if(i != len) printf("->");
		cout << m[v[i]];
	}
}

int main() {
	fill(cost[0], cost[0]+N*N, INF);
	string s;
	cin >> n >> k >> s;
	m[1] = s; m2[s] = 1;
	for(int i=2; i<=n; ++i) {
		int hap;
		cin >> s >> hap;
		m[i] = s; m2[s] = i;
		weight[i] = hap;
	}
	st = 1, ed = m2["ROM"];
	for(int i=0; i<k; ++i) {
		string s1, s2; int costa;
		cin >> s1 >> s2 >> costa;
		cost[m2[s1]][m2[s2]] = cost[m2[s2]][m2[s1]] = costa;
	}
	Dij();
	print_res();
	return 0;
}

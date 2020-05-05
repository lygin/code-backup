#include <bits/stdc++.h>
using namespace std;

struct node {
	int v, layer;
	node (int v, int layer) : v(v), layer(layer) {}
};
const int N = 1010;
vector<node> adj[N];
int n, L;
bool inq[N] = {false};

int bfs(int s) {
	int sum = 0;
	queue<node> q;
	node st(s, 0);
	q.push(st);
	inq[st.v] = true;
	while(!q.empty()) {
		node top = q.front();
		q.pop();
		int u = top.v;
		for(int i=0; i<adj[u].size(); ++i) {
			node next = adj[u][i];
			next.layer = top.layer+1;
			if(inq[next.v] == false && next.layer <= L) {
				q.push(next);
				inq[next.v] = true;
				sum++;
			}
		}
	} 
	return sum;
}

int main() {
	int k;
	scanf("%d%d", &n, &L);
	for(int i=1; i<=n; ++i) {
		scanf("%d", &k);
		for(int j=0; j<k; ++j) {
			int tmp;scanf("%d", &tmp);
			adj[tmp].push_back(node(i, 0));
		}
	}
	scanf("%d", &k);
	for(int i=0; i<k; ++i) {
		memset(inq, 0, sizeof(inq));
		int st;
		scanf("%d", &st);
		int res = bfs(st);
		printf("%d\n", res);
	}
	return 0;
}

#include <bits/stdc++.h>
using namespace std;

const int N =110;
int in[N], n, t=0;
vector<int> res;
struct node {
	int l, r, val;
}tree[N];

void dfs(int root ) {
	if(tree[root].l != -1) dfs(tree[root].l);
	tree[root].val = in[t++];
	if(tree[root].r != -1) dfs(tree[root].r);
}

void bfs(int root) {
	queue<int> q;
	q.push(root);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		res.push_back(tree[u].val);
		if(tree[u].l != -1) q.push(tree[u].l);
		if(tree[u].r != -1) q.push(tree[u].r);
	}
}

int main () {
	scanf("%d", &n);
	for(int i=0; i<n; ++i) {
		scanf("%d%d", &tree[i].l, &tree[i].r);
	}
	for(int i=0; i<n; ++i) scanf("%d", &in[i]);
	sort(in, in+n);
	dfs(0);
	bfs(0);
	for(int i=0; i<res.size(); ++i) {
		if(i!= 0) printf(" ");
		printf("%d", res[i]);
	}
	return 0;
}

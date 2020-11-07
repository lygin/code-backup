#include <bits/stdc++.h>
using namespace std;

const int N = 110;
struct node {
	int w;
	vector<int> child;
} Node[N];

int n, m, k;
int path[N];
void dfs(int idx, int nodeNum, int sum) {
	if(sum > k) return ;
	if(sum == k) {
		if(Node[idx].child.size() != 0) return;
		for(int i=0; i<nodeNum; ++i) {
			if(i != 0) printf(" ");
			printf("%d", Node[path[i]].w);
		}
		printf("\n");
		return ;
	}
	for(int i=0; i<Node[idx].child.size(); ++i) {
		int child = Node[idx].child[i];
		path[nodeNum] = child;
		dfs(child, nodeNum+1, sum+Node[child].w);
	}
}

int main() {
	int id, cNum, c;
	scanf("%d%d%d", &n, &m, &k);
	for(int i=0; i<n; ++i) scanf("%d", &Node[i].w);
	for(int i=0; i<m; ++i) {
		scanf("%d%d", &id, &cNum);
		for(int j=0; j<cNum; ++j) {
			scanf("%d", &c);
			Node[id].child.push_back(c);
		}
		sort(Node[id].child.begin(), Node[id].child.end(), [&](int id1, int id2) {
			return Node[id1].w > Node[id2].w;
		});		
	}
	path[0] = 0;
	dfs(0, 1, Node[0].w);
	return 0;
}

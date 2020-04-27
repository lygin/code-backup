#include <bits/stdc++.h>
using namespace std;

const int maxv = 10010;//常量不要搞低了
int in_order[maxv], post_order[maxv], lch[maxv], rch[maxv]; 
//静态三元表树，lch[i] == 0,表示i的左子树为空，其中i为树的编号（亦可为值）
int n;

bool readlist(int* a) {
	n = 0;
	string line;
	if(!getline(cin,line)) return false;
	stringstream ss(line);
	int x;
	while(ss>>x) a[n++] = x;
	return n>0;
}

int build(int l1, int r1, int l2, int r2) {
	if(l1 > r1) return 0; //空树
	int root = post_order[r2]; //根
	int p = l1;
	while(in_order[p] != root) ++p; 
	int cnt = p-l1; //左子树结点个数
	lch[root] = build(l1, p-1, l2, l2+cnt-1);
	rch[root] = build(p+1,r1,l2+cnt,r2-1);
	return root;
}

int best, best_sum;

void dfs(int v, int sum) {
	sum += v;
	if(!lch[v] && !rch[v]) {
		//叶子结点
		if(sum < best_sum || (sum == best_sum && v < best)) {
			best = v;
			best_sum = sum;
		}
	}
	if(lch[v]) dfs(lch[v], sum);
	if(rch[v]) dfs(rch[v], sum);
}

int main() {
	freopen("in.txt", "r", stdin);
	while(readlist(in_order)) {
		readlist(post_order);
		int root = build(0,n-1,0,n-1);
		best_sum = 1000000000;
		dfs(root, 0);
		cout << best << "\n";
	}
	return 0;
}
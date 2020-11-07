#include <bits/stdc++.h>
using namespace std;
//静态二叉树
//中序遍历构造答案
const int N = 30;
struct node {
	int l,r;//左右孩子编号
	string val;//节点数据
}T[N];
int have[N] = {0};
int n;

string dfs(int root) {
	//所有可能情况
	if(T[root].l == -1 && T[root].r == -1) return T[root].val;//单独节点
	if(T[root].l == -1 && T[root].r != -1) return "(" + T[root].val + dfs(T[root].r) + ")"; //有右子树
	if(T[root].l != -1 && T[root].r == -1) return "(" + dfs(T[root].l) + T[root].val + ")"; //有左子树
	if(T[root].l != -1 && T[root].r != -1) return "(" + dfs(T[root].l) + T[root].val + dfs(T[root].r) + ")";	 	 
}

int main() {
	scanf("%d", &n);
	int root = 1;
	for(int i=1; i<=n; ++i) {
		cin >> T[i].val >> T[i].l >> T[i].r;
		if(T[i].l != -1) have[T[i].l]++;
		if(T[i].r != -1) have[T[i].r]++;
	}
	while(have[root]) root++;//寻找根（孩子中没有出现的）
	string res = dfs(root);
	if(res[0] == '(') res = res.substr(1,res.size()-2);//最终可能由左右子树拼接构成，去除最外层括号
	cout << res;
	return 0;
}

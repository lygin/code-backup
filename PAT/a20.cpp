#include <bits/stdc++.h>
using namespace std;

const int N = 40;
int post[N], in[N];
struct node {
	int val;
	node* left;
	node* right;
};
int n;

node* create(int postL, int postR, int inL, int inR) {
	if(postL > postR) {
		return NULL;
	}
	node* root = new node;
	root->val = post[postR];
	int k;
	for(int i=inL; i<=inR; ++i)
		if(in[i] == post[postR]) {
			k = i; break;
		}
	int leftNum = k - inL;
	root->left = create(postL, postL+leftNum-1, inL, k-1);
	root->right = create(postL+leftNum, postR-1, k+1, inR);
	return root;
}

void bfs(node* r) {
	int cnt = 0;
	queue<node*> q;
	q.push(r);
	while(!q.empty()) {
		node* top = q.front();
		q.pop();
		if(cnt != 0) printf(" ");
		printf("%d", top->val);
		cnt++;
		if(top->left) q.push(top->left);
		if(top->right) q.push(top->right);
	}
}

int main() {
	scanf("%d", &n);
	for(int i=0; i<n; ++i) scanf("%d", &post[i]);
	for(int i=0; i<n; ++i) scanf("%d", &in[i]);
	node* root = create(0,n-1, 0, n-1);
	bfs(root);
	return 0;
}

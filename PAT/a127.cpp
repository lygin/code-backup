#include <bits/stdc++.h>
using namespace std;

const int N = 40;
int in[N], post[N];
int n;
struct node {
	int val;
	node* l;
	node* r;
};
vector<vector<int> > res;
node* build(int inL, int inR, int postL, int postR) {
	if(inL > inR) return NULL;
	node* root = new node;
	root->val = post[postR];
	int pos;
	for(pos=inL; pos<=inR && in[pos]!=post[postR]; ++pos);
	int lNum = pos-inL;
	root->l = build(inL, pos-1, postL, postL+lNum-1);
	root->r = build(pos+1, inR, postL+lNum, postR-1);
	return root; 
}
void bfs(node* root) {
	queue<node*> q;
	q.push(root);
	while(!q.empty()) {
		int size = q.size();
		vector<int> tmp;
		for(int i=0; i<size; ++i) {
			node* u = q.front(); q.pop();
			tmp.push_back(u->val);
			if(u->l) q.push(u->l);
			if(u->r) q.push(u->r);
		}
		res.push_back(tmp);
	}
} 

int main() {
	scanf("%d", &n);
	for(int i=0; i<n; ++i) scanf("%d", &in[i]);
	for(int i=0; i<n; ++i) scanf("%d", &post[i]);
	node* root = build(0,n-1,0,n-1);
	bfs(root);
	printf("%d", res[0][0]);
	for(int i=1; i<res.size(); ++i) {
		if(i%2==1) {
			for(int j=0; j<res[i].size();++j) {
				printf(" %d", res[i][j]);
			}
		} else {
			for(int j=res[i].size()-1; j>=0; --j) {
				printf(" %d", res[i][j]);
			}
		}
	}
	return 0;
}

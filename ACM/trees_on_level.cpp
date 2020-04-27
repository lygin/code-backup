#include <bits/stdc++.h>
using namespace std;

struct node
{
	bool have_value = 0; //是否被赋值
	int v;
	node *left, *right;
	node() : have_value(false), left(NULL), right(NULL) {}
};

node* root;
bool failed;
string s;

void addnode(int v, string s) {
	node* p = root;
	for(int i=0; i<s.size(); ++i) {
		if(s[i] == 'L') {
			if(!p->left) p->left = new node();
			p = p->left;
		}
		else if(s[i] == 'R') {
			if(!p->right) p->right = new node();
			p = p->right;
		}
	}

	if(p->have_value) failed = true;
	p->v = v;
	p->have_value = true;
}

bool read_input() {
	root = new node();
	failed = false;
	root = new node();
	while(cin >> s) {
		if( s == "()") return true;
		int v;
		int pos = s.find(',');
		v = stoi(s.substr(1,pos-1));
		addnode(v, s.substr(pos+1));
	}
	return false;
}

vector<int> ans;
bool bfs() {
	queue<node*> q;
	ans.clear();
	q.push(root);
	while(!q.empty()) {
		node* p = q.front(); q.pop();
		if(!p->have_value) return false;
		ans.push_back(p->v);
		if(p->left != NULL) q.push(p->left);
		if(p->right != NULL) q.push(p->right);
	}
	return true;
}

int main() {
	freopen("in.txt", "r", stdin);
	while(read_input()) {
		if(failed) {
			printf("not complete\n");
			continue;
		}
		if(!bfs()) {
			printf("not complete\n");
		}
		else {
			for(int i=0; i<ans.size(); ++i) {
				if(i != ans.size()-1)
					printf("%d ", ans[i]);
				else
					printf("%d\n", ans[i]);
			}
		}
	}
	return 0;
}


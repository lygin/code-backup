#include <bits/stdc++.h>
using namespace std;

struct node
{
	int num;
	int time;
	char op;	// G表示取，R表示还
	bool operator <(node a)const {
		if(a.time != time)
			return a.time < time;
		else if(a.op != op) 
			return a.op > op;
		else
			return a.num < num;
	}
};

const int N = 1000;
int hook[N+1];

int main() {
	freopen("in.txt", "r", stdin);	// woc 代码全都没错，打开文件写错了！！！
	int n, k;
	int w, s, c;
	node t;
	priority_queue<node> q;
	scanf("%d%d", &n, &k);

	for(int i=1; i<=n; ++i)
		hook[i] = i;

	for(int i=1; i<=k; ++i) {
		scanf("%d%d%d", &w, &s, &c);
		t.num = w;
		t.time = s;
		t.op = 'G';
		q.push(t);

		t.time = s+c;
		t.op = 'R';
		q.push(t);
	}

	while(!q.empty()) {
		t = q.top();
		q.pop();

		if(t.op == 'G') {
			for(int i=1; i<=n; ++i)
				if(hook[i] == t.num) {
					hook[i] = 0;
					break;
				}
		}
		else {	//t.op == 'R'
			for(int i=1; i<=n; ++i)
				if(hook[i] == 0) {
					hook[i] = t.num;
					break;
				}
		}
	}
	for(int i=1; i<=n; ++i) {
		if(i != 1)
			printf(" ");
		printf("%d ", hook[i]);
	}
	printf("\n");
	return 0;
}

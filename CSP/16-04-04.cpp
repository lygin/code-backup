#include <bits/stdc++.h>
using namespace std;
struct node {
	int r, c, t;
	node(int r, int c, int t): r(r), c(c), t(t) {}
};

bool unable[105][105][305] = {false};
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

int main() {
	int n, m, t;
	scanf("%d%d%d", &n, &m, &t);
	for(int i=0; i<t; ++i) {
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		for(int j=c; j<=d; ++j) unable[a][b][j] = true;
	}
	queue<node> q;
	q.push(node(1,1,0));
	while(!q.empty()) {
		node top = q.front();
		q.pop();
		if(top.r == n && top.c == m) {
			printf("%d", top.t);
			return 0;
		}
		for(int i=0; i<4; ++i) {
			int nr = top.r+dr[i];
			int nc = top.c+dc[i];
			int nt = top.t+1;
			if(nr >=1 && nr <=n && nc >=1 && nc <=m && !unable[nr][nc][nt]) {
				q.push(node(nr, nc, nt));
				unable[nr][nc][nt] = true;
			}
		}
	}
}

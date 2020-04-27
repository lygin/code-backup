#include <bits/stdc++.h>
using namespace std;

const int maxn = 110;8
char pic[maxn][maxn];
int m, n;

void dfs(int r, int c) {
	if(r >= m || r<0 || c>=n || c<0 || pic[r][c] == '*') return;
	pic[r][c] = '*';
	for(int dr=-1; dr<=1; ++dr)
		for(int dc=-1; dc<=1; ++dc)
			if(dr !=0 || dc != 0)
				dfs(r+dr,c+dc);
}

int main() {
	freopen("in.txt", "r", stdin);
	while(cin >> m >> n && m && n) {
		int ans = 0;
		for(int i=0; i<m; ++i)
			for(int j=0; j<n; ++j)
				cin >> pic[i][j];
		for(int i=0; i<m; ++i)
			for(int j=0; j<n; ++j)
				if(pic[i][j] == '@') {
					dfs(i,j);
					++ans;
				}
		printf("%d\n", ans);
	}
	return 0;
}

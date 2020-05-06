#include <bits/stdc++.h>
using namespace std;
struct node {
	int r,c,z;
};
int m, n, l, t;
int dr[6] = {1,0,0,-1,0,0};
int dc[6] = {0,1,0,0,-1,0};
int dz[6] = {0,0,1,0,0,-1};
int arr[1300][130][70];
bool test(int r, int c, int z) {
	if(r < 0 || r>=m || c<0 || c>=n || z<0 || z>=l) return false;
	if(arr[r][c][z] == 0) return false;
	return true;
}
int bfs(int r, int c, int z) {
	int cnt = 0;
	queue<node> q;
	q.push({r,c,z});
	arr[r][c][z] = 0;
	while(!q.empty()) {
		node top = q.front();
		q.pop();
		cnt++;
		for(int i=0; i<6; ++i) {
			int nr = top.r+dr[i];
			int nc = top.c+dc[i];
			int nz = top.z+dz[i];
			if(test(nr,nc,nz)) {
				q.push({nr,nc,nz});
				arr[nr][nc][nz] = 0;
			}
		}
	}
	return cnt>=t? cnt:0;
}

int main() {
	scanf("%d%d%d%d", &m, &n, &l, &t);
	for(int i=0; i<l; ++i)
		for(int j=0; j<m; ++j) 
			for(int k=0; k<n; ++k) 
				scanf("%d", &arr[j][k][i]);
	
	int ans = 0;
	for(int i=0; i<l; ++i)
		for(int j=0; j<m; ++j) 
			for(int k=0; k<n; ++k)
				if(arr[j][k][i] == 1) ans += bfs(j, k, i);
				
	printf("%d", ans);
	return 0;
}

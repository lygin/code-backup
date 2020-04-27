#include <bits/stdc++.h>
using namespace std;

int main() {
	map<long,int> mp;
	int m,n,x,y,cnt=0;
	long tol;
	scanf("%d%d%ld",&m, &n, &tol);
	long a[n][m];
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j) {
			scanf("%ld",&a[i][j]);
				mp[a[i][j]]++;
		}
	for(int i=0; i<n && cnt<2; ++i)
		for(int j=0; j<m && cnt<2; ++j) {
			if(mp[a[i][j]] > 1) continue;
			int flag = 1;
			for(int r=-1; r<=1; ++r)
				for(int c=-1; c<=1; ++c) {
					int ni = i+r;
					int nj = j+c;
					if((ni!= i || nj!= j) && ni>=0 && ni<n && nj>=0 && nj<m && abs(a[i][j]-a[ni][nj])<=tol) {
					flag = 0;break;
					}
				}
			if(flag) {
				x=i;y=j;
				cnt++;
			}
		}
	if(cnt==0) printf("Not Exist\n");
	else if(cnt ==2) printf("Not Unique\n");
	else if(cnt == 1) printf("(%d, %d): %ld",y+1,x+1,a[x][y]);
	return 0;
}

#include <bits/stdc++.h>
using namespace std;
int getc(int x) {
	int m = 1;
	for(int i=2; i<=sqrt(x); ++i) {
		if(x%i == 0) m = i;
	}
	return m;
}
int main() {
	int n;
	scanf("%d", &n);
	int a[n];
	for(int i=0; i<n; ++i)
	scanf("%d", &a[i]);
	sort(a,a+n,[&](int a, int b) {
		return a > b;
	});
	int c = getc(n);
	int m = n/c;
	int ans[m][c];
	memset(ans,0,sizeof(ans));
	int cnt = 0;
	int i=0, j=0;
	while(cnt < n) {
		while(cnt < n && j<c && ans[i][j] == 0) {
			ans[i][j] = a[cnt++];
			j++;
		}
		j--;
		i++;
		while(cnt < n &&  i<m && ans[i][j] == 0) {
			ans[i][j] = a[cnt++];
			i++;
		}
		i--;
		j--;
		while(cnt < n && i>=0 && i<m && j>=0 && j<c && !ans[i][j]) {
			ans[i][j] = a[cnt++];
			j--;
		}
		j++;
		i--;
		while(cnt < n && i>=0 && i<m && j>=0 && j<c && !ans[i][j]) {
			ans[i][j] = a[cnt++];
			i--;
		}
		i++;
		j++;
	}
	for(int i=0; i<m; ++i) {
		for(int j=0; j<c; ++j) {
			if(j != 0) printf(" ");
			printf("%d", ans[i][j]);
		}
		printf("\n");
	}
	return 0;
}

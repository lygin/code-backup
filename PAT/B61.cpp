#include <bits/stdc++.h>
using namespace std;

int main() {
	int n,m;
	scanf("%d%d", &n, &m);
	int pt[m];
	int ans[m];
	int my[m];
	for(int i=0; i<m; ++i)
	scanf("%d", &pt[i]);
	for(int i=0; i<m; ++i)
	scanf("%d", &ans[i]);
	for(int k=0; k<n; ++k) {
		int point = 0;
		for(int i=0; i<m; ++i) {
			scanf("%d", &my[i]);
			if(my[i] == ans[i]) point += pt[i];
		}
		printf("%d\n", point);
	}
	return 0;
}

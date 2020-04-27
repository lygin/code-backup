#include <bits/stdc++.h>
using namespace std;

int main() {
	int m,n,l,r,tar,x;
	scanf("%d%d%d%d%d", &m, &n, &l, &r, &tar);
	for(int i=0; i<m; ++i) {
		for(int j=0; j<n; ++j) {
			if(j != 0) printf(" ");
			scanf("%d", &x);
			if(x>=l && x<=r) printf("%03d", tar);
			else printf("%03d", x);
		}
		printf("\n");
	}
	return 0;
}

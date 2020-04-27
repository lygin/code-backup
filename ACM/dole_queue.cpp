#include <bits/stdc++.h>
using namespace std;

const int maxn = 25;
int n, k, m, a[maxn];

int main() {
	freopen("in.txt", "r", stdin);
	while(cin >> n >> k >> m && n) {
		for(int i=0; i<n; ++i) a[i]=i;
		int left = n;
		int p1=-1, p2=n;
		while(left) {
		for(int i=0; i<k; ++i) {
			do {
				p1 = (p1+1)%n;
			} while(a[p1] == -1);
		}
		for(int i=0; i<m; ++i) {
			do {
				p2 = (p2-1+n)%n;
			} while(a[p2] == -1);
		}
		printf("%3d", p1+1); left--;
		if(p2 != p1) {
			printf("%3d", p2+1);
			left--;
		}

		a[p1] = a[p2] = -1;
		if(left) printf(",");
		}
		printf("\n");
	}	
}
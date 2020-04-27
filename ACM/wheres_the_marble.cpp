#include <bits/stdc++.h>
using namespace std;

const int maxn = 10000;

int main() {
	freopen("in.txt", "r", stdin);
	int n,q,a[maxn];
	int kase = 1;
	while(cin >> n >> q) {
		if(n == 0)
			break;
		printf("CASE# %d:\n", kase++);
		for(int i=0; i<n; ++i)
			cin >> a[i];
		sort(a,a+n);
		while(q--) {
			int x;
			cin >> x;
			int p = lower_bound(a,a+n,x) - a;
			if(a[p] == x) printf("%d found at %d\n", x, p+1);
			else printf("%d not found\n", x);
		}
	}
	return 0;
}
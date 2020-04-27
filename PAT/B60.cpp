#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
int a[N];

int main() {
	int n;
	scanf("%d", &n);
	for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
	sort(a+1,a+1+n, [&](int a, int b) {
		return a>b;
	});
	int ans = 0;
	for(int i=1; i<=n; ++i) {
		if(a[i] > i) ans = i;
	}
	printf("%d", ans);
	return 0;
}

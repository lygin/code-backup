#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("in.txt", "r", stdin);
	int n,k;
	scanf("%d%d", &n, &k);
	int a[n];
	for(int i=0; i<n; ++i)
		scanf("%d", a+i);
	int sum = 0, ans = 0;
	for(int i=0; i<n; ++i) {
		sum += a[i];
		if(sum >= k) {
			ans++;
			sum = 0;
		}
	}
	if(sum)
		printf("%d\n", ans+1);
	else
		printf("%d\n", ans);
	return 0;
}
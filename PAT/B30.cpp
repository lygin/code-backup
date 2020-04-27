#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	long long p,x;
	scanf("%d%d", &n, &p);
	long long a[n];
	for(int i=0; i<n; ++i) {
		scanf("%lld", &a[i]);
	}
	sort(a,a+n);
	int ans = 0;
	for(int i=0; i<n; ++i){
		for(int j=i+ans; j<n; ++j) {
			if(a[j] <= p*a[i]) {
				int tmp = j-i+1;
				if(tmp > ans) ans = tmp;
			}
			else break;
		}
	}
	printf("%d", ans);
	return 0;
}

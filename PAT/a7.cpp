#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> a(n),dp(n);
	for(int i=0; i<n; ++i) scanf("%d", &a[i]);
	dp[0] = a[0];
	int mx = dp[0],left=0,right=0,tmp=0;
	for(int i=1; i<n; ++i) {
		if(dp[i-1] < 0) tmp = i;
		dp[i] = dp[i-1]<0?a[i]:a[i]+dp[i-1];
		if(dp[i]>mx) {
			mx = dp[i];
			right = i;
			left = tmp;
		}
	}
	if(mx < 0) {
		printf("0 %d %d", a[0],a[n-1]);
		return 0;
	}
	printf("%d %d %d",mx, a[left], a[right]);
	return 0;
}

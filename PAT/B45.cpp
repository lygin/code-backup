#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	int a[n];
	for(int i=0; i<n; ++i) scanf("%d", &a[i]);
	vector<int> left_max(n), right_min(n);
	left_max[0] = 0;
	right_min[n-1] = INT_MAX;
	for(int i=1; i<n; ++i) {
		left_max[i] = max(a[i-1],left_max[i-1]);
	}
	for(int i=n-2; i>=0; --i) {
		right_min[i] = min(a[i+1],right_min[i+1]);
	}
	vector<int> ans;
	for(int i=0; i<n; ++i) {
		if(a[i] > left_max[i] && a[i] < right_min[i]){
			ans.push_back(a[i]);
		}
	}
	printf("%d\n", ans.size());
	for(int i=0; i<ans.size(); ++i) {
		if(i!= 0) printf(" ");
		printf("%d", ans[i]);
	}
	printf("\n");
	return 0;
}

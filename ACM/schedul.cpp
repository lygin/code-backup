// 选择结束时间最早的
#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100000

int n;
int s[MAX_N], e[MAX_N];

void solve() {
	pair<int, int> itv[n];
	for(int i=0; i<n; ++i) {
		itv[i].first = e[i];
		itv[i].second = s[i];
	}
	sort(itv, itv + n);
	int ans = 0;
	int t = 0;
	for(int i=0; i<n; ++i) {
		if(t < itv[i].second) {
			ans++;
			t = itv[i].first;
		}
	}
	printf("%d\n", ans);
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &n);
	for(int i=0; i<n; ++i)
		scanf("%d", &s[i]);
	for(int i=0; i<n; ++i)
		scanf("%d", &e[i]);
	solve();
	return 0;
}

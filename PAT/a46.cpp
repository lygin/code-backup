#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	cin >> n;
	int dist[n+1];
	dist[1] = 0;
	int sum = 0;
	for(int i=2; i<=n; ++i) {
		int a;
		scanf("%d", &a);
		sum += a;
		dist[i] = sum;
	}
	scanf("%d", &dist[0]); sum += dist[0];
	cin >> m;
	for(int i=0; i<m; ++i) {
		int a1, a2;
		cin >> a1 >> a2;
		if(a1 > a2) swap(a1,a2);
		int tmp = dist[a2]- dist[a1];
		printf("%d\n", min(tmp, sum-tmp));
	}
	return 0;
}

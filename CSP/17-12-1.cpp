#include <bits/stdc++.h>
using namespace std;

const int N = 1000;
int a[N];
const int MAX = 10000;

int main(){
	freopen("in.txt", "r", stdin);
	int n;
	int ans = MAX;
	scanf("%d", &n);

	for(int i=0; i<n; ++i)
		scanf("%d", a+i);

	sort(a, a+n);

	for(int i=1; i<n; ++i) {
		int d = a[i] - a[i-1];
		if(d < ans)
			ans = d;
	}

	printf("%d\n", ans);
	return 0;
}
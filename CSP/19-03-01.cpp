#include <bits/stdc++.h>
using namespace std;

const int N = 100000;
int a[N];

int main() {
	freopen("in.txt", "r", stdin);
	int n;
	int ma, mi;
	scanf("%d", &n);
	for(int i=0; i<n; ++i)
	scanf("%d", a+i);
	if(a[0] <= a[n-1]) {
		mi = a[0];
		ma = a[n-1];
	}
	else {
		mi = a[n-1];
		ma = a[0];
	}
	if(n % 2)
		printf("%d %d %d\n", ma, a[n/2], mi);
	else {
		if((a[n/2] + a[n/2-1]) % 2 == 1)
			printf("%d %.1f %d\n", ma, (float)((a[n/2] + a[n/2-1]) / 2.0), mi);
		else
			printf("%d %d %d\n", ma, (a[n/2] + a[n/2-1]) / 2, mi);
	}
	return 0;
}
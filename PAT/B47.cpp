#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
int a[N] = {0};

int main() {
	int n;
	scanf("%d", &n);
	int t,tmp,s;
	for(int i=0; i<n; ++i) {
		scanf("\n");
		scanf("%d-%d %d", &t, &tmp, &s);
		a[t] += s;
	}
	int p = 0;
	for(int i=0; i<N; ++i) {
		if(a[i] > a[p]) p = i;
	}
	printf("%d %d", p, a[p]);
	return 0;
}

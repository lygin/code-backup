#include <bits/stdc++.h>
using namespace std;

int main() {
	int n,m;
	scanf("%d%d", &n, &m);
	int a[n];
	for(int i=0; i<n; ++i)
		scanf("%d", &a[i]);
	m = m%n;
	if(m!=0) {
		reverse(a,a+n);
		reverse(a,a+m);
		reverse(a+m,a+n);
	}
	for(int i=0; i<n; ++i) {
		if(i!= 0) printf(" ");
		printf("%d", a[i]);
	}
	return 0;
}

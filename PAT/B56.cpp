#include <bits/stdc++.h>
using namespace std;

int main() {
	int n,x;
	scanf("%d", &n);
	int sum = 0;
	for(int i=0; i<n; ++i) {
		scanf("%d", &x);
		sum += x*10*(n-1) + x*(n-1);
	}
	printf("%d", sum);
	return 0;
}

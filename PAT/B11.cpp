#include <bits/stdc++.h>
using namespace std;

int main() {
	long long a,b,c;
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; ++i) {
		scanf("%lld%lld%lld", &a, &b, &c);
		printf("Case #%d: %s\n", i+1, a+b>c?"true":"false");
	}
	return 0;
}

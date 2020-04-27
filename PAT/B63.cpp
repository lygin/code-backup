#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	float mx = 0,a,b;
	scanf("%d", &n);
	for(int i=0; i<n; ++i) {
		scanf("%f%f", &a, &b);
		mx = max(mx, sqrt(a*a+b*b));
	}
	printf("%.2f", mx);
	return 0;
	
}

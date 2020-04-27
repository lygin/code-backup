#include <bits/stdc++.h>
using namespace std;

int main() {
	int n,a,b,c,d,n1=0,n2=0;
	scanf("%d", &n);
	for(int i=0; i<n; ++i) {
		scanf("%d%d%d%d", &a,&b,&c,&d);
		if(b == d) continue;
		if(b == a+c) n2++;
		if(d == a+c) n1++;
	}
	printf("%d %d", n1, n2);
	return 0;
}

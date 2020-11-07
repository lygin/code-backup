#include <bits/stdc++.h>
using namespace std;

int isprime(int x) {
	if(x <= 1) return 0;
	for(int i=2; i<=sqrt(x); ++i) {
		if(x % i == 0) return 0;
	} 
	return 1;
}
int main() {
	int a,b,c;
	while(scanf("%d", &a) != EOF) {
		if(a <0) break;
		scanf("%d", &b);
		if(!isprime(a)) {
			printf("No\n");
			continue;
		}
		int len=0, arr[100];
		do {
			c = a%b;
			arr[len++] = c;
			a /= b;
		} while(a);
		for(int i=0; i<len; ++i) {
			a = a*b+arr[i];
		}
		if(isprime(a)) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	}
	return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
	int a,b;
	int flag = 0;
	while(scanf("%d%d", &a, &b) == 2) {
		if(b > 0) {
		if(flag == 1) printf(" ");
		printf("%d", a*b);
		printf(" %d", b-1);
		flag = 1;
		}
	}
	if(!flag) printf("0 0");
	return 0;
}

#include <bits/stdc++.h>
using namespace std;

int a[3], b[3];
int c[3] = {29,17,INT_MAX};

int main() {
	scanf("%d.%d.%d %d.%d.%d", &a[2], &a[1], &a[0], &b[2], &b[1], &b[0]);
	int flag = 0;
	for(int i=0; i<3; ++i) {
		int tmp = a[i]+b[i]+flag;
		a[i] = tmp%c[i];
		flag = tmp/c[i];
	}
	for(int i=2; i>=0; i--) {
		if(i != 2) printf(".");
		printf("%d", a[i]);
	}
	return 0;
}

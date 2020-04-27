#include <bits/stdc++.h>
using namespace std;

int main() {
	int a[3],b[3];
	scanf("%d.%d.%d %d.%d.%d", &a[0],&a[1],&a[2],&b[0],&b[1],&b[2]);
	if(b[0] < a[0] || (b[0] == a[0] && b[1] < a[1]) || (b[0] == a[0] 
	&& b[1] == a[1] && b[2] < a[2])) {
		for(int i=0; i<3; ++i) swap(a[i],b[i]);
		cout << "-";
	}
	int flag = 0;
	if(b[2]>=a[2]) a[2] = b[2]-a[2];
	else {
		a[2] = b[2]-a[2]+29;
		flag = 1;
	}
	b[1] -= flag;
	if(b[1]>=a[1]) {
		a[1] = b[1]-a[1];
		flag = 0;
	}
	else {
		a[1] = b[1]-a[1]+17;
		flag = 1;
	}
	b[0] -= flag;
	a[0] = b[0]-a[0];
	printf("%d.%d.%d", a[0],a[1],a[2]);
	return 0;
}

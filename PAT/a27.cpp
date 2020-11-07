#include <bits/stdc++.h>
using namespace std;

char c[14] = "0123456789ABC";
int main() {
	printf("#");
	for(int i=0; i<3; ++i) {
		int tmp;
		scanf("%d", &tmp);
		printf("%c%c", c[tmp/13], c[tmp%13]);
	}
	return 0;
} 

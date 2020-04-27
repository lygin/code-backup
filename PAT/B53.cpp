#include <bits/stdc++.h>
using namespace std;

int main() {
	int n,D;
	float e;
	int K;
	scanf("%d%f%d", &n, &e, &D);
	int n1 = 0,n2= 0;
	for(int i=0; i<n; ++i) {
		scanf("%d", &K);
		float x;
		int cnt = 0;
		for(int j=0; j<K; ++j) {
			scanf("%f", &x);
			if(x < e) cnt++;
		}
		if(cnt > K/2){
			if(K > D) n2++;
			else n1++;
		}
	}
	printf("%.1f%% %.1f%%", n1*100.0/n, n2*100.0/n);
	return 0;
}

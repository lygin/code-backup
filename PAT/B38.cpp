#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int score[N] = {0};

int main (){
	int n;
	scanf("%d", &n);
	while(n--) {
		int x;
		scanf("%d", &x);
		score[x]++;
	}
	scanf("%d", &n);
	for(int i=0; i<n; ++i) {
		int x; scanf("%d", &x);
		if(i!=0) printf(" ");
		printf("%d", score[x]); 
	}
	return 0;
}

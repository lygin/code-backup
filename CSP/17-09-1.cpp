#include <bits/stdc++.h>
using namespace std;

int main(){
	freopen("in.txt", "r", stdin);
	int n;
	scanf("%d", &n);
	int cnt = 0;
	while(n>=10){
		if(n>=50) {
			n -= 50;
			cnt += 7;
		}
		else if(n>=30) {
			n -= 30;
			cnt += 4;
		}
		else if(n>=10) {
			n -= 10;
			++cnt;
		}
	}
	printf("%d\n", cnt);
	return 0;
}
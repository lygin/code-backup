#include <bits/stdc++.h>
using namespace std;

int main(){
	//freopen("in.txt", "r", stdin);
	int x;
	int cnt = 0;
	int ans = 0;
	scanf("%d", &x);
	while(x){
	switch(x){
		case 1:
		ans += 1;
		cnt = 0;
		break;
		case 2:
		++cnt;
		ans += 2 * cnt;
		break;
		case 0:
		break;
	}
	scanf("%d", &x);
	}
	printf("%d\n", ans);
	return 0;
}
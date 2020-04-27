#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("in.txt", "r", stdin);
	int ans = 0;
	int plus = 0;
	int tmp;
	while(1) {
		scanf("%d", &tmp);
		if(!tmp) break;
		if(tmp == 2) {
			if(plus == 0 || plus == 1)
				plus = 2;
			else
				plus += 2;
		}
		else {	//temp == 1
			plus = 1;
		}
		ans += plus;
	}
	printf("%d\n", ans);
	return 0;
}
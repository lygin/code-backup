#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("in.txt", "r", stdin);
	int r, y, g;
	int n;
	int k, t;
	long long ans = 0, temp;	// temp比ans可能还大故也要用longlong,1e11左右大小
	scanf("%d%d%d%d", &r, &y, &g, &n);

	while(n--) {
		scanf("%d%d", &k, &t);
		if(k!=0) {
			if(k == 1)
				temp = r - t + ans;
			else if( k == 2)
				temp = r + g + y - t + ans;
			else 
				temp = r + g -t + ans;
			temp = temp % (r + g + y);

			if(temp >= r+g)
				t = r + g + y - temp + r;
			else if(temp <= r)
				t = r - temp;
			else
				t = 0;
		}
		ans += t;
	}
	printf("%lld\n", ans);
}
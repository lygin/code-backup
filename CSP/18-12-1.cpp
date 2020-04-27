#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("in.txt", "r", stdin);
	int r,y,g,n,k,t;
	int ans = 0;
	scanf("%d%d%d%d", &r, &y, &g, &n);

	while(n--)
	{
		scanf("%d%d", &k, &t);
		if(k == 0 || k == 1) ans += t;
		else if(k == 2) ans += t+r;
	}
	printf("%d\n", ans);
	return 0;
}
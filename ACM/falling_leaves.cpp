#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000;
int sum[maxn];

void build(int p) {
	int v;
	cin >> v;
	if(v==-1) return;
	sum[p] += v;
	build(p-1);
	build(p+1);
}
bool init() {
	int v;
	cin >> v;
	if(v == -1) return false;
	memset(sum,0,sizeof(sum));
	int pos = maxn/2;
	sum[pos] = v;
	build(pos-1);
	build(pos+1);
	return true;
}

int main() {
	int kase = 1;
	freopen("in.txt", "r", stdin);
	while(init()) {
	int p = 0;
	while(sum[p] == 0) p++;
	printf("Case %d:\n", kase++);
	cout << sum[p++];
	while(sum[p] != 0)
		printf(" %d", sum[p++]);
	cout << "\n\n";
}
return 0;
}


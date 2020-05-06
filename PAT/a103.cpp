#include <bits/stdc++.h>
using namespace std;
int n, k, p, maxFacSum = -1;
vector<int> v, tmp, ans;
void init() {
	int idx = 0, tmp = 0;
	while(tmp <= n) {
		v.push_back(tmp);
		idx++;
		tmp = pow(idx, p);
	} 
}

void dfs(int idx, int nowK, int nowSum, int nowFacSum) {
	if(nowK == k) {
		if(nowSum == n && nowFacSum > maxFacSum) {
			maxFacSum = nowFacSum;
			ans = tmp;
		}
		return;
	}
	for(int i=idx; i>=1; --i) {
		if(nowSum + v[i] <= n) {
			tmp[nowK] = i;
			dfs(i, nowK+1, nowSum+v[i], nowFacSum+i);
		}
	} 
}

int main() {
	scanf("%d%d%d", &n, &k, &p);
	init();
	tmp.resize(k);
	dfs(v.size()-1, 0, 0, 0);
	if(maxFacSum == -1) {
		printf("Impossible");
		return 0;
	}
	printf("%d = ", n);
	for(int i=0; i<ans.size(); ++i) {
		if(i != 0) printf(" + ");
		printf("%d^%d", ans[i], p);
	}
	return 0;
}

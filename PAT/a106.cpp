#include <bits/stdc++.h>
using namespace std;

const int N= 1e5+10;
vector<int> T[N];
int n, mindep=1e9, minnum=0;

void dfs(int root, int dep) {
	if(dep > mindep) return;
	if(T[root].size() == 0) {
		if(dep < mindep) {
			mindep = dep;
			minnum = 1;
		} else if(dep == mindep) {
			minnum++;	
		}
		
	}
	for(int i=0; i<T[root].size(); ++i) {
		dfs(T[root][i], dep+1);
	}
}

int main() {
	double base, r;
	scanf("%d%lf%lf", &n, &base, &r);
	int k;
	for(int i=0; i<n; ++i) {
		scanf("%d", &k);
		for(int j=0; j<k; ++j) {
			int tmp;
			scanf("%d", &tmp);
			T[i].push_back(tmp);
		}
	}
	dfs(0,0); 
	printf("%.4lf %d", base*pow(1.0+r/100, mindep), minnum);
	return 0;
}

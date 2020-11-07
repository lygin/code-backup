#include <bits/stdc++.h>
using namespace std;

const int N = 55;
set<int> st[N];
int n, k, m;
int main() {
	scanf("%d", &n);
	for(int i=1; i<=n; ++i) {
		scanf("%d", &k);
		for(int j=0; j<k; ++j) {
			scanf("%d", &m);
			st[i].insert(m);
		}		
	}
	scanf("%d", &m);
	for(int i=0; i<m; ++i) {
		int s1, s2;
		scanf("%d%d", &s1, &s2);
		int nc=0, nt=st[s1].size();
		for(auto it=st[s2].begin(); it!=st[s2].end(); ++it) {
			if(st[s1].find(*it) != st[s1].end()) {
				nc++;
			} else nt++;
		}
		printf("%.1f%%\n", nc*1.0/nt*100.0);
	}
	return 0;
}

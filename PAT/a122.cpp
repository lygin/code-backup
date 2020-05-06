#include <bits/stdc++.h>
using namespace std;
const int N = 210;
int n, m, k;
int G[N][N]= {0};
vector<int> tmp;
set<int> s;

int main() {
	scanf("%d%d", &n, &m);
	for(int i=0; i<m; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		G[a][b] = G[b][a] = 1;
	}
	int n1;
	scanf("%d", &n1);
	for(int i=0; i<n1; ++i) {
		s.clear();
		tmp.clear();
		scanf("%d", &k);
		tmp.resize(k);
		for(int i=0; i<k; ++i) {
			scanf("%d", &tmp[i]);
			s.insert(tmp[i]);
		}
		int flag1 = 1, flag2= 1;
		if(tmp[0] != tmp[k-1] || s.size() != n || k-1 != n) flag1 = 0;
		for(int i=0; i<tmp.size()-1; ++i)
			if(G[tmp[i]][tmp[i+1]] == 0) {
				flag2 = 0;
				break;
			}
		printf("%s\n", flag1 && flag2 ? "YES":"NO");
	}
	return 0;
}

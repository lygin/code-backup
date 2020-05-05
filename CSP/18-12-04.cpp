#include <bits/stdc++.h>
using namespace std;

int father[500000+10];
int findFather(int x) {
	int a = x;
	while(father[x] != x) {
		x = father[x];
	}
	//Path compression
	while(father[a] != a) {
		int z = a;
		a = father[a];
		father[z] = x;
	}
	return x;
}
struct edge{
	int u, v;
	int w;
}E[100000+10];

int main() {
	int n, m, root;
	scanf("%d%d%d", &n, &m, &root);
	for(int i=1; i<=n; ++i) father[i] = i;
	for(int i=0; i<m; ++i) {
		scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].w);
	}
	sort(E, E+m, [&](edge a, edge b) {
		return a.w < b.w;
	});
	int edge_num = 0, res = 0;
	for(int i=0; i<m; ++i) {
		int Fu = findFather(E[i].u);
		int Fv = findFather(E[i].v);
		if(Fu != Fv) {
			father[Fu] = Fv;//merge
			edge_num++;
			res = E[i].w;
			if(edge_num == n-1) break;
		}
	}
	printf("%d", res);
	return 0;
}

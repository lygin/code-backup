#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
int in[N], tree[N];
int t=0, n;
void inOrder(int root) {
	if(root > n) return ;
	inOrder(2*root);
	tree[root] = in[t++];
	inOrder(2*root+1);
}

int main () {
	scanf("%d", &n);
	for(int i=0; i<n; ++i) scanf("%d", &in[i]);
	sort(in, in+n);
	inOrder(1);
	for(int i=1; i<=n; ++i) {
		if( i != 1) printf(" ");
		printf("%d", tree[i]);
		
	}
	return 0;
}

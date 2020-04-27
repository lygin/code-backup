#include <bits/stdc++.h>
using namespace std;

const int N = 100;
struct node {
	int id;
	int pos;
	int step;
}b[N];

bool cmp1(node a, node b) {
	return a.pos < b.pos;
}

bool cmp2(node a, node b) {
	return a.id < b.id;
}

int main() {
	freopen("in.txt", "r", stdin);
	int n, l, t;
	scanf("%d%d%d", &n, &l, &t);

	for(int i=0; i<n; ++i) {
		b[i].id = i+1;
		scanf("%d", &b[i].pos);
		b[i].step = 1;
	}

	sort(b, b+n, cmp1);

	for(int i=0; i<t; ++i) {
		//one step
		for(int j=0; j<n; ++j) {
			b[j].pos += b[j].step;
			if(b[j].pos == 0 || b[j].pos == l)
				b[j].step = -b[j].step;
		}

		for(int j=1; j<n; ++j) {
			if(b[j].pos == b[j-1].pos) {
				b[j].step = -b[j].step;
				b[j-1].step = -b[j-1].step;
			}
		}
	}

	sort(b, b+n, cmp2);
	for(int i=0; i<n; ++i) {
		if(i!=0)
			printf(" ");
		printf("%d", b[i].pos);
	}

	return 0;
}
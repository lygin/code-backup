#include <bits/stdc++.h>
using namespace std;

const int maxn = 100;
string in_order, pre_order;
char lch[maxn], rch[maxn];
char root;

char build(int l1, int r1, int l2, int r2) {
	if(l1 > r1) return '0';
	char root = pre_order[l1];
	int pos = l2;
	while(in_order[pos] != root) pos++;
	int cnt = pos-l2;
	lch[root - 'A'] = build(l1+1, l1+cnt, l2, pos-1);
	rch[root - 'A'] = build(l1+cnt+1, r1, pos+1, r2);
	return root;
}

void post_order(char root) {
	if(lch[root - 'A'] != '0') post_order(lch[root - 'A']);
	if(rch[root - 'A'] != '0') post_order(rch[root - 'A']);
	if(root != '0') cout << root;
	return;
}

int main() {
	freopen("in.txt", "r", stdin);
	while(cin >> pre_order) {
		cin >> in_order;
		int n = pre_order.size();
		char root = build(0, n-1, 0, n-1);

		//输出
		post_order(root);
		cout << endl;
	}
}

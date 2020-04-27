#include <bits/stdc++.h>
using namespace std;

int main() {
	map<int,int> mp;
	set<int> st;
	int n,m;
	scanf("%d", &n);
	for(int i=0; i<n; ++i) {
		int x,y;
		scanf("%d%d", &x, &y);
		mp[x] = y;
		mp[y] = x;
	}
	scanf("%d", &m);
	for(int i=0; i<m; ++i) {
		int x;
		scanf("%d", &x);
		st.insert(x);
	}
	vector<int> v;
	for(int it : st) {
		if(!mp.count(it)) v.push_back(it);
		else if(!st.count(mp[it])) v.push_back(it);
	}
	printf("%d\n", v.size());
	for(int i=0; i<v.size(); ++i) {
		if(i!=0) printf(" ");
		printf("%05d", v[i]);
	}
	return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("in.txt", "r", stdin);
	int n,m,p,q;
	cin >> n >> m;
	list<int> l;
	for(int i=1; i<=n; ++i)
		l.push_back(i);
	for(int i=1; i<=m; ++i) {
		cin >> p >> q;
		auto iter1 = find(l.begin(), l.end(), p);
		auto iter2 = iter1;
		if(q > 0)
			for(int i=0; i<=q; ++i)
				++iter2;
		else
			for(int i=0; i<-q; ++i)
				--iter2;
		l.insert(iter2, p);
		l.erase(iter1);
	}
	auto iter = l.begin();
	cout << *iter;
	for(++iter; iter!=l.end(); ++iter)
		cout << " " << *iter;
	cout << endl;
	return 0;
}
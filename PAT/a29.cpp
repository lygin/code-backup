#include <bits/stdc++.h>
using namespace std;

int main() {
	vector<int> v;
	int tmp;
	int m, n;
	cin >> m;
	for(int i=0; i<m; ++i) {
		scanf("%d", &tmp);
		v.push_back(tmp);
	}
	cin >> n;
	for(int i=0; i<n; ++i) {
		scanf("%d", &tmp);
		v.push_back(tmp);
	}
	sort(v.begin(), v.end());
	cout << v[(m+n-1)/2];
	return 0;
}

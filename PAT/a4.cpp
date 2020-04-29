#include <bits/stdc++.h>
using namespace std;

vector<int> v[100];

int main() {
	int n,k;
	cin >> n >> k;
	for(int i=0; i<k; ++i) {
		int p, n1, c;
		scanf("%d", &p);
		scanf("%d", &n1);
		for(int j=0; j<n1; ++j) {
			scanf("%d", &c);
			v[p].push_back(c);
		}
	}
	queue<int> q;
	q.push(1);
	int level = 0;
	while(!q.empty()) {
		++level;
		int ln = q.size(), cnt = 0;
		for(int i=0; i<ln; ++i) {
			int first = q.front();q.pop();
			if(v[first].size() == 0) cnt++;
			else {
				for(int j=0; j<v[first].size(); ++j) q.push(v[first][j]);
			}
		}
		if(level != 1) cout << " ";
		cout << cnt;
	}
	return 0;
}

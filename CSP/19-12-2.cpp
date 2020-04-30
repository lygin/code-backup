#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int> > v;
int res[5] = {0};

int main() {
	int n;
	cin >> n;
	for(int i=0; i<n; ++i) {
		int x,y;
		scanf("%d%d", &x, &y);
		v.push_back(make_pair(x,y));
	}
	int len = v.size();
	for(int i=0; i<len; ++i) {
		int x = v[i].first, y = v[i].second;
		int flag = 0;
		int point = 0;
		for(int j=0; j<len; ++j) {
			int nx = v[j].first, ny = v[j].second;
			if(abs(x-nx) + abs(y-ny) == 1) flag++;
			if(abs(x-nx) == 1 && abs(y-ny) == 1) point++;
		}
		if(flag == 4) res[point]++;
	}
	for(int i=0; i<5; ++i) {
		if(i !=0) cout << endl;
		cout << res[i];
	}
	return 0;
}

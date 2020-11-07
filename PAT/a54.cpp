#include <bits/stdc++.h>
using namespace std;
map<int, int> mp;
int main() {
	int m, n;
	scanf("%d%d", &m, &n);
	int half = m*n/2;
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j) {
			int temp;
			scanf("%d", &temp);
			mp[temp]++;
			if(mp[temp] > half) {
				printf("%d", temp);
				return 0;
			}
		}
	return 0;
}

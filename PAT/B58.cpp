#include <bits/stdc++.h>
using namespace std;

const int maxm = 110;
struct t
{
	int point;
	int wn = 0;
	set<char> ans;
}ts[maxm];

int main() {
	freopen("in.txt", "r", stdin);
	int n,m;
	int tmp,an;
	char c;
	cin >> n >> m;
	for(int i=0; i<m; ++i) {
		cin >> ts[i].point >> tmp >> an;
		for(int j=0; j<an; ++j) {
			cin >> c;
			ts[i].ans.insert(c);
		}
	}
	for(int i=0; i<n; ++i) {
		int score = 0;
		scanf("\n");
		for(int j=0; j<m; ++j) {
			set<char> sans;
			if(j != 0) scanf(" ");
			scanf("(%d", &an);
			for(int k=0; k<an; ++k) {
				scanf(" %c", &c);
				sans.insert(c);
			}
			scanf(")");
			if(ts[j].ans == sans) score += ts[j].point;
			else ++ts[j].wn;
		}
		cout << score << endl;
	}
	int maxf = 0;
	for(int i=0; i<m; ++i)
		maxf = max(maxf,ts[i].wn);
	if(maxf == 0) cout << "Too simple" << endl;
	else {
		cout << maxf;
		for(int i=0; i<m; ++i)
			if(ts[i].wn == maxf)
				printf(" %d", i+1);
	}
	return 0;
}

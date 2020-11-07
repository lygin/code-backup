#include <bits/stdc++.h>
using namespace std;

struct node {
	string id;
	int score, loc, locrank, finrank;
};

bool cmp(node a, node b) {
	return a.score != b.score? a.score>b.score : a.id < b.id;
}
int main() {
	int n;
	scanf("%d", &n);
	vector<node> all;
	for(int i=0; i<n; ++i) {
		int m;
		scanf("%d", &m); 
		vector<node> loc(m);
		for(int j=0; j<m; ++j) {
			cin >> loc[j].id;
			scanf("%d", &loc[j].score);
			loc[j].loc = i+1;
		}
		sort(loc.begin(), loc.end(), cmp);
		loc[0].locrank = 1;
		all.push_back(loc[0]);
		for(int j=1; j<m; ++j) {
			loc[j].locrank = (loc[j].score == loc[j-1].score)? loc[j-1].locrank : (j+1);
			all.push_back(loc[j]);
		}	
	}
	sort(all.begin(), all.end(), cmp);
	all[0].finrank = 1;
	for(int i=1; i<all.size(); ++i) {
		all[i].finrank = (all[i].score == all[i-1].score)? all[i-1].finrank : (i+1);
	}
	cout << all.size() << endl;
	for(int i=0; i<all.size(); ++i) {
		cout << all[i].id;
		printf(" %d %d %d\n", all[i].finrank, all[i].loc, all[i].locrank);
	}
	return 0;
}

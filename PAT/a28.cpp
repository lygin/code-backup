#include <bits/stdc++.h>
using namespace std;

struct node {
	string name;
	int id, score;
};

int main() {
	int n, c;
	cin >> n >> c;
	vector<node> v(n);
	for(int i=0; i<n; ++i) {
		scanf("%d", &v[i].id);
		cin >> v[i].name;
		scanf("%d", &v[i].score);
	}
	if(c == 1) {
		sort(v.begin(), v.end(), [&](node a, node b) {
			return a.id < b.id;	
		});
	} else if(c == 2) {
		sort(v.begin(), v.end(), [&](node a, node b) {
			return (a.name != b.name)? a.name < b.name : a.id < b.id;
		});
	} else {
		sort(v.begin(), v.end(), [&](node a, node b) {
			return (a.score != b.score)? a.score < b.score : a.id < b.id;
		});
	}
	for(int i=0; i<n; ++i) {
		printf("%06d ", v[i].id);
		cout << v[i].name;
		printf(" %d\n", v[i].score);
	}
	return 0;
}

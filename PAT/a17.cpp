#include <bits/stdc++.h>
using namespace std;

struct node {
	int time;
	int dur;
	node (int time, int dur): time(time), dur(dur) {}
};

int main() {
	int n, k;
	cin >> n >> k;
	double sum = 0.0;
	vector<node> v;
	for(int i=0; i<n; ++i) {
		int hh, mm, ss, dd;
		scanf("%d:%d:%d %d", &hh, &mm, &ss, &dd);
		int t = hh*3600 + mm*60 + ss;
		if(dd > 60) dd = 60;
		if(t > 17*3600) continue;
		v.push_back(node(t, dd));
	}
	sort(v.begin(), v.end(), [&](node a, node b) {
		return a.time < b.time;
	});
	int cnt = 0;
	priority_queue<int, vector<int>, greater<int> >  pq;
	for(int i=0; i<k; ++i) pq.push(8*3600);
	while(cnt < v.size()) {
		int tmp = pq.top(); pq.pop();
		int delt = tmp - v[cnt].time;
		sum += delt>0? delt : 0;
		pq.push(max(tmp, v[cnt].time) + v[cnt].dur*60);
		cnt++;
	}
	printf("%.1lf", sum/60.0/v.size());
	return 0;
}

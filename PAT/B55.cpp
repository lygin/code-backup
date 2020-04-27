#include <bits/stdc++.h>
using namespace std;

struct node {
	string name;
	int h;
};
int cmp(struct node a, struct node b) {
	return a.h == b.h? a.name<b.name:a.h > b.h;
}
int main() {
	int n,k,m;
	cin >> n >> k;
	vector<node> stu(n);
	for(int i=0; i<n; ++i)
	cin >> stu[i].name >> stu[i].h;
	sort(stu.begin(),stu.end(), cmp);
	int t=0, row = k;
	while(row) {
		if(row == k) m = n-n/k*(k-1);
		else m = n/k;
		vector<string> ans(m);
		ans[m/2] = stu[t].name;
		//×ó±ß
		int j = m/2-1;
		for(int i = t+1; i<t+m; i += 2)
		ans[j--] = stu[i].name;
		//ÓÒ±ß
		j = m/2+1;
		for(int i=t+2; i<t+m; i += 2)
		ans[j++] = stu[i].name;
		for(int i=0; i<ans.size(); ++i) {
			if(i!=0) cout << " ";
			cout << ans[i];
		} 
		cout << endl;
		t += m;
		row--;
	}
	return 0;
}

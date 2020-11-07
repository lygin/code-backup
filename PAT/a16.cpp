#include <bits/stdc++.h>
using namespace std;
struct node {
	string name;
	int status, m, d, h, mi, time;
};
int rate[25];
int n;

double bill(node call) {
	double total = rate[24]*call.d*60+call.mi*rate[call.h];
	for(int i=0; i<call.h; ++i) {
		total += 60*rate[i];
	}
	return total/100.0;
}
int main() {
	//freopen("out.txt", "w", stdout);
	for(int i=0; i<24; ++i) {
		scanf("%d", &rate[i]);
		rate[24] += rate[i];
	}
	scanf("%d", &n);
	vector<node> data(n);
	for(int i=0; i<n; ++i) {
		cin >> data[i].name;
		scanf("%d:%d:%d:%d", &data[i].m, &data[i].d, &data[i].h, &data[i].mi);
		string tmp;
		cin >> tmp;
		if(tmp[1] == 'n') data[i].status = 1;
		else data[i].status = 0;
		data[i].time = data[i].d*24*60+data[i].h*60+data[i].mi;
	}
	sort(data.begin(), data.end(), [&](node a, node b) {
		return a.name != b.name? a.name < b.name : a.time < b.time;	
	});
	map<string, vector<node> > person;
	for(int i=1; i<n; ++i) {
		if(data[i].name == data[i-1].name && data[i-1].status == 1 && data[i].status == 0) {
			person[data[i].name].push_back(data[i-1]);
			person[data[i].name].push_back(data[i]);
		}
	}
	for(auto it : person) {
		vector<node> tmp = it.second;
		cout << it.first;
		printf(" %02d\n", tmp[0].m);
		double total = 0.0;
		for(int i=1; i<tmp.size(); i+=2) {
			double t = bill(tmp[i]) - bill(tmp[i-1]);
			printf("%02d:%02d:%02d %02d:%02d:%02d %d $%.2f\n", tmp[i-1].d, tmp[i-1].h, tmp[i-1].mi,
			tmp[i].d, tmp[i].h, tmp[i].mi, tmp[i].time-tmp[i-1].time, t);
			total += t;
		}
		printf("Total amount: $%.2f\n", total);
	}
	return 0;
}

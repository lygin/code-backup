#include <bits/stdc++.h>
using namespace std;

int main() {
	int m;
	string id1, id2, t1 = "23:59:59", t2 = "00:00:00";
	cin >> m;
	for(int i=0; i<m; ++i) {
		string id, time1, time2;
		cin >> id >> time1 >> time2;
		if(time1 <= t1) {
			t1 = time1;
			id1 = id;
		}
		if(time2 >= t2) {
			t2 = time2;
			id2 = id;
		}
	}
	cout << id1 << " " << id2;
	return 0;
}

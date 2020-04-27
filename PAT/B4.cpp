#include <bits/stdc++.h>
using namespace std;

int main() {
	int n,score,maxs=-1,mins=101;
	string maxname,maxid,minname,minid,name,id;
	cin >> n;
	while(n--) {
		cin >> name >> id >> score;
		if(score>maxs) {
			maxs = score;
			maxname = name;
			maxid = id;
		}
		if(score<mins) {
			mins = score;
			minname = name;
			minid = id;
		}
	}
	cout << maxname << " " << maxid << endl;
	cout << minname << " " << minid << endl;
	return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main () {
	int n;
	cin >> n;
	string maxname,maxbirth="2014/09/06",minname,minbirth="1814/09/06";
	int cnt = 0;
	for(int i=0; i<n; ++i) {
		string s1,s2;
		cin >> s1 >> s2;
		if(s2 >= "1814/09/06" && s2 <= "2014/09/06") {
			cnt++;
			if(s2 <= maxbirth) {
				maxbirth = s2;
				maxname = s1;
			}
			if(s2 >= minbirth) {
				minbirth = s2;
				minname = s1;
			}
		}
	}
	cout << cnt;
	if(cnt) {
		cout << " " << maxname << " " << minname;
	}
	return 0;
}

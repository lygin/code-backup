#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;
	cin >> s;
	s.insert(0,4-s.size(),'0');
	do {
		string s1 = s,s2 = s;
		sort(s1.begin(),s1.end(),[&](char a,char b) {
			return a > b;
		});
		sort(s2.begin(),s2.end());
		int ans = stoi(s1)-stoi(s2);
		s = to_string(ans);
		s.insert(0,4-s.size(),'0');
		cout << s1 << " - " << s2 << " = " << s << endl;;
	} while(s != "0000" && s!= "6174");
	return 0;
}

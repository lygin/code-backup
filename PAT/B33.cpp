#include <bits/stdc++.h>
using namespace std;

int main() {
	string s1, s2, ans;
	getline(cin,s1);
	getline(cin,s2);
	int flag = 0;
	if(s1.find('+') != string :: npos) flag = 1;
	for(int i=0; i<s2.size(); ++i) {
		if(flag && isupper(s2[i])) continue;
		if(s1.find(toupper(s2[i])) == string :: npos)
			ans += s2[i];
	}
	cout << ans;
	return 0;
}

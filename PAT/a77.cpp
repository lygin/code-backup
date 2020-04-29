#include <bits/stdc++.h>
using namespace std;
string s[110];
int main() {
	int k;
	cin >> k;
	getchar();
	for(int i=0; i<k; ++i) {
		getline(cin, s[i]);
		reverse(s[i].begin(), s[i].end());
	}
	string ans = "";
	for(int i=0; i<s[0].size(); ++i) {
		char c = s[0][i], j;
		for(j=1; j<k; ++j)
			if(s[j][i] != c) break;
		if(j != k) break;
		ans.push_back(c);
	}
	reverse(ans.begin(), ans.end());
	if(ans.size()) cout << ans;
	else cout << "nai";
	return 0;
} 

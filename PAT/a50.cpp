#include <bits/stdc++.h>
using namespace std;

string s1, s2;
unordered_set<char> st;
int main() {
	getline(cin, s1);
	getline(cin, s2);
	string ans;
	for(char c: s2) {
		st.insert(c);
	}
	for(int i=0; i<s1.size(); ++i) {
		if(!st.count(s1[i])) ans.push_back(s1[i]);
	}
	cout << ans;
	return 0;
}

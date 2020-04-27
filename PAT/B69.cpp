#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("in.txt", "r", stdin);
	int m,n,s;
	cin >> m >> n >> s;
	string str;
	set<string> st;
	int flag = 0;
	for(int i=1; i<=m; ++i) {
		cin >> str;
		if(i == s && !st.count(str)) {
			cout << str << endl;
			s += n;
			st.insert(str);
			flag = 1;
		}
		else if(i == s && st.count(str)) {
			s++;
		}
	}
	if(!flag) cout << "Keep going...";
	return 0;
}

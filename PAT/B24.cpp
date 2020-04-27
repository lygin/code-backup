#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("in.txt", "r", stdin);
	string s;
	cin >> s;
	if(s[0] == '-') cout << s[0];
	int pos = s.find_first_of("E");
	int n = stoi(s.substr(pos+1));
	string f = s.substr(1,pos-1);
	if(n < 0) {
		cout << "0.";
		for(int i=0; i<abs(n)-1; ++i)
			cout << "0";
		for(int i=0; i<f.size(); ++i)
			if(f[i] != '.')
				cout << f[i];
	}
	else {
		cout << f[0];
		int cnt = 0, j = 2;
		for(;j<f.size() && cnt < n; ++j,++cnt)
			cout << f[j];
		if(j == f.size())
			for(int i=cnt; i<n; ++i)
				cout << '0';
		else {
			cout << ".";
			cout << f.substr(j);
		}
	}
	return 0;
}
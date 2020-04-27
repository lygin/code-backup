#include <bits/stdc++.h>
using namespace std;

const int N = 100;
string p[N], r[N], s;

bool match(string t, string s, bool flag) {
	int lent = t.size();
	int lens = s.size();
	int pt = 0, ps = 0;
	while(pt < lent && ps < lens) {
		if(t[pt] == s[ps]) {
			ps++;
			pt++;
		}
		else {
			if(s[ps++] != '<')	//匹配失败
				return false;

			if(flag)
				cout << " ";

			if(s[ps] == 'i') {	// 匹配int
				bool ok = false;

				while(t[pt] && isdigit(t[pt])) {
					if(t[pt] != '0')
						ok = true;
					if(flag && ok)
						cout << t[pt];
					++pt;
				}

				if(!ok) {
					return false;
				}
				ps += 4;
			}

			else if(s[ps] == 's') {	// str
				bool ok = false;
				while(t[pt] && t[pt] != '/') {
					ok = true;
					if(flag)
						cout << t[pt];
					++pt;
				}

				if(!ok) {
					return false;
				}
				ps += 4;
			}

			else if(s[ps] == 'p') {
				if(flag)
					while(t[pt])
					cout << t[pt++];
				return true;
			}
			}
	}
	return pt == lent && ps == lens;
}

int main() {
	freopen("in.txt", "r", stdin);
	int n, m;
	cin >> n >> m;

	for(int i=0; i<n; ++i)
		cin >> p[i] >> r[i];

	for(int i=0; i<m; ++i) {
		cin >> s;

		bool flag = true;

		for(int j=0; j<n; ++j) {
			if(match(s, p[j], false)) {
				flag = false;
				cout << r[j];
				match(s, p[j], true);
				break;
			}
		}

		if(flag) {
			cout << "404";
		}

		cout << endl;
	}
	return 0;
}
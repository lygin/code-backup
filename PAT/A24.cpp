#include <bits/stdc++.h>
using namespace std;
string s;

void add(string t) {
	int cf = 0;
	for(int i=t.size()-1; i>=0; --i) {
		int tmp = s[i] + t[i] - 2*'0' + cf;
		cf = tmp / 10;
		s[i] = tmp % 10 + '0';
	}
	if(cf) s = "1" + s;
}
int main() {
	cin >> s;
	int k, i;
	for(i=0; i<k; ++i) {
		string t = s;
		reverse(t.begin(), t.end());
		if(s == t) break;
		add(t);
	}
	cout << s << endl;
	cout << i;
	return 0;
}

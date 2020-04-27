#include <bits/stdc++.h>
using namespace std;

const char s[14] = "0123456789JQK";

int main() {
	freopen("in.txt", "r", stdin);
	string a,b;
	cin >> a >> b;
	int na = a.size(), nb = b.size();
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	if(na < nb) a.append(nb-na, '0');
	if(na > nb) b.append(na-nb, '0');
	for(int i=0; i<a.size(); ++i) {
		if(i%2 == 0) {
			a[i] = s[(a[i]-'0'+b[i]-'0')%13];
		}
		else {
			int c = b[i] - a[i];
			a[i] = s[c<0?c+10:c];
		}
	}
	reverse(a.begin(), a.end());
	cout << a;
	return 0;
}
#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;
	int x;
	cin >> s >> x;
	int len = s.size();
	int t = (s[0]-'0')/x;
	if(len == 1 || (len>1 && t)) {
		cout << t;
	}
	int yv = (s[0]-'0')%x;
	for(int i=1; i<len; ++i) {
		t = (yv*10+s[i]-'0')/x;
		cout << t;
		yv = (yv*10+s[i]-'0')%x;
	}
	cout << " " << yv;
	return 0;
}

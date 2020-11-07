#include <bits/stdc++.h>
using namespace std;

int n;
string handle(string s) {
	string res = "";
	int e = 0;
	while(s.length() > 0 && s[0] == '0') s.erase(s.begin());
	if(s[0] == '.') {
		s.erase(s.begin());
		while(s.length() > 0 && s[0] == '0') {
			s.erase(s.begin());
			e--;
		}
	} else {
		int i = 0;
		while(i < s.length() && s[i] != '.') {
			e++;
			i++;
		}
		if(i < s.length()) {
			s.erase(s.begin()+i);
		}
	}
	if(s.length() == 0) {
		e = 0;
	}
	int num = 0;
	while(num < n) {
		if(num < s.length()) res += s[num];
		else res += '0';
		num++;
	}
	res += "*10^" + to_string(e);
	return "0." + res;
}

int main() {
	string s1, s2;
	cin >> n >> s1 >> s2;
	string res1 = handle(s1);
	string res2 = handle(s2);
	if(res1 == res2) {
		printf("YES ");
		cout << res1;
	} else {
		printf("NO ");
		cout << res1 << " " << res2;
	}
	return 0;
}

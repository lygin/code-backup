#include <bits/stdc++.h>
using namespace std;

string a[13] = {"tret", "jan", "feb", "mar", "apr", "may", "jun", 
"jly", "aug", "sep", "oct", "nov", "dec"};
string b[13] = {"####", "tam", "hel", "maa", "huh", "tou", "kes",
 "hei", "elo", "syy", "lok", "mer", "jou"};
 
string tomars(int t) {
	string ans;
	if(t/13) ans += b[t/13];
	if(t/13 && t%13) ans += " ";
	if(t%13 || t==0) ans += a[t%13];
	return ans;
}

int mystoi(string s) {
	int ans = 0;
	for(int i=0; i<13; ++i) {
		if(a[i] == s) ans = i;
		else if(b[i] == s) ans = i*13;
	}
	return ans;
}
int toearth(string s) {
	stringstream ss(s);
	string buf;
	vector<string> v;
	int ans = 0;
	while(ss >> buf) {
		v.push_back(buf);
	}
	for(int i=0; i<v.size(); ++i) {
		ans += mystoi(v[i]);
	}
	return ans;
}
int main() {
	int n;
	scanf("%d", &n);
	string s;
	getchar();
	while(n--) {
		getline(cin,s);
		if(isdigit(s[0])) {
			string t1 = tomars(stoi(s));
			cout << t1 << endl;
		}
		else {
			int t2 = toearth(s);
			printf("%d\n", t2);
		}
	}
}

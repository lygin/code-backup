#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;
	cin >> s;
	int pos;
	while(s[pos] != 'E') pos++;
	if(s[0] == '-') cout << "-";
	string dec = s.substr(1,pos-1);
	int exp = stoi(s.substr(pos+1));
	if(exp<0) {
		cout << "0.";
		for(int i=0; i<abs(exp)-1; ++i) cout << "0";
		for(int i=0; i<dec.size(); ++i) {
			if(dec[i] != '.') cout << dec[i];
		}
	} else {
		cout << dec[0];
		int cnt = 0, j = 2;
		for(; j<dec.size() && cnt<exp; ++j, ++cnt) cout << dec[j];
		if(j == dec.size()) {
			for(;cnt<exp; ++cnt) cout << "0";
		} else {
			cout << ".";
			for(;j<dec.size(); ++j) cout << dec[j];
		}
	}
	return 0;
}

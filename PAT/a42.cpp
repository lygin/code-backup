#include <bits/stdc++.h>
using namespace std;
string tab[5] = {"S", "H", "C", "D", "J"};
int main() {
	string s[54];
	for(int i=0; i<54; ++i) {
		s[i] = tab[i/13] + to_string((i%13)+1);
	}
	int k;
	int pos[54];
	cin >> k;
	for(int i=0; i<54; ++i) cin >> pos[i];
	for(int i=0; i<k; ++i) {
		string tmp[54];
		for(int j=0; j<54; ++j)
			tmp[pos[j]-1] = s[j];
		for(int j=0; j<54; ++j)
			s[j] = tmp[j];
	}
	for(int i=0; i<54; ++i) {
		if(i != 0) cout << " ";
		cout << s[i];
	}
	return 0;
}

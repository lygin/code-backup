#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;
	cin >> s;
	int cntp=0,cntt = 0;
	long long ans = 0;
	for(int i=0; i<s.size(); ++i)
		if(s[i] == 'T') cntt++;
	for(int i=0; i<s.size(); ++i) {
		if(s[i] == 'P') cntp++;
		if(s[i] == 'T') cntt--;
		if(s[i] == 'A') {
			ans += cntp*cntt;
		}
	}
	printf("%lld", ans%1000000007);
	return 0;	
}

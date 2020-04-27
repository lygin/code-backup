#include <bits/stdc++.h>
using namespace std;

const int a[17] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
const int b[11] = {1, 0, 10, 9, 8, 7, 6, 5, 4, 3, 2};
string s;
bool valid() {
	int sum = 0;
	for(int i=0; i<s.size()-1; ++i) {
		if(s[i] > '9' || s[i] < '0') return false;
		sum += a[i]*(s[i]-'0');
	}
	int last = (s[17] == 'X')? 10 : s[17]-'0';
	return last == b[sum%11];
}

int main() {
	freopen("in.txt", "r", stdin);
	int n;
	int flag = 1;
	cin >> n;
	while(n--) {
		cin >> s;
		if(!valid()) {
			flag = 0;
			cout << s << endl;
		}
	}
	if(flag) cout << "All passed";
	return 0;
}
#include <bits/stdc++.h>
using namespace std;

int main() {
	long long a,b,d;
	cin >> a >> b >> d;
	long long c = a+b;
	stack<int> s;
	if(c == 0) cout << 0;
	while(c) {
		s.push(c%d);
		c /= d;
	}
	while(!s.empty()) {
		cout << s.top();
		s.pop();
	}
	return 0;
}

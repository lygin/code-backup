#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("in.txt", "r", stdin);
	int n;
	cin >> n;
	while(n--) {
		stack<char> s;
		string str;
		cin >> str;
		int flag = 1;
		for(int i=0; i<str.size(); ++i) {
			char c = str[i];
			if(c == '(' || c == '[') s.push(c);
			if(c == ')') {
				if(!s.empty() && s.top() == '(') s.pop();
				else {
					flag = 0;
					break;
				}
			}
			if(c == ']') {
				if(!s.empty() && s.top() == '[') s.pop();
				else {
					flag = 0;
					break;
				}
			}
		}
		if(flag) cout << "Yes\n";
		else cout << "No\n";
	}
	return 0;
}
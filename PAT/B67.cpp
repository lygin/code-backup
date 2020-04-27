#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("in.txt", "r", stdin);
	string ans,tmp;
	int n;
	cin >> ans >> n;
	int cnt = 0;
	getchar();
	while(1) {
		getline(cin,tmp);
		if(tmp == "#") break;
		++cnt;
		if(cnt <= n && tmp == ans) {
			cout << "Welcome in\n";
			break;
		}
		else if(tmp != ans) {
			cout << "Wrong password: " << tmp << endl;
			if(cnt == n) {
				cout << "Account locked\n";
				break;
			}
		}
	}
	return 0;
}
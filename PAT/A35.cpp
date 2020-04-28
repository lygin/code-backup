#include <bits/stdc++.h>
using namespace std;

vector<string> v;

int main() {
	string name, pwd;
	int N, cnt=0;
	cin >> N;
	for(int i=0; i<N; ++i) {
		cin >> name >> pwd;
		int flag = 0;
		for(int i=0; i<pwd.size(); ++i) {
			if(pwd[i] == 'l') {
				pwd[i] = 'L';
				flag = 1;
			}
			if(pwd[i] == '1') {
				pwd[i] = '@';
				flag = 1;
			}
			if(pwd[i] == '0') {
				pwd[i] = '%';
				flag = 1;
			}
			if(pwd[i] == 'O') {
				pwd[i] = 'o';
				flag = 1;
			}	
		}
		if(flag) {
			cnt++;
			v.push_back(name + " " + pwd);	
		}
	}
	if(cnt == 0) {
		if(N == 1) printf("There is 1 account and no account is modified");
		else printf("There are %d accounts and no account is modified", N);
	} else {
		cout << cnt << endl;
		for(int i=0; i<v.size(); ++i) cout << v[i] << endl;
	}
	return 0;
}

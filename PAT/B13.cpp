#include <bits/stdc++.h>
using namespace std;

bool isprime (int x) {
	for(int i=2; i*i<=x; ++i)
		if(x%i == 0) return false;
	return true;
}

int main(){
	int m,n;
	cin >> m >> n;
	int cnt = 0,num = 2;
	vector<int> v;
	while(cnt < n) {
		if(isprime(num)) {
			cnt++;
			if(cnt >= m) v.push_back(num);
		}
		num++;
	}
	cnt = 0;
	for(int i=0; i<v.size(); ++i) {
		++cnt;
		if(cnt%10 != 1) cout << " ";
		cout << v[i];
		if(cnt%10 == 0) cout << endl;
	}
	return 0;
}

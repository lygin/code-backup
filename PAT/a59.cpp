#include <bits/stdc++.h>
using namespace std;

bool isprime(int n) {
	if(n <= 1) return false;
	for(int i=2; i<(int)sqrt(1.0*n); ++i) {
		if(n % i == 0) return false;
	}
	return true;
}

vector<int> prime;
int maxn = 100010;

int main() {
	for(int i=2; i<maxn; ++i) {
		if(isprime(i)) prime.push_back(i);
	}
	int n;
	cin >> n;
	printf("%d=", n);
	if(n == 1) {
		printf("1");
		return 0;
	}
	string ans;
	for(int i=0; i<prime.size() && prime[i]<=(int)sqrt(1.0*n); ++i) {
		if(n % prime[i] == 0) {
			int num = 0;
			while(n % prime[i] == 0) {
				num++;
				n /= prime[i];
			}
			ans += to_string(prime[i]);
			if(num > 1) ans += "^" + to_string(num);
			ans += "*";
		}
		if(n == 1) break;
	}
	if(n != 1) {
		ans += to_string(n) + "*";
	}
	ans.pop_back();
	cout << ans;
	return 0;
}

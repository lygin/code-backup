#include <bits/stdc++.h>
using namespace std;

bool isprime(int x) {
	for(int i=2; i*i<=x; ++i) {
		if(x%i == 0) return false;
	}
	return true;
}
int main() {
	vector<int> prime;
	int n,ans=0;
	cin >> n;
	for(int i=2; i<=n; ++i)
		if(isprime(i)) prime.push_back(i);
	for(int i=0; i<prime.size()-1; ++i)
		if(prime[i+1] - prime[i] == 2) ans++;
	cout << ans;
	return 0;
}

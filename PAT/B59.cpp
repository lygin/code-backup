#include <bits/stdc++.h>
using namespace std;
const int N = 10010;
int a[N] = {0};
bool isPrime(int x) {
	if(x<=1) return false;
	for(int i=2; i<=sqrt(x); ++i) {
		if(x%i == 0) return false;
	}
	return true;
}
int main() {
	freopen("in.txt", "r", stdin);
	int n,k;
	scanf("%d", &n);
	for(int i=1; i<=n; ++i) {
		int x;
		scanf("%d", &x);
		a[x] = i;
	}
	scanf("%d", &k);
	for(int i=0; i<k; ++i) {
		int x;
		scanf("%d", &x);
		if(a[x] == 0) printf("%04d: %s\n", x,"Are you kidding?");
		else if(a[x] == -1) printf("%04d: %s\n",x, "Checked");
		else {
			if(a[x] == 1) printf("%04d: %s\n",x, "Mystery Award");
			else if(isPrime(a[x])) printf("%04d: %s\n",x, "Minion");
			else printf("%04d: %s\n",x, "Chocolate");
			a[x] = -1;
		}
	}
	return 0;
}

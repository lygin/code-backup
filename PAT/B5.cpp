#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+10;
int arr[N] = {0};
void solve(int x) {
	while(x != 1) {
		if(x%2) x = (3*x+1)/2;
		else x /= 2;
		if(arr[x] == 1) break; //able to 1
		arr[x] = 1; 
	}
}
int main() {
	int n;
	cin >> n;
	int a[n];
	for(int i=0; i<n; ++i) {
		cin >> a[i];
		solve(a[i]);
	}
	sort(a,a+n,[&](int a, int b) {
		return a>b;
	});
	int cnt = 0;
	for(int i=0; i<n; ++i) {
		if(arr[a[i]] == 0) {
			if(cnt >= 1) cout << " ";
			cout << a[i];
			cnt++;
		}
	}
	return 0;
}

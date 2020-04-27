#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, x, ans = 0;
	int tmp;
	cin >> n;
	cin >> x;
	for(int i=1; i<n; ++i) {
		cin >> tmp;
		ans = max(ans, abs(tmp - x));
		x = tmp;
	}
	cout << ans << endl;
	return 0;
}
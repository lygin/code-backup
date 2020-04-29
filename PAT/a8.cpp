#include <bits/stdc++.h>
using namespace std;

int main() {
	int curr = 0, k, sum = 0;
	cin >> k;
	for(int i=0; i<k; ++i) {
		int next;
		cin >> next;
		int delt = next-curr;
		sum += delt > 0? 6*delt+5 : -4*delt+5;
		curr = next;
	}
	cout << sum;
	return 0;
}

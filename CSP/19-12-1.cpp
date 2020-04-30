#include <bits/stdc++.h>
using namespace std;

bool contain7(int num) {
	if(num/100 == 7) return true;
	if((num/10)%10 == 7) return true;
	if(num%10 == 7) return true;
	return false;
}

int main() {
	int n, cnt =0, idx = 1, a[4] = {0};
	cin >> n;
	while(cnt < n) {
		for(int i=0; i<4 && cnt < n; ++i) {
			if(contain7(idx) || idx % 7 == 0) {
				a[i]++;
			} else {
				cnt++;
			}
			idx++;
		}
	}
	for(int i=0; i<4; ++i) {
		if(i != 0) cout << endl;
		cout << a[i];
	}
	return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
	double a[1010] = {0.0}, res[2010] = {0.0};
	int k;
	cin >> k;
	int exp;
	double coe;
	for(int i=0; i<k; ++i) {
		scanf("%d %lf", &exp, &coe);
		a[exp] = coe;
	}
	cin >> k;
	for(int i=0; i<k; ++i) {
		scanf("%d %lf", &exp, &coe);
		for(int j=0; j<1001; ++j)
			res[exp+j] += coe*a[j];
	} 
	int cnt = 0;
	for(int i=0; i<2001; ++i) {
		if(res[i] != 0.0) cnt++;
	}
	cout << cnt;
	for(int i=2000; i>=0; --i) {
		if(res[i] != 0.0) {
			printf(" %d %.1lf", i, res[i]);
		}
	}
	return 0;
}

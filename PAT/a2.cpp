#include <bits/stdc++.h>
using namespace std;
double a[1010] = {0};
int main() {
	int k,exp;
	double coe;
	scanf("%d", &k);
	for(int i=0; i<k; ++i) {
		scanf("%d%lf", &exp,&coe);
		a[exp] += coe;
	}
	scanf("%d", &k);
	for(int i=0; i<k; ++i) {
		scanf("%d%lf", &exp,&coe);
		a[exp] += coe;
	}
	int cnt=0;
	for(int i=0; i<=1000; ++i)
		if(a[i]) cnt++;
	printf("%d",cnt);
	for(int i=1000; i>=0; --i)
		if(a[i] != 0.0) {
			printf(" %d %.1lf",i,a[i]);
		}
	return 0;
}

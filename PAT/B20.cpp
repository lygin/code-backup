#include <bits/stdc++.h>
using namespace std;

struct node {
	float amount;
	float price;
	float unit;
};

int main() {
	int n,need;
	cin >> n >> need;
	node a[n];
	for(int i=0; i<n; ++i) scanf("%f", &a[i].amount);
	for(int i=0; i<n; ++i) scanf("%f", &a[i].price);
	for(int i=0; i<n; ++i) a[i].unit = a[i].price/a[i].amount;
	sort(a,a+n,[&](node a, node b) {
		return a.unit > b.unit;
	});
	float profit = 0;
	for(int i=0; i<n; ++i) {
		if(need > a[i].amount) {
			need -= a[i].amount;
			profit += a[i].price;
		}
		else {
			profit += need*a[i].unit;
			break;
		}
	}
	printf("%.2f", profit);
	return 0;
}

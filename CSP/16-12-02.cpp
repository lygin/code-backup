#include <bits/stdc++.h>
using namespace std;

int salaryrange[] = {3500, 3500+1500, 3500+4500, 3500+9000, 3500+35000, 3500+55000, 3500+80000};
int taxrate[] = {3, 10, 20, 25, 30, 35, 45};
const int SIZE = sizeof(salaryrange) / sizeof(int);
int getrange[SIZE];

int main() {
	int t;
	freopen("in.txt", "r", stdin);
	getrange[0] = salaryrange[0];
	for(int i=1; i<SIZE; ++i) {
		getrange[i] = getrange[i-1] + (salaryrange[i] - salaryrange[i-1]) * (100 - taxrate[i-1]) / 100;
	}

	int i=0;
	cin >> t;
	for(; i<SIZE; ++i) {
		if(t <= getrange[i])
			break;
	}

	int realsalary;
	if(i == 0)
		realsalary = t;
	else {
		realsalary = salaryrange[i-1] + (t - getrange[i-1]) * 100 / (100 - taxrate[i-1]);
	}

	cout << realsalary << endl;
	return 0;

}
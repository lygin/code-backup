#include <bits/stdc++.h>
using namespace std;

int a[100010] = {0};
int main() {
	int n;
	cin >> n;
	for(int i=0; i<n; ++i) {
		int id, score;
		cin >> id >> score;
		a[id] += score;
	}
	int maxid = 0;
	for(int i=1; i<=100000; ++i) {
		if(a[i] > a[maxid]) maxid = i;
	}
	cout << maxid << " " << a[maxid];
	return 0;
}

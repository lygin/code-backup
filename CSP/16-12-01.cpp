#include <bits/stdc++.h>
using namespace std;

const int N = 1000;
int a[N];

int main() {
	freopen("in.txt", "r", stdin);
	int n;
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	sort(a, a+n);

	int mid = n/2;
	int lnum = mid;
	int rnum = n-mid-1;

	for(int i=mid-1; i>=0; --i) {
		if(a[i] == a[mid])
			lnum--;
		else
			break;
	}

	for(int i=mid+1; i<n; ++i) {
		if(a[i] == a[mid])
			rnum--;
		else 
			break;
	}

	if(lnum == rnum)
		cout << a[mid] << endl;
	else
		cout << -1 << endl;
	return 0;
}
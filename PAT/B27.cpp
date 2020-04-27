#include <bits/stdc++.h>
using namespace std;

int getr(int n, int& yv) {
	int i = 1;
	while(1) {
		if(2*i*i-1 > n) break;
		i++;
	}
	yv = n - 2*(i-1)*(i-1)+1;
	return i-1;
}
int main() {
	int n;
	char c;
	cin >> n >> c;
	int yv;
	int row = getr(n,yv);
	for(int i=row; i>=2; --i) {
		for(int j=0; j<row-i; ++j) cout << " ";
		for(int j=0; j<2*i-1; ++j) cout << c;
		cout << endl;
	}
	for(int i=0; i<row-1; ++i) cout << " ";
	cout << c << endl;;
	for(int i=2; i<=row; ++i) {
		for(int j=0; j<row-i; ++j) cout << " ";
		for(int j=0; j<2*i-1; ++j) cout << c;
		cout << endl;
	}
	cout << yv;
	return 0;
}

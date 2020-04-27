#include <bits/stdc++.h>
using namespace std;

int main() {
	int a[10];
	for(int i=0; i<10; ++i)
		scanf("%d", &a[i]);
	for(int i=1; i<10; ++i) {
		if(a[i]) {
			cout << i;
			a[i]--;
			break;
		}
	}
	for(int i=0; i<10; ++i) {
		if(a[i]) {
			for(int j=0; j<a[i]; ++j)
				cout << i;
		}
	}
	return 0;
}

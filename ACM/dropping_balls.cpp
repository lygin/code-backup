#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("in.txt", "r", stdin);
	int D, I;
	int num;
	cin >> num;
	while(num--) {
		cin >> D >> I;
		int k = 1;
		for(int i=0; i<D-1; ++i) {
			//让I个小球下落
			if(I%2) {
				k = k*2;
				I = (I+1)/2;
			}
			else {
				k = k*2+1;
				I /= 2;
			}
		}
		cout << k << endl;
	}
	getchar();
	return 0;
}
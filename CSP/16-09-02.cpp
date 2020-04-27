#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("in.txt" , "r", stdin);
	int seat[20][5] = {0};
	int n, x;
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> x;
		int j;
		for(j=0; j<20; ++j) {
			int tmp = 0;
			for(int k=0; k<5; ++k)
				if(seat[j][k] == 0)
					tmp++;
			if(tmp >= x) {
				for(int k=0; k<5 && x; ++k)
					if(seat[j][k] == 0) {
						seat[j][k] = 1;
						if(x == 1)
							cout << j*5 + k + 1;
						else
							cout << j*5 + k + 1 << " ";
						x--;
					}
					cout << endl;
					break;
			}
		}
		if(j == 20) {
			while(x--) {
				for(int m=0; m<20; ++m)
					for(int n=0; n<5; ++n)
						if(seat[m][n] == 0) {
							seat[m][n] = 1;
							if(x == 1)
								cout << m*5 + n + 1;
							else 
								cout << m*5 + n  + 1<< " ";
						}
			}
			cout << endl;
		}
	}
	return 0;	
}
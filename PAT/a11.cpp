#include <bits/stdc++.h>
using namespace std;

char tab[4] = {'W', 'T', 'L'};
int main() {
	int res[3];
	double sum = 1;
	for(int i=0; i<3; ++i) {
		double tmp, maxn = 0;
		for(int j=0; j<3; ++j) {
			cin >> tmp;
			if(tmp > maxn) {
				res[i] = j;
				maxn = tmp;
			}
		}
		sum *= maxn;
		cout << tab[res[i]] << " ";
	}
	printf("%.2lf", (sum*0.65-1)*2);
	return 0;
}

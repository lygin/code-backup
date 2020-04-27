#include <bits/stdc++.h>
using namespace std;

int main() {
	//freopen("in.txt", "r", stdin);
	int N;
	int sum = 0;
	cin >> N;
	int mark[N] = {0};
	
	for(int i=0; i<N; ++i) {
		int n;
		int origin;
		cin >> n >> origin;
		for(int j=0; j<n-1; ++j) {
			int tmp;
			cin >> tmp;
			if(tmp > 0) {
				if(tmp != origin) {
					mark[i] = 1;
					origin = tmp;	
				}
			}
			else 
				origin -= abs(tmp);	
		}
		sum += origin;
	}
	
	int t1 = 0, t2 = 0;
	for(int i=0; i<N; ++i) {
		if(mark[i])
			++t1;
		if(mark[i] && mark[(i+1)%N] && mark[(i-1+N)%N])
			++t2;
	}
	cout << sum << " " << t1 << " " << t2 << endl;
	return 0;
}

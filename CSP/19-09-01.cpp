#include <bits/stdc++.h>
using namespace std;

int main() {
	//freopen("in.txt", "r", stdin);
	int N, M;
	int sum = 0, max_pos, max_num = -1;
	cin >> N >> M;
	for(int i=0; i<N; ++i) {
		int origin, tmp, tot = 0;
		cin >> origin;
		for(int j=0; j<M; ++j) {
			cin >> tmp;
			origin -= abs(tmp);
			tot += abs(tmp);
		}
		sum += origin;
		if(tot > max_num) {
			max_pos = i+1;
			max_num = tot;
		}
	}
	cout << sum << " " << max_pos << " " << max_num << endl;
	return 0;
}

#include <bits/stdc++.h>
using namespace std;

struct stuff
{
	int weight;
	int value;
}stuff[1011];

int N, C;
int dp[1011][1011];

int ans() {
	memset(dp,0,sizeof(dp));
	for(int i=1; i<=N; ++i) {
		for(int j=1; j<=C; ++j) {
			if(stuff[i].weight > C)
				dp[i][j] = dp[i-1][j];	// cannot involve i
			else {
				dp[i][j] = max(dp[i-1][j],	// not involve i
					dp[i-1][j-stuff[i].weight] + stuff[i].value);	// involve i
			}
		}
	}
	return dp[N][C];
}

void print_solution(int n, int c) {
	if(n == 0)
		return ;
	if(dp[n][c] == dp[n-1][c]) {
		cout << n << ":NO" << endl;
		print_solution(n-1, c);
	}
	else {
		cout << n << ":YES" << endl;
		print_solution(n-1, c-stuff[n].weight);
	}
}

int main() {
	freopen("in.txt", "r", stdin);
	cin >> N >> C;
	for(int i=1; i<=N; ++i) cin >> stuff[i].value;
	for(int i=1; i<=N; ++i) cin >> stuff[i].weight;

	cout << ans() << endl;
	print_solution(N, C);
	return 0;
}

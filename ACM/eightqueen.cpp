#include <bits/stdc++.h>
using namespace std;

int tot = 0;
const int n = 8;
int col[10] = {0};


bool check(int r, int c) {
	for(int i=0; i<r; ++i)
		if(col[i] == c || abs(c-col[i]) == abs(i-r))
			return false;
	return true;
}

void dfs(int r) {
	if(r == n) {
		tot++;
		return ;
	}
	else {
		for(int j=0; j<n; ++j)
			if(check(r, j)) {
				col[r] = j;
				dfs(r+1);
			}
	}
}

int main() {
	dfs(0);
	cout << tot << endl;
	return 0;
}
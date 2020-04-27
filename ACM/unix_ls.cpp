#include <bits/stdc++.h>
using namespace std;

const int maxcol = 60;
const int maxn = 100+5;
string filename[maxn];

//输出字符串s,长度不足len时补字符extra
void print(const string& s, int len, char extra) {
	cout << s;
	for(int i=0; i<len-s.size(); ++i) cout << extra;
}

int main() {
	freopen("in.txt", "r", stdin);
	int n;
	while(cin >> n) {
		int M = 0;
		for(int i=0; i<n; ++i) {
			cin >> filename[i];
			M = max(M, (int)filename[i].length());
		}
		//计算行数和列数
		int cols = (maxcol - M) / (M+2) + 1, rows = (n-1) / cols +1;
		print("", 60, '-');
		printf("\n");
		sort(filename, filename+n);
		for(int r=0; r<rows; ++r) {
			for(int c=0; c<cols; ++c) {
				int idx = c*rows +r;
				if(idx < n) print(filename[idx], c == cols-1?M:M+2, ' ');
			}
		printf("\n");
		}
	}
	return 0;
}
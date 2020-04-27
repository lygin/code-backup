#include <bits/stdc++.h>
using namespace std;

int readint() {
	int x;
	scanf("%d", &x);
	return x;
}
const int maxn = 128, maxp = 10;
int n, m, priority[maxn], pcnt[maxp];

int main() {
	freopen("in.txt", "r", stdin);
	int T = readint();
	while(T--) {
		n = readint();
		m = readint();
		fill_n(pcnt, maxp, 0);
		fill_n(priority, maxn, 0);
		queue<int> q;
		for(int i=0; i<n; ++i) {
			q.push(i);
			priority[i] = readint();
			pcnt[priority[i]]++;
		}

		int time = 1;
		while(!q.empty()) {
			int t = q.front();
			q.pop();
			int p = priority[t];
			bool flag = false; //如果还有更高级的任务，则置1
			for(int i=maxp-1; i>p; --i) {
				if(pcnt[i] > 0) {
					flag = true;
					break;
				}
			}
			if(flag) {q.push(t); continue;}

			//没有更高级的任务了
				if(t == m) break;
				pcnt[p]--;
				assert(pcnt[p] >= 0);
				time++;
			}
		cout << time << endl;
	}
	return 0;
}
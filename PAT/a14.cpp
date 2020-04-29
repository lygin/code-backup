#include <bits/stdc++.h>
using namespace std;

struct node {
	int poptime;
	int endtime;
	queue<int> q;
};

int main() {
	int n, m, k, q;
	scanf("%d%d%d%d", &n, &m, &k, &q);
	int time[k+1], result[k+1];
	node windows[n+1];
	for(int i=1; i<=k; ++i) scanf("%d", &time[i]);
	int cnt = 1;
	for(int i=1; i<=m; i++)
		for(int j=1; j<=n; ++j)
			if(cnt <= k) {
				windows[j].q.push(time[cnt]);
				if(i == 1) {
					windows[j].poptime = time[cnt];
					windows[j].endtime = time[cnt];
					result[cnt] = time[cnt];
				} else {
					if(windows[j].endtime >= 540) {
						result[cnt] = -1;
						windows[j].endtime += time[cnt];
					} else {
						windows[j].endtime += time[cnt];
						result[cnt] = windows[j].endtime;
					}
				}
				cnt++;
			}
	while(cnt <= k) {
		int mintime = windows[1].poptime, minpos = 1;
		for(int i=2; i<=n; ++i)
			if(windows[i].poptime < mintime) {
				mintime = windows[i].poptime;
				minpos = i;
			}
		windows[minpos].q.pop();
		windows[minpos].q.push(time[cnt]);
		windows[minpos].poptime += windows[minpos].q.front();
		if(windows[minpos].endtime >= 540) {
			result[cnt] = -1;
			windows[minpos].endtime += time[cnt];
		} else {
			windows[minpos].endtime += time[cnt];
			result[cnt] = windows[minpos].endtime;
		}
		cnt++;
	}
	for(int i=1; i<=q; ++i) {
		int tmp;
		scanf("%d", &tmp);
		if(result[tmp] < 0) printf("Sorry\n");
		else {
			printf("%02d:%02d\n", (result[tmp]+480)/60, (result[tmp]+480)%60);
		}
	}
	return 0;
}

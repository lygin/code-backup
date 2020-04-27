#include <bits/stdc++.h>
using namespace std;

const int maxt = 1000+10;	//最大队数

int main() {
	freopen("in.txt", "r", stdin);
	int t, kase = 1;
	while(cin >> t) {
		if(t == 0) break;
		printf("Scenario #%d\n", kase++);

		map<int,int> team;	//team[x]表示编号为x的人所在团队编号
		for(int i=0; i<t; ++i) {
			int n, x;
			cin >> n;
			while(n--) {cin >> x; team[x] = i;}	//输入队员
		}

		//模拟
		queue<int> q, q2[maxt];	//q2[i]表示团队i的队列
		while(1) {
			string cmd;
			cin >> cmd;
			if(cmd[0] == 'S') break;
			else if(cmd[0] == 'E') {
				int x;
				cin >> x;
				int t = team[x]; //x的队号
				if(q2[t].empty()) q.push(t); //团队t入队
				q2[t].push(x);
			}
			else if(cmd[0] == 'D') {
				int t = q.front();
				cout << q2[t].front() << endl;
				q2[t].pop();
				if(q2[t].empty()) q.pop();
			}
		}
		cout << endl;
	}
}
#include <bits/stdc++.h>
using namespace std;
const int INF = 1 << 30;

vector<vector<int> > G(10005);
unordered_map<int, int> line;
vector<int> vis(10005,0);
int st, ed;

int MIND = INF, MINC = INF;
vector<int> tmpath, path;

int calC(vector<int>& p) {
	int sumC = -1, preLine = -1;//很关键
	for(int i=0; i<p.size()-1; ++i) {//从起点走到终点，共n-1条路
		int curLine = line[p[i]*10000+p[i+1]];
		if(curLine != preLine) {
			preLine = curLine;
			sumC ++;
		}
	}
	return sumC;
}
void dfs(int u) {
	if(u == ed && (tmpath.size() < MIND || (tmpath.size() == MIND && calC(tmpath) < MINC))) {
		MIND = tmpath.size();
		MINC = calC(tmpath);
		path = tmpath;
	}
	if(u == ed) {
		return;
	}
	for(int v : G[u]) {
		if(vis[v]) continue;//访问过就跳过
		vis[v] = 1;
		tmpath.push_back(v);
		dfs(v);
		tmpath.pop_back();
		vis[v] = 0;
	}
}
void print_ans();

int main() {
	freopen("in.txt", "r", stdin);
	int n,m,pre,cur;
	cin >> n;
	for(int i=1; i<=n; ++i) {
		cin >> m >> pre;
		for(int j=1; j<m; ++j) {
			scanf("%d", &cur);
			G[pre].push_back(cur);
			G[cur].push_back(pre);
			line[pre*10000+cur] = line[cur*10000+pre] = i;
			pre = cur;
		}
	}
	int k;
	cin >> k;
	for(int i=0; i<k; ++i) {
		scanf("%d%d", &st, &ed);
		//init
		MIND = INF, MINC = INF;
		//init
		tmpath.push_back(st);
		vis[st] = 1;
		dfs(st);
		vis[st] = 0;
		tmpath.pop_back();
		print_ans();
	}
	return 0;
}

void print_ans() {
	printf("%d\n", MIND-1);
	int preLine = -1, preS = st;
	for(int i=0; i<path.size()-1; ++i) {
		int curLine = line[path[i]*10000+path[i+1]];
		if(curLine != preLine) {//从path[i]开始换路
			if(preLine != -1) printf("Take Line#%d from %04d to %04d.\n", preLine, preS, path[i]);//打印path[i]之前的路
			preLine = curLine;
			preS = path[i];//上条路的终点=这条路的起点
		}
	}
	printf("Take Line#%d from %04d to %04d.\n", preLine, preS, ed);//最后一步
}
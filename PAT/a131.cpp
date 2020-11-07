#include <bits/stdc++.h>
using namespace std;
const int INF = 1 << 30;
//双向搜索，BFS找最短路，DFS从最短路中取最优解
vector<vector<int>> G(10005);//保存图
unordered_map<int, int> line;//保存两点之间属于哪条线路，第一个int为 起始点*10000+结束点
vector<vector<int>> pre(10005);//保存最短路关系
int st, ed;
void bfs() {
	//init
	for(int i=0; i<10005; ++i) pre[i].clear();
	vector<int> dist(10005, INF);
	//init
	queue<int> q;
	q.push(st);
	dist[st] = 0;
	while(!q.empty()) {
		int cur = q.front(); q.pop();
		if(cur == ed) return ;
		for(int u : G[cur]) {
			if(dist[cur] + 1 < dist[u]) {
				q.push(u);
				dist[u] = dist[cur]+1;
				pre[u].push_back(cur);
			} else if(dist[cur] + 1 == dist[u]) {
				pre[u].push_back(cur);
			}
		}
	}
}
vector<int> path;//临时路径
int MIND = INF, MINC = INF;//最短dist和最小conjection
string ans;//打印信息

string mytostr(int x) {
	string ans = to_string(x);
	while(ans.size() < 4) {
		ans = "0"+ans;
	}
	return ans;
}

void dfs(int u, int csum, int preline) {
	if(u == st && (path.size() < MIND || (path.size() == MIND && csum < MINC))) {
		MIND = path.size();
		MINC = csum;
		ans.clear();
		ans += to_string(MIND-1)+"\n";
		//printf("%d\n", MIND-1);
		int preline = -1;
		int prest = st;
		for(int i=path.size()-1; i>0; --i) {//从起点开始
			int curline = line[path[i]*10000+path[i-1]];
			if(curline != preline) {
				if(preline != -1) 
					ans += "Take Line#" +to_string(preline)+" from " + mytostr(prest) + " to " + mytostr(path[i]) + ".\n";
				//printf("Take Line#%d from %d to %d.\n",preline,prest,path[i]);
				preline = curline;
				prest = path[i];
			}
		}
		ans += "Take Line#" +to_string(preline)+" from " + mytostr(prest) + " to " + mytostr(ed) + ".\n";
		//printf("Take Line#%d from %d to %d.\n",preline,prest,ed);
	}
	if(u == st) return ;
	for(int v : pre[u]) {
		//cout << v << endl;
		path.push_back(v);
		if(line[v*10000+u] == preline) dfs(v,csum,preline);
		else {
			dfs(v,csum+1,line[v*10000+u]);
		}
		path.pop_back();
	}
}
int main() {
	freopen("in.txt", "r", stdin);
	int N;
	cin >> N;
	for(int i=1; i<=N; ++i) {
		int m;
		int pre, cur;
		scanf("%d%d", &m, &pre);
		for(int j=1; j<m; ++j) {
			scanf("%d", &cur);
			G[cur].push_back(pre);
			G[pre].push_back(cur);
			line[pre*10000+cur] = line[cur*10000+pre] = i;//line
			pre = cur;
		}
	}
	int K;
	cin >> K;
	while(K--) {
		scanf("%d%d", &st, &ed);
		//init
		MIND = INF, MINC = INF;
		path.clear();
		//init	
		bfs();
		//printf("test:%d\n", pre[2302].size());
		//cout << "fine";
		path.push_back(ed);
		dfs(ed,0,-1);
		cout << ans;
	}
	return 0;
}

#include <bits/stdc++.h>
using namespace std;

int r0,c0,dir,r2,c2;
int has_edge[10][10][4][3];
int d[10][10][4];
node p[10][10][4];

struct node
{
	int r;
	int c;
	int dir;
	node(int r, int c, int dir): r(r), c(c), dir(dir) {}
};

const char* dirs = "NESW";
const char* turns = "FLR";

int dir_id(char c) {return strchr(dirs,c) - dirs;}
int turn_id(char c) {return strchr(turns,c) - turns;}

const int dr[4] = {-1,0,1,0};
const int dc[4] = {0,1,0,-1};

node walk(const node& v, int turn) {
	int dir = u.dir;
	if(turn == 1) dir = (dir+3)%4; //左转
	if(turn == 2) dir = (dir+1)%4; //右转
	return node(v.r+dr[dir], v.c+dc[dir], dir);
}

void print_ans(node u) {
	vector<node> ans;
	for(;;) {
		ans.push_back(u);
		if(d[u.r][u.c][u.dir] == 0) break;
		u = p[u.r][u.c][u.dir];
	}
	ans.push_back(node(r0,c0,dir));

	int cnt = 0;
	for(int i=ans.size()-1; i>=0; --i) {
		if(cnt%10 ==0) printf(" ");
		printf(" (%d,%d)", nodes[i].r, nodes[i].c);
		if(++cnt % 10 == 0) printf("\n");
	}
}

void solve() {
	queue<node> q;
	memset(d, -1, sizeof(d));
	node u(r1,c1,dir); //起点
	d[u.r][u.c][u.dir] = 0;
	q.push(u);
	while(!q.empty()) {
		node v = q.front(); q.pop();
		if(v.r == r2 && v.c == c2) {
			print_ans(v);
			return;
		}
		for(int i=0; i<3; ++i) {//三种转向
			node u = walk(v,i);
			if(has_edge[v.r][v.c][v.dir][i] && inside(v.r, v.c) &&
				d[u.r][u.c][u.dir] < 0) {
				d[u.r][u.c][u.dir] = d[v.r][v.c][v.dir]+1;
				p[u.r][u.c][u.dir] = v;
				q.push(u);
			}
		}
	}
	printf("No Solution Possible\n");
}

int main() {
	freopen("in.txt", "r", stdin);
	string s;
	while(cin >> s && s != "END") {
		cout << s << endl;
		scanf("%d %d %c %d %d", &r0, &c0, &dir, &r2, &c2);
		int x,y;
		
	}
}
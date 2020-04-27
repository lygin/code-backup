#include <bits/stdc++.h>
using namespace std;

const int LEN = 362880;	// 共9！种状态

struct node
{
	int state[9];	// 记录八数码排列，即一个状态
	int dis;
};

int dir[4][2] = {	//左，上，右，下顺时针方向
	{-1,0},
	{0,-1},
	{1,0},
	{0,1},
};

int visited[LEN] = {0};	// cantor判重，若某状态访问过置为一
int start[9];
int goal[9];
long factory[] = {1,1,2,6,24,120,720,5040,40320,362880};	// cantor判重用到的常数，从0！到9！

bool cantor(int str[], int n) {
	long result = 0;
	for(int i=0; i<n; ++i) {
		int cnt = 0;
		for(int j=i+1; j<n; ++j)
			if(str[i] > str[j])
				cnt++;
		result += cnt*factory[n-i-1];
	}
	if(!visited[result]) {
		visited[result] = 1;
		return true;
	}
	else return false;
}

int bfs() {
	node head;
	memcpy(head.state, start, sizeof(head.state));
	head.dis = 0;
	queue<node> q;
	cantor(head.state, 9);
	q.push(head);

	while(!q.empty()) {
		head = q.front();
		q.pop();
		int z;
		for(z=0; z<9; ++z)
			if(head.state[z] == 0)	//寻找元素0的位置
				break;

		// z的二维转换
		int x = z%3;
		int y = z/3;

		// 向四个方向转移新状态
		for(int i=0; i<4; ++i) {
			int nx = x + dir[i][0];
			int ny = y + dir[i][1];
			int nz = ny*3 + nx;	// 二维化一维
			if(nx >= 0 && nx <3 && ny >= 0 && ny < 3) {	//未越界
				node nnode;
				memcpy(&nnode, &head, sizeof(struct node));
				swap(nnode.state[z], nnode.state[nz]);
				nnode.dis++;
				if(memcmp(nnode.state, goal, sizeof(goal)) == 0)	//与目标状态比较
					return nnode.dis;
				if(cantor(nnode.state, 9))	//判重
					q.push(nnode);	//把新的状态放进队列
			}
		}
	}
	return -1;	//没找到
}

int main() {
	freopen("in.txt", "r", stdin);
	for(int i=0; i<9; ++i)
		cin >> start[i];
	for(int i=0; i<9; ++i)
		cin >> goal[i];
	int num = bfs();
	if(num != -1)
		cout << num << endl;
	else
		cout << "impossible" << endl;
	return 0;
}

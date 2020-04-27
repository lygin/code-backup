#include <bits/stdc++.h>
using namespace std;

#define INF 100000000
#define MAX_N 20
#define MAX_M 20

typedef pair<int, int> point;

char maze[MAX_N][MAX_M];
int Sx, Sy;
int Gx, Gy;
int m = 4, n = 5;

int dx[4] = {1,0,-1,0};
int dy[4] = {0,-1,0,1};

int dis[MAX_N][MAX_M] = {0};

int bfs() {
	for(int i=0; i<m; ++i)
		for(int j=0; j<n; ++j)
			dis[i][j] = INF;
	queue<point> que;
	que.push(point(Sx, Sy));
	dis[Sx][Sy] = 0;
	while(!que.empty()) {
		point P = que.front();
		que.pop();
		if(P.first == Gx && P.second == Gy) break;
		for(int i=0; i<4; ++i) {  // four direction
			int nx = P.first + dx[i];
			int ny = P.second + dy[i];
			if(nx >= 0 && nx < m && ny >= 0 && ny < n && dis[nx][ny] == INF && maze[nx][ny] != '#') {
				que.push(point(nx, ny));
				dis[nx][ny] = dis[P.first][P.second] + 1;
			}
		}
	}
	return dis[Gx][Gy];
	}

int main() {
	freopen("in.txt", "r", stdin);
	for(int i=0; i<m; ++i)
		for(int j=0; j<n; ++j) {
			scanf("%c", &maze[i][j]);
			if(maze[i][j] == 'S') {
				Sx = i;
				Sy = j;
			}
			if(maze[i][j] == 'G') {
				Gx = i;
				Gy = j;
			}
		}
	printf("res = %d\n", bfs());
	for(int i=0; i<m; ++i){
		for(int j=0; j<n; ++j)
			printf("%c", maze[i][j]);
		cout << endl;
	}
	return 0;
}

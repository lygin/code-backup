#include <bits/stdc++.h>
using namespace std;

int main(){
	freopen("in.txt", "r", stdin);
	int n ,k ,head;
	int cnt = 0;
	scanf("%d%d", &n, &k);
	queue<int> q;

	for(int i=0; i<n; ++i)
		q.push(i+1);

	while(!q.empty()) {
		head = q.front();
		q.pop();
		++cnt;

		if(cnt % k == 0 || cnt % 10 == k);
		else
			q.push(head);
	}

	printf("%d\n", head);
	return 0;
}
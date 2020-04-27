#include <bits/stdc++.h>
using namespace std;

int main() {
	int data[100010], next[100010], list[100010];
	int first,n,k;
	cin >> first >> n >> k;
	for(int i=0; i<n; ++i) {
		int tmp;
		cin >> tmp;
		cin >> data[tmp] >> next[tmp];
	}
	int idx = 0;
	while(first != -1) {
		list[idx++] = first;
		first = next[first];
	}
	for(int i=0; i<idx-idx%k; i+=k) {
		reverse(list+i,list+i+k);
	}
	for(int i=0; i<idx-1; ++i)
		printf("%05d %d %05d\n", list[i],data[list[i]],list[i+1]);
	printf("%05d %d -1",list[idx-1],data[list[idx-1]]);
		return 0;
}

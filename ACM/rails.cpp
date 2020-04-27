#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000+10;
int n, target[maxn];

int main() {
	freopen("in.txt", "r", stdin);
	while(cin >> n) {
		stack<int> s;
		int a=1, b=1;
		for(int i=1; i<=n; ++i) {
			scanf("%d", &target[i]);
		}
		int ok = 1;
		while(b <= n) {
			if(a == target[b]) {
				a++;
				b++;
			}
			else if(!s.empty() && s.top() == target[b]) {
				s.pop();
				b++;
			}
			else if(a <= n) {
				s.push(a++);
			}
			else {
				ok = 0;
				break;
			}
		}
		printf("%s\n", ok ? "YES" : "NO");
	}
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
char b[7] = "PATest";
int cid(char c) {
	int ans = -1;
	if(c == 'P') ans = 0;
	if(c == 'A') ans = 1;
	if(c == 'T') ans = 2;
	if(c == 'e') ans = 3;
	if(c == 's') ans = 4;
	if(c == 't') ans = 5;
	return ans;
}
int a[7] = {0};
int main() {
	string s;
	getline(cin, s);
	for(int i=0; i<s.size(); ++i)
		if(cid(s[i]) != -1) a[cid(s[i])]++;
	while(1) {
		int flag = 1;
		for(int i=0; i<6; ++i)
			if(a[i]) {
				printf("%c", b[i]);
				flag = 0;
				a[i]--;
			}
		if(flag) break;
	}
	return 0;
}

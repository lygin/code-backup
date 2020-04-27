#include <bits/stdc++.h>
using namespace std;
int a[26] = {0};
int main() {
	string s;
	getline(cin,s);
	for(int i=0; i<s.size(); ++i) {
		if(isalpha(s[i])) a[tolower(s[i])-'a']++;
	}
	int maxn = 0;char c;
	for(int i=0; i<26; ++i) {
		if(a[i] > maxn) {
			maxn = a[i];
			c = i+'a';
		}
	}
	printf("%c %d", c, maxn);
	return 0;
}

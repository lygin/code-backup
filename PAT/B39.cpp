#include <bits/stdc++.h>
using namespace std;

const int N = 256;
int a[N] = {0};
int b[N] = {0};

int main() {
	string s1,s2;
	cin >> s1 >> s2;
	for(int i=0; i<s1.size(); ++i) {
		a[s1[i]]++;
	}
	for(int i=0; i<s2.size(); ++i) {
		b[s2[i]]++;
	}
	int cha = 0;
	for(int i=0; i<N; ++i) {
		if(a[i] < b[i]) {
			cha += b[i]-a[i];
		}
	}
	if(!cha) printf("Yes %d", s1.size()-s2.size());
	else printf("No %d", cha);
	return 0;
}

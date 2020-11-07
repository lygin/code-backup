#include <bits/stdc++.h>
using namespace std;

string trans(int x, int b) {
	string ans;
	while(x) {
		int tmp = x%b;
		x/=b;
		ans += to_string(tmp) + " ";
	}
	ans.pop_back();
	return ans;
}

int main() {
	int a, b;
	scanf("%d%d", &a, &b);
	string s1 = trans(a,b);
	string s2;
	stringstream ss(s1);
	string buf;
	while(getline(ss,buf,' ')) {
		s2 = " " + buf + s2;
	}
	s2 = s2.substr(1);
	printf("%s\n", s1 == s2? "Yes":"No");
	cout << s2;
	return 0;
} 

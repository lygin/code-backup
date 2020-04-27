#include <bits/stdc++.h>
using namespace std;

int main(){
	string s1, s2;
	set<char> s;
	cin >> s1 >> s2;
	for(int i=0; i<s1.size(); ++i) {
		if(s2.find(s1[i]) == string::npos && !s.count(toupper(s1[i]))) {
			printf("%c", toupper(s1[i]));
			s.insert(toupper(s1[i]));
		}
	}
	return 0;
}

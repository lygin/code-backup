#include <bits/stdc++.h>
using namespace std;

int main() {
	string s1,s2;
	int n1,n2;
	cin >> s1 >> n1 >> s2 >> n2;
	string a1, a2;
	for(int i=0; i<s1.size(); ++i) 
		if(s1[i] == n1+'0') a1.push_back(s1[i]);
	for(int i=0; i<s2.size(); ++i)
		if(s2[i] == n2 + '0') a2.push_back(s2[i]);
	long a = a1.size()?stoi(a1):0;
	long b = a2.size()?stoi(a2):0;
	cout << a+b;
	return 0;
}

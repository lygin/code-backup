#include <bits/stdc++.h>
using namespace std;
string tab[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main() {
	string s;
	cin >> s;
	int sum = 0;
	for(int i=0; i<s.size(); ++i)
		sum += s[i] - '0';
	string str = to_string(sum);
	for(int i=0; i<str.size(); ++i) {
		if(i != 0) cout << " ";
		cout << tab[str[i]-'0'];
	}
	return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;
	getline(cin,s); 
	int sum = 0;
	for(char c: s) {
		if(isalpha(c))
			sum += tolower(c)-'a'+1;
	}
	int n0 = 0,n1= 0;
	while(sum) {
		if(sum%2) n1++;
		else n0++;
		sum /= 2;
	}
	printf("%d %d", n0,n1);
	return 0;
}

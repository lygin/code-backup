#include <bits/stdc++.h>
using namespace std;

string week[7] = {"MON", "TUE", "WED" ,"THU", "FRI", "SAT", "SUN"};

int main() {
	string s1,s2,s3,s4;
	cin >> s1 >> s2 >> s3 >> s4;
	char c1,c2;
	int i=0, j=0;
	while(i<s1.size() && i<s2.size()) {
		if(s1[i] == s2[i] && (s1[i] >= 'A' && s1[i] <= 'G')) {
			c1 = s1[i];
			break;
		}
		i++;
	}
	i++;
	while(i<s1.size() && i<s2.size()) {
		if(s1[i] == s2[i] && ((s1[i] >= 'A' && s1[i] <= 'N') || isdigit(s1[i]))) {
			c2 = s1[i];
			break;
		}
		i++;
	}
	int pos;
	while(j<s3.size() && j < s4.size()) {
		if(s3[j] == s4[j] && isalpha(s3[j])) {
			pos = j;
			break;
		}
		j++;
	}
	int shi = isdigit(c2)?c2-'0':c2-'A'+10;
	cout << week[c1-'A'];
	printf(" %02d:%02d", shi,pos);
	return 0;
} 

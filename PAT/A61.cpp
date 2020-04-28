#include <bits/stdc++.h>
using namespace std;

string week[7] = {"MON ", "TUE ", "WED ", "THU ", "FRI ", "SAT ", "SUN "};

int main() {
	string s1, s2, s3, s4;
	cin >> s1 >> s2 >> s3 >> s4;
	int i;
	for(i=0; i<s1.size() && i<s2.size(); ++i) {
		if(s1[i] == s2[i] && s1[i] >= 'A' && s1[i] <= 'G') {
			cout << week[s1[i] - 'A'];
			break;
		}
	}
	for(i++;i<s1.size() && i<s2.size(); ++i) {
		if(s1[i] == s2[i] && s1[i] >= '0' && s1[i] <'9') {
			printf("%02d:", s1[i] - '0');
			break;
		} else if(s1[i] == s2[i] && s1[i] >='A' && s1[i] <= 'N') {
			printf("%02d:", s1[i] - 'A'+10);
			break;
		}
	}
	for(int j=0; j<s3.size() && j<s4.size(); ++j) {
		if(s3[j] == s4[j] && isalpha(s3[j])) {
			printf("%02d", j);
			break;
		}
	}
	return 0;
}

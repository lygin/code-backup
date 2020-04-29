#include <bits/stdc++.h>
using namespace std;

string tab[10] = {"ling","yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
string tab2[4] = {"Ge", "Shi", "Bai", "Qian"};
int tab3[4] = {1, 10, 100, 1000};
string tab4[2] = {"Yi", "Wan"};
int main() {
	int a;
	bool zero = false;
	bool go = false;
	string buf = "";
	cin >> a;
	if(a < 0) {
		buf += "Fu ";
		a = -a;
	}
	if(a == 0) {
		cout << "ling";
		return 0;
	}
	int part[3];
	part[0] = a/100000000;
	part[1] = (a%100000000)/10000;
	part[2] = a%10000;
	for(int j=0; j<3; ++j) {
		for(int i=3; i>=0; --i) {
			int tmp = (part[j]/tab3[i]) % 10; // 取出当前数字 
			if(!tmp) zero = true;
			else {
				if(zero && go) buf += "ling ";
				buf += tab[tmp] + " ";
				if(i != 0) buf += tab2[i] + " ";
				zero = false;
				go = true;
			}
		}
		if(j != 2 && part[j] > 0) buf += tab4[j] + " ";
	}
	buf.pop_back();
	cout << buf;
	return 0;
} 

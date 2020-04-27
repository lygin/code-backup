#include <bits/stdc++.h>
using namespace std;

int chance;
set<char> lft;
int win, lose;

void guess(char c) {
	if(lft.count(c)) lft.erase(c);
	else --chance;
	if(!chance) lose = 1;
	if(!lft.size()) win = 1;
}

int main() {
	freopen("in.txt", "r", stdin);
	int rnd;
	string s, s2;
	while(cin >> rnd >> s >> s2) {
		if(rnd == -1) break;
		printf("Round %d\n", rnd);
		//每轮初始化
		win = lose = 0; 
		lft.clear(); 
		for(char c: s) lft.insert(c);
		chance = 7;

		for(char c: s2) {
			guess(c);
			if(win || lose) break;
		}

		if(win) printf("You win.\n");
		else if(lose) printf("You lose.\n");
		else printf("You chickened out.\n");
	}
	return 0;
}
#include <bits/stdc++.h>
using namespace std;

map<char, int> tb;
char id[]= "JCB";
int cmp(char a, char b) {
	if(a == 'C' && b == 'J') return 1;
	else if(a == 'C' && b == 'B') return -1;
	else if(a == 'J' && b == 'B') return 1;
	else if(a == 'J' && b == 'C') return -1;
	else if(a == 'B' && b == 'C') return 1;
	else if(a == 'B' && b == 'J') return -1;
	return 0;
}

int main() {
	tb['J'] = 0; tb['C'] = 1; tb['B']=2;
	int n;
	char a,b;
	int wina = 0, winb = 0;
	int acnt[3] = {0}, bcnt[3] = {0};
	scanf("%d", &n);
	for(int i=0; i<n; ++i) {
		scanf("\n");
		scanf("%c %c", &a, &b);
		if(cmp(a,b) > 0) {
			wina++;
			acnt[tb[a]]++;
		}
		else if(cmp(a,b) < 0) {
			winb++;
			bcnt[tb[b]]++;
		}
	}
	printf("%d %d %d\n", wina, n-wina-winb, winb);
	printf("%d %d %d\n", winb, n-wina-winb, wina);
	int mpos1 = 0,mpos2 = 0;
	for(int i=1; i<3; ++i) {
		if(acnt[i] >= acnt[mpos1]) mpos1 = i;
		if(bcnt[i] >= bcnt[mpos2]) mpos2 = i;
	}
	printf("%c %c", id[mpos1], id[mpos2]);
	return 0;
}

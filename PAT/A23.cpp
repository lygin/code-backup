#include <bits/stdc++.h>
using namespace std;

char num[22];
int flag[10];
int main() {
	scanf("%s", num);
	int len = strlen(num);
	int cf = 0;
	for(int i=len-1; i>=0; --i) {
		int tmp = num[i]-'0';
		flag[tmp]++;
		tmp = tmp * 2 + cf;
		cf = tmp / 10;
		num[i] = tmp % 10 + '0';
		flag[tmp%10]--;
	}
	int flag2 = 0;
	for(int i=0; i<10; ++i)
		if(flag[i] != 0) flag2 = 1;
	printf("%s\n", (flag2 || cf)?"No" : "Yes");
	if(cf) printf("%d", cf);
	printf("%s", num);
	return 0; 
}

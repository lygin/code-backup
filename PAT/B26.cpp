#include <bits/stdc++.h>
using namespace std;

int main() {
	int a,b;
	scanf("%d%d", &a,&b);
	int sec = (int)((b-a)/100.0+0.5);
	int hour = sec/3600;
	sec -= hour*3600;
	int mi = sec/60;
	sec -= mi*60;
	printf("%02d:%02d:%02d", hour, mi, sec);
	return 0;
}

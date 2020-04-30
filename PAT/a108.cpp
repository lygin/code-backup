#include <bits/stdc++.h>
using namespace std;

int main() {
	char a[100], b[100];
	int n, cnt = 0;
	double sum = 0.0;
	cin >> n;
	for(int i=0; i<n; ++i) {
		double t1;
		scanf("%s", a);
		sscanf(a, "%lf", &t1);
		sprintf(b, "%.2lf", t1);
		int flag = 0;
		for(int i=0; i<strlen(a); ++i)
			if(a[i] != b[i]) flag = 1;
		if(flag || t1 < -1000 || t1 > 1000) {
			printf("ERROR: %s is not a legal number\n", a);
		} else {
			sum += t1;
			cnt ++;
		}
	}
	if(cnt == 0) printf("The average of 0 numbers is Undefined");
	else if(cnt == 1) printf("The average of 1 number is %.2f", sum);
	else printf("The average of %d numbers is %.2f", cnt, sum/cnt);
	return 0;	
}

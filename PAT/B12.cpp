#include <bits/stdc++.h>
using namespace std;

const int N = 5;
vector<int> a[N];
int main() {
	int n,x;
	scanf("%d", &n);
	while(n--) {
		scanf("%d", &x);
		a[x%5].push_back(x);
	}
	if(a[0].size()) {
		int sum = 0;
		for(int i=0; i<a[0].size(); ++i)
			if(a[0][i]%2 == 0) sum += a[0][i];
		if(sum) printf("%d", sum);
		else  printf("N");
	}
 	else  printf("N");
	
	if(a[1].size()) {
		int sum2 = 0, flag = 1;
		for(int i=0; i<a[1].size(); ++i) {
			sum2 += a[1][i]*flag;
			flag = -flag;
		}
		printf(" %d", sum2);
	}
	else printf(" N");
	
	if(a[2].size()) {
		printf(" %d", a[2].size());
	}
	else printf(" N");
	
	if(a[3].size()) {
		double sum3 = 0;
		for(int i=0; i<a[3].size(); ++i)
			sum3 += a[3][i];	
		printf(" %.1f", sum3*1.0/a[3].size());
	}
	else printf(" N");
	
	if(a[4].size()) {
		int mx = a[4][0];
		for(int i=1; i<a[4].size(); ++i)
			mx = max(mx,a[4][i]);
		printf(" %d",mx);
	}
	else printf(" N");
	return 0;
}

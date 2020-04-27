#include <bits/stdc++.h>
using namespace std;

int main(){
	double a,b,c,d;
	scanf("%lf%lf%lf%lf", &a,&b,&c,&d);
	double shi = a*c*(cos(b)*cos(d)-sin(b)*sin(d));
	double xv = a*c*(sin(b)*cos(d)+cos(b)*sin(d));
	if(shi<0 && shi+0.005 >= 0) printf("0.00");
	else printf("%.2lf",shi);
	if(xv<0 && xv+0.005 >= 0) printf("+0.00i");
	else if(xv>=0) printf("+%.2lfi",xv);
	else printf("%.2lfi",xv);
	return 0;
}

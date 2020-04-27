#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("in.txt", "r", stdin);
    int n;
    cin >> n;
    char a[50], b[50];
    double sum = 0;
    int cnt = 0;
    while(n--) {
        scanf("%s", a);
        double tmp;
        sscanf(a,"%lf",&tmp);
        sprintf(b,"%.2f",tmp);
        int flag = 0;
        for(int i=0; i<strlen(a); ++i) {
            if(a[i] != b[i]) flag = 1;
        }
        if(tmp > 1000 || tmp < -1000 || flag ) {
            printf("ERROR: %s is not a legal number\n", a);
        }
        else {
            ++cnt;
            sum += tmp;
        }
    }
    if(cnt == 1)
        printf("The average of 1 number is %.2f", sum);
    else if(cnt > 1)
        printf("The average of %d numbers is %.2f", cnt, sum / cnt);
    else
        printf("The average of 0 numbers is Undefined");
    return 0;
}
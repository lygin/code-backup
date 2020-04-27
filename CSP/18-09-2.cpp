#include <bits/stdc++.h>
using namespace std;

const int N = 1000000;
int cnt[N+1];

int main() {
    freopen("in.txt", "r", stdin);
    int n, a, b;
    int ans = 0;

    memset(cnt, 0, sizeof(cnt));
    scanf("%d", &n);

    for(int i=0; i<2*n; ++i) {
        scanf("%d%d", &a, &b);
        for(int j=a; j<b; ++j)  //切记j<b，若等于则为时间点了，但实际上一个区间相交后应该为时间段，故为时间点数减1，不妨左闭右开，则赋值的即为时间段
            cnt[j]++;
    }

    for(int i=1; i<=N; ++i)
        if(cnt[i] == 2)
            ++ans;

    printf("%d\n", ans);
    return 0;
}


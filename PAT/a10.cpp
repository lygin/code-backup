#include <bits/stdc++.h>
using namespace std;

long long convert(string s, long long rdx) {
	int len = s.size();
	long long ans = 0;
	for(int i=len-1; i>=0; --i) {
		ans += (isdigit(s[i])?s[i]-'0':s[i]-'a'+10) * pow(rdx, len-1-i);
	}
	return ans;
}

void find_rdx(string s, long long num) {
	char maxc = s[0];
	for(int i=1; i<s.size(); ++i) {
		if(s[i] > maxc) maxc = s[i];
	}
	long long low = isdigit(maxc)? maxc-'0'+1 : maxc-'a'+11;
	long long high = max(low, num);
	while(low <= high) {
		long long mid = (low+high)/2;
		long long tmp = convert(s, mid);
		if(tmp == num) {
			cout << mid;
			return;
		} else if(tmp > num || tmp < 0) {
			high = mid-1;
		} else low = mid+1;
	}
	printf("Impossible");
}


int main() {
	string n1, n2;
	long long tag, rdx;
	cin >> n1 >> n2 >> tag >> rdx;
	tag == 1? find_rdx(n2, convert(n1, rdx)) : find_rdx(n1, convert(n2, rdx));
	return 0;
}

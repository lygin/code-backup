#include <bits/stdc++.h>
using namespace std;

int main() {
	int n,tmp;
	cin >> n;
	set<int> st;
	while(n--) {
		int sum = 0;
		cin >> tmp;
		while(tmp) {
			sum += tmp%10;
			tmp /= 10;
		}
		st.insert(sum);
	}
	cout << st.size() << endl;
	for(auto it=st.begin(); it!= st.end(); ++it) {
		if(it!=st.begin()) cout << " ";
		cout << *it;
	}
	return 0;
}

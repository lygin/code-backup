#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("in.txt", "r", stdin);
	vector<string> v[3];
	string line;
	for(int i=0; i<3; ++i) {
		getline(cin,line);
		for(int j=0,k=0; j<line.size();++j) {
			if(line[j] == '[') {
				k = j+1;
				while(k<line.size() && line[k] != ']') {++k;}
				if(k < line.size()) v[i].push_back(line.substr(j+1,k-j-1));
				j = k;
			}
		}
	}
	int n;
	cin >> n;
	int a, b, c, d, e;
	while(n--) {
		cin >> a >> b >> c >> d >> e;
		if(a > v[0].size() || b>v[1].size() || c>v[2].size() || d>v[1].size() ||
			e > v[0].size() || a<1 || b <1 || c<1 || d<1 || e<1) {
			cout << "Are you kidding me? @\\/@" << endl;
			continue;
		}
		cout << v[0][a-1] << "(" << v[1][b-1] << v[2][c-1] << v[1][d-1] << ")" << 
		v[0][e-1] << endl;
	}
	return 0;
}
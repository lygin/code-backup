#include <bits/stdc++.h>
using namespace std;
map<string, set<int> > title, author, key, pub, year;
int n,m;
void search(map<string, set<int> > &m, string &s) {
	if(m.count(s)) {
		for(auto it=m[s].begin(); it!=m[s].end(); ++it) {
			printf("%07d\n", *it);
		}
	} else printf("Not Found\n");
}
int main() {
	int id;
	string ti,au,ke,pu,ye;
	scanf("%d", &n);
	for(int i=0; i<n; ++i) {
		scanf("%d\n", &id);
		getline(cin, ti);
		title[ti].insert(id);
		getline(cin, au);
		author[au].insert(id);
		getline(cin, ke);
		stringstream ss(ke);
		string tmp;
		while(ss >> tmp) {
			key[tmp].insert(id);
		}
		getline(cin, pu);
		pub[pu].insert(id);
		getline(cin, ye);
		year[ye].insert(id);
	}
	scanf("%d", &m);
	for(int i=0; i<m; ++i) {
		int num;string s;
		scanf("%d: ", &num);
		getline(cin, s);
		cout << num << ": " << s << "\n";
		if(num == 1) search(title, s);
		else if(num == 2) search(author, s);
		else if(num == 3) search(key, s);
		else if(num == 4) search(pub, s);
		else if(num == 5) search(year, s); 
	}
	return 0;
}

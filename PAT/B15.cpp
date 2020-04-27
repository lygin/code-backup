
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct stu {
	int id,de,cai;
};
int cmp(struct stu a, struct stu b) {
	if((a.cai+a.de )!= (b.cai+b.de) )return (a.cai+a.de )> (b.cai+b.de);
	else if(a.de != b.de) return a.de > b.de;
	else a.id < b.id;
}
int main() {
	int n,L,H;
	scanf("%d %d %d", &n, &L, &H);
	vector<stu> v[4];
	int pass = n;
	stu tmp;
	for(int i=0; i<n; ++i) {
		scanf("%d %d %d",&tmp.id, &tmp.de, &tmp.cai);
		if(tmp.de < L || tmp.cai < L) pass--;
		else if(tmp.cai >= H && tmp.de >= H) v[0].push_back(tmp);
		else if(tmp.de >= H && tmp.cai < H) v[1].push_back(tmp);
		else if(tmp.de < H && tmp.de >= tmp.cai) v[2].push_back(tmp);
		else v[3].push_back(tmp);
	}
	printf("%d\n", pass);
	for(int i=0; i<4; ++i) {
		sort(v[i].begin(),v[i].end(), cmp);
		for(int j=0; j<v[i].size(); ++j)
		printf("%d %d %d\n",v[i][j].id,v[i][j].de,v[i][j].cai);
	}
	return 0;
}

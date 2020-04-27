#include <iostream>
using namespace std;

//输入一个子天平重量，返回该天平是否平衡
bool solve(int& w) {
	int w1,d1,w2,d2;
	bool b1 = true,b2 = true;
	cin >> w1 >> d1 >> w2 >> d2;
	if(!w1) b1 = solve(w1);
	if(!w2) b2 = solve(w2);
	w = w1+w2;
	return b1 && b2 && (w1*d1 == w2*d2);
}

int main() {
	freopen("in.txt", "r", stdin);
	int n, w;
	cin >> n;
	while(n--) {
		if(solve(w))
			cout << "YES\n";
		else 
			cout << "NO\n";
		if(n)
			cout << endl;
	}
}
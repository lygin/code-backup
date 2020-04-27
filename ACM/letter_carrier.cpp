#include <bits/stdc++.h>
using namespace std;

void parse_address(const string &s, string &user, string &mta) {
	int k = s.find('@');
	user = s.substr(0, k);
	mta = s.substr(k+1);
}

int main() {
	freopen("in.txt", "r", stdin);
	int k;
	string s, t;
	string user1, mta1; //发件信息
	string user2, mta2; //收件信息
	set<string> addr; //用户集

	//输入所有mta包含的信息，转化为用户集
	while(cin >> s && s != "*") {
		cin >> s >> k;
		while(k--) {
			cin >> t;
			addr.insert(t+"@"+s);
		}
	}

	while(cin >> s && s!= "*") {
		//处理发件信息
		parse_address(s, user1, mta1);

		vector<string> mta; //收件人的mta,按顺序发件
		map<string, vector<string> > dest; //string是mta,vector<string>是这个mta要发的人群,其中每个string代表一个地址
		set<string> vis; //防止重复发送

		//处理发件信息
		while(cin >> t && t != "*") {
			parse_address(t, user2, mta2);
			if(vis.count(t)) continue; //重复的收件人
			vis.insert(t);
			if(dest.count(mta2) == 0) {
				dest[mta2] = vector<string>();
				mta.push_back(mta2);
			}
			dest[mta2].push_back(t);
		}

		getline(cin, t);
		string data;
		while(getline(cin, t) && t[0] != '*') data += "     " + t + "\n";

		for(int i=0; i<mta.size(); ++i) {
			string mta2 = mta[i];
			vector<string> users = dest[mta2];
			cout << "Connection between " << mta1 << " and " << mta2 <<endl;
			cout << "     HELO " << mta1 << "\n";
			cout << "     250\n";
			cout << "     MAIL FROM:<" << s << ">\n";
			cout << "     250\n";
			bool ok = false; //是否发送data
			for(int i=0; i<users.size(); ++i) {
				cout << "     RCPT TO:<" << users[i] << ">\n";
				if(addr.count(users[i])) {
					ok = true;
					cout << "     250\n";
				}
				else cout << "     550\n";
			}
			if(ok) {
				cout << "     DATA\n";
				cout << "     354\n";
				cout << data;
				cout << "     .\n";
				cout << "     250\n";
			}
			cout << "     QUIT\n";
			cout << "     221\n";
		}

	}
	return 0;
}
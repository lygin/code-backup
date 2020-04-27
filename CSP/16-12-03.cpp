#include <bits/stdc++.h>
using namespace std;

const int NOVALUE = -1;
const int TRUE = -2;
const int FALSE = -3;

struct _privilege
{
	string category;
	int level;
};

vector<_privilege> privileges;

struct _role
{
	string role;
	int s;	// 该角色的权限privilege的个数
	vector<_privilege> privileges;
};

vector<_role> roles;

struct _user
{
	string user;
	int t;  // 该用户的角色个数
	vector<string> roles;
};

vector<_user> users;

string getcategory(string s) {
	int pos = s.find(":");
	if(pos != (int)string::npos) {
		return s.substr(0, pos);
	}
	else
		return s;
}

int getlevel(string s) {
	int pos = s.find(":");
	if(pos != (int)string::npos)
		return atoi(s.substr(pos+1).c_str());
	else
		return NOVALUE;
}

int privilegematch(_privilege p1, _privilege p2) {
	if(p1.category != p2.category)
		return FALSE;
	else if(p2.level == NOVALUE) {
		//  不带等级查询
		if(p1.level == NOVALUE)
			return TRUE;
		else {	// 分等级不带等级查询返回最高等级
			return p1.level;
		}
	}

	else {	// 带等级查询
		if(p1.level == NOVALUE)
		return TRUE;
		else {
			if(p1.level >= p2.level)
				return TRUE;
			else
				return FALSE;
		}
	}
}

int rolematch(string r, _privilege p) {

	int ans = FALSE;

	for(int i=0; i<roles.size(); ++i) {
		if(r == roles[i].role) {
			for(int j=0; j<roles[i].s; ++j) {
				int rt = privilegematch(roles[i].privileges[j], p);
				if(rt > ans)
					ans = rt;
			}
		}
	}

	return ans;
}

int usermatch(string u, _privilege p) {
	int ans = FALSE;

	for(int i=0; i<users.size(); ++i) {
		if(u == users[i].user) {
			for(int j=0; j<users[i].t; ++j) {
				int ut = rolematch(users[i].roles[j], p);
				if(ut > ans)
					ans = ut;
			}
		}
	}
	return ans;
}

int main() {
	freopen("in.txt", "r", stdin);
	int p, r, u, q;
	string str;
	_privilege pri;

	cin >> p;

	for(int i=0; i<p; ++i) {
		cin >> str;
 		
 		pri.category = getcategory(str);
 		pri.level = getlevel(str);
 		privileges.push_back(pri);
	}

	cin >> r;

	for(int i=0; i<r; ++i) {
		_role rl;

		cin >> rl.role >> rl.s;
		for(int j=0; j<rl.s; ++j) {
			cin >> str;

			pri.category = getcategory(str);
			pri.level = getlevel(str);
			rl.privileges.push_back(pri);
		}

		roles.push_back(rl);
	}

	// 输入用户数量
	cin >> u;

	for(int i=0; i<u; ++i) {
		_user us;

		cin >> us.user >> us.t;

		for(int j=0; j<us.t; ++j) {
			cin >> str;
			us.roles.push_back(str);
		}

		users.push_back(us);
	}

	// 输入查询数量q
	cin >> q;
	string suser;

	for(int i=0; i<q; ++i) {
		cin >> suser >> str;

		// 待查询权限初始化
		pri.category = getcategory(str);
		pri.level = getlevel(str);

		int ans = usermatch(suser, pri);

		if(ans == TRUE)
			cout << "true" << endl;
		else if(ans == FALSE)
			cout << "false" << endl;
		else
			cout << ans << endl;
	}

	return 0;

}
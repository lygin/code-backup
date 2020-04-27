#include <bits/stdc++.h>
using namespace std;

int n, m;
string s, key;
map<string,string> json;
int state;	//0:起始括号；1：输入key；2：输入val

void handle(string s) {
	for(int i=0; s[i]; ++i) {
		if(s[i] == '{') {
			if(state == 0) {
				key = "";
			}
			else {
				json[key] = "OBJECT";
			}
			state = 1;
		}

		if(s[i] == '"') {
			string tmp = "";
			for(++i; s[i]!= '"'; ++i) {
				if(s[i] == '\\') {
					tmp += s[++i];
				}
				else
					tmp += s[i];
			}

			if(state == 1) {
				if(key == "") 
					key = tmp;
				else
					key = key + '.' + tmp;
			}
			else if(state == 2) {
				json[key] = "STRING " + tmp;
				// 返回上层key的状态
				int j;
				for(j = (int)key.size()-1; j>= 0; --j) {
					if(key[j] == '.')
						break;
				}
				if(j >= 0)
					key = key.substr(0,j);
				else {	// 最外层
					key = "";
				}
			}
		}

		if(s[i] == ':')
			state = 2;

		if(s[i] == ',')
			state = 1;

		if(s[i] == '}') {	// key返回到上一层
			int j;
			for(j == (int)key.size()-1; j>=0; --j)
				if(key[j] == '.')
					break;
			if(j>=0)
				key = key.substr(0,j);
			else 
				key = "";
		}
	}
}
int main() {
	freopen("in.txt", "r", stdin);
	cin >> n >> m;

	getline(cin, s);	//获取第一行换行符，以免干扰第二行输入

	state = 0;

	while(n--) {
		getline(cin,s);
		handle(s);
	}

	while(m--) {
		cin >> s;
		if(json[s] == "")
			cout << "NOTEXIST" << endl;
		else
			cout << json[s] << endl;
	}
	return 0;
}
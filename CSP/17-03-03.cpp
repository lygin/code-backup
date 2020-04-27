#include <bits/stdc++.h>
using namespace std;

string text, line;

void solve() {
	// _text_
	size_t leftp = text.find("_");
	while(leftp != string::npos) {
		text.replace(leftp, 1, "<em>");
		size_t rightp = text.find("_", leftp);
		text.replace(rightp, 1, "</em>");
		leftp = text.find("_", rightp);
	}

	// [text](link)
	leftp = text.find("[");
	while(leftp != string::npos) {
		size_t rightp = text.find("]", leftp);
		size_t leftp2 = text.find("(", rightp);
		size_t rightp2 = text.find(")", leftp2);
		string tmp1 = text.substr(leftp+1, rightp - leftp -1);
		string tmp2 = text.substr(leftp2+1, rightp2 - leftp2 -1);
		text.replace(text.begin()+leftp, text.begin()+rightp2+1, "<a href=\"" + tmp2 + "\">" + tmp1 + "</a>");
		leftp = text.find("[", rightp2);
	}

	// #
	if(text[0] == '#') {
		int i=0;
		while(text[i] == '#') ++i;
		text = "<h" + string(1, '0' +i) + ">" + text.substr(i+1);
		text.insert(text.size() - 1, "</h" + string(1, '0' + i) + ">" );
	}

	// *
	else if(text[0] == '*') {
		text.insert(0, "<ul>\n");
		text.insert(text.size(), "</ul>\n");
		size_t leftp  = text.find("*");
		while(leftp != string::npos) {
			size_t rightp = text.find("\n", leftp);
			text.insert(rightp,"</li>");
			text.replace(leftp, 2, "<li>");
			leftp = text.find("*", rightp);
		}
	}

	// paragraph
	else {
		text = "<p>" + text.substr(0, text.size()-1) + "</p>\n";
	}

	cout << text;

	// 每输出一个区块，把区块的text初始化为""
	text = "";
}

int main(int argc, char const *argv[])
{
	freopen("in.txt", "r", stdin);
	bool flag = false;

	getline(cin, line);

	while(1) {
		if(line.size() > 0)
			text += line + "\n";
		else if(line.size() == 0 && text.size() > 0)
			solve();

		if(flag)
			break;
		if(!getline(cin, line)) {
			flag = true;
			line = "";
		}
	}
	return 0;
}
#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("in.txt", "r", stdin);
	set<string> words;
	string word, left, right;
	while(cin >> word) words.insert(word);

	for(const auto& s : words) {
		for(int i=1; i<s.size(); ++i) {
			left = s.substr(0,i);
			if(words.count(left)) {
				right = s.substr(i);
				if(words.count(right)){
					cout << s << endl;
					break;
				}
			}
		}
	}
	return 0;
}

/*
复杂度分析:
若共有n个单词，单词最大长度为m
则最坏： T = O（n*m*logn)
*/
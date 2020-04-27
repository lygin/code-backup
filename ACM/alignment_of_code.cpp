#include <bits/stdc++.h>
using namespace std;

const int maxn = 1024; //最大列数
vector<string>  linewords[maxn]; //每行的单词集为linewords[i],类型为vector<string>
size_t wordlen[maxn]; //每列单词的最大长度，wordlen[i]表示第i列的单词最大长度
size_t maxwords, linecnt; //maxwords计数列数的最大值, linecnt计数行数

int main() {
	freopen("in.txt", "r", stdin);
	string line, word;
	maxwords = 0;
	linecnt = 0;
	fill_n(wordlen, maxn, 0);
	while(getline(cin, line)) {
		stringstream ss(line);
		size_t wi = 0; //计数每列
		while(ss >> word) {
			wordlen[wi] = max(wordlen[wi], word.size());
			wi++;
			linewords[linecnt] .push_back(word);
		}
		maxwords = max(maxwords, wi);
		linecnt ++;
	}

	for(int i=0; i<linecnt; ++i) {
		const auto ls = linewords[i];
		for(int j=0; j<ls.size(); ++j) {
			cout << left << setw(j<ls.size()-1?wordlen[j]+1:0) << ls[j];
		}
		cout << endl;
	}
	return 0;
}
#include <bits/stdc++.h>
using namespace std;

struct book {
	string title, author;
	book(string t, string a) : title(t), author(a) {}
	bool operator < (const book& a) {
		if(author != a.author) return author < a.author;
		return title < a.title;
	}
};

vector<book> books;
map<string, int> bookindex;
struct indexcmp
{
	bool operator () (const int& a, const int& b) const {
		return books[a] < books[b];
	}
};

set<int, indexcmp> shelf, lib;

void borrow(string t) {
	int idx = bookindex[t];
	if(lib.count(idx)) {
		lib.erase(idx);
	}
	else {
		shelf.erase(idx);
	}
}

void retbook(string t) {
	int idx = bookindex[t];
	shelf.insert(idx);
}

void shelve() {
	for(int it : shelf) {
		int idx = it;
		auto pit = lib.insert(idx).first;
		if(pit == lib.begin())
			cout << "Put " << books[idx].title << " first" << endl;
		else {
			pit--;
			cout << "Put " << books[idx].title << " after " << books[*pit].title << endl;
		}
	}

	shelf.clear();
	cout << "END" << endl;
}

int main() {
	freopen("in.txt", "r", stdin);
	string buf;
	while(true) {
		getline(cin, buf);
		if(buf == "END") break; //no book
		int pos = buf.find(" by ");
		string title = buf.substr(0, pos);
		string author = buf.substr(pos+4);
		books.push_back(book(title, author));
		int idx = books.size() -1;
		bookindex[title] = idx;
	}

	for(int i=0; i<books.size(); ++i) {
		lib.insert(i);
	}

	string cmd, title;
	while(true) {
		getline(cin, buf);
		if(buf == "END") break;
		cmd = buf.substr(0, 6);
		if(cmd[0] == 'S') shelve();
		else {
			title = buf.substr(cmd.size()+1);
			if(cmd[0] == 'B') borrow(title);
			else retbook(title);
		}
	}

	return 0;
}
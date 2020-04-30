#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> m;
int toNum(string s, int i) {
	int sum = 0;
	while(isdigit(s[i])) {
		sum = sum*10 + s[i]-'0';
		i++;
	}
	return sum;
}

void count(string s, int cho) {
	//cout << s << " " << cho << endl;
	int base = cho, num1=0, num2=0; 
	s += ' ';
	string tmp = "";
	for(int i=0; i<s.size()-1; ++i) {
		if(isupper(s[i])) tmp.push_back(s[i]);
		if(i == 0 && isdigit(s[i])) {
			int num = toNum(s, i);
			base *= num;
		}
		//case
		if(isupper(s[i]) ) {
			if(islower(s[i+1])) {
				tmp.push_back(s[i+1]);
				i++;
			} 
			if(isupper(s[i+1]) || s[i+1] == ' ' || s[i+1] == '(') {
				m[tmp] += base;
			} else if(isdigit(s[i+1])) {
				m[tmp] += base*toNum(s, i+1);
			}
			tmp = "";
		}
		if(s[i] == '(') {
			num1++;
			int left = i+1;
			for(i++; num2 != num1; ++i) {
				if(s[i] == '(') num1++;
				if(s[i] == ')') num2++;
			}
			i--;
			if(isdigit(s[i+1])) count(s.substr(left, i-left), base*toNum(s, i+1));
			else count(s.substr(left, i-left), base);
		}
	}
}
void handle(string s, int cho) {
	stringstream ss(s);
	string buf;
	while(getline(ss, buf, '+')) {
		count(buf, cho);
	}
}
void printm() {
	for(auto it = m.begin(); it!=m.end(); ++it) {
		cout << it->first << " " << it->second << endl;
	}
	cout << endl;
}

bool istrue() {
	for(auto it = m.begin(); it!=m.end(); ++it) {
		if(it->second != 0) return false;
	}
	return true;
}

int main() {
	int n;
	string s;
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> s;
		int pos;
		for(pos=0; pos<s.size() && s[pos] != '='; ++pos);
		string left = s.substr(0,pos), right = s.substr(pos+1);
		handle(left, 1);
		handle(right, -1);
		//printm();
		printf("%s\n", istrue()?"Y":"N");
		m.clear();
	}
}

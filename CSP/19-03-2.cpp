#include <bits/stdc++.h>
using namespace std;

bool is24(string s){
	stack<char> optr;
	stack<int> opnd;
	for(int i=0; i<s.size(); ++i){
		if(isdigit(s[i])) opnd.push(s[i] - '0');  //字符串的数字转化成整数记得 - '0'
		else {
			if(s[i] == '+') optr.push(s[i]);
			else if(s[i] == '-') {
				int num = (s[++i] - '0')*(-1);
				optr.push('+');
				opnd.push(num); 
			}
			else if(s[i] == 'x'){
				int num = opnd.top() * (s[++i] - '0');  //
				opnd.pop();
				opnd.push(num);
			}
			else if(s[i] == '/'){
				int num = opnd.top() / (s[++i] - '0');
				opnd.pop();
				opnd.push(num);
			}
		}
	}
	while(!optr.empty()){  //
		int a = opnd.top();
		opnd.pop();
		int b = opnd.top();
		opnd.pop();
		opnd.push(a + b);
		optr.pop();
	}
	if(opnd.top() == 24) return true;
	else return false;
}

int main(){
	freopen("in.txt", "r", stdin);
	int n;
	string str;
	scanf("%d", &n);
	for(int i=0; i<n; ++i){
		cin >> str;
		if(is24(str))
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}

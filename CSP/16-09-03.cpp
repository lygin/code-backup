#include <bits/stdc++.h>
using namespace std;

#define OPPONENT 1-player

const int RED = 0;
const int BLACK = 1;

struct status
{
	int life, power;
	status(int l, int p) {life = l; power = p;}
};

vector<status> v[2];

int main() {
	freopen("in.txt", "r", stdin);
	int n, player = RED;
	string action;
	int position, attack, health;
	int attacker, defender;

	v[RED].push_back(status(30, 0));
	v[BLACK].push_back(status(30, 0));

	cin >> n;

	while(n--) {
		cin >> action;
		if(action == "summon") {
			cin >> position >> attack >> health;
			v[player].insert(v[player].begin() + position, status(health, attack));

		}
		else if(action == "attack") {
			cin >> attacker >> defender;
			v[player][attacker].life -= v[OPPONENT][defender].power;
			v[OPPONENT][defender].life -= v[player][attacker].power;

			if(v[player][attacker].life <= 0) 
				v[player].erase(v[player].begin() + attacker);

			if(defender != 0 && v[OPPONENT][defender].life <= 0)
				v[OPPONENT].erase(v[OPPONENT].begin() + defender);
		}
		else if(action == "end") {
			player = OPPONENT;
		}
	}

	if(v[RED][0].life <= 0)
		cout << -1 << endl;
	else if(v[BLACK][0].life <= 0)
		cout << 1 << endl;
	else 
		cout << 0 << endl;

	cout << v[RED][0].life << endl;

	cout << v[RED].size() - 1;
	for(int i=1; i<v[RED].size(); ++i)
	cout << " " << v[RED][i].life;
	cout << endl;

	cout << v[BLACK][0].life << endl;

	cout << v[BLACK].size() - 1;
	for(int i=1; i<v[BLACK].size(); ++i)
	cout << " " << v[BLACK][i].life;
	cout << endl;

	return 0;
}



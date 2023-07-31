#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "color";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
string c[6] = {"Yellow", "Green", "Blue", "Violet", "Red", "Orange"};
unordered_map<string, int> mp;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	for (int i = 0; i < 6; ++i)
		mp[c[i]] = i;
	string s, t;
	cin >> s >> t;
	int x = mp[s], y = mp[t];
	if (x == y) cout << "Same";
	else if ((x + 1) % 6 == y || ((y + 1) % 6 == x)) cout << "Adjacent";
	else if ((x + 2) % 6 == y) cout << c[(x + 1) % 6];
	else if ((y + 2) % 6 == x) cout << c[(y + 1) % 6];
	else if ((x + 3) % 6 == y) cout << "Complementary";
	else cout << "None";
	return 0;
}


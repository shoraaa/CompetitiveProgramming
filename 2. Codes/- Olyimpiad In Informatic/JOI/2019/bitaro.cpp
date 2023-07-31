#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 3000 + 5;
string s[N];
ll cnt[N];
int n, m;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
		cin >> s[i];
	ll res = 0;
	for (int i = 0; i < n; ++i) {
		int orbs = 0;
		for (int j = m-1; ~j; --j)	{
			if (s[i][j] == 'I' && cnt[j])
				res += cnt[j];
			else if (s[i][j] == 'O')
				orbs++;
			else if (s[i][j] == 'J')
				cnt[j] += orbs;
		}
	}
	cout << res;
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 20 + 5;
string s;
char tg[256][256]; 
vector<pair<char, char>> res;
void call(int n, char dich) {
  if (n == -1) return;
  if (s[n] == dich) return call(n-1, dich), void();
  call(n-1, tg[s[n]][dich]);
  res.emplace_back(s[n], dich);
  s[n] = dich;
  call(n-1, dich);
}
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> s;
  tg['A']['B'] = tg['B']['A'] = 'C';
  tg['C']['B'] = tg['B']['C'] = 'A';
  tg['A']['C'] = tg['C']['A'] = 'B';
  call(n-1, 'C');
  cout << res.size() << '\n';
  for (auto& p : res)
    cout << p.first << p.second << '\n';
	return 0;
}


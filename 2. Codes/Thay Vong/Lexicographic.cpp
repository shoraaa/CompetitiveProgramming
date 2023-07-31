#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5, M = 1e9 + 7;
int n; ll L, R;

void add(int& x, int y) {
  x += y; if (x >= M) x -= M; 
}

int nxt[N * 20][11], cnt[N * 20], id = 0;
void add(const string& s, int val) {
  int u = 0;
  for (char c : s) {
    int z = c - '0' + 1; 
    if (!nxt[u][z]) nxt[u][z] = ++id;
     u = nxt[u][z]; add(cnt[u], val);
  }
}

int get(const string& s) {
  int u = 0, res = 0;
  for (char c : s) {
    int z = c - '0' + 1;
    for (int x = 0; x < z; ++x) add(res, cnt[nxt[u][x]]);
    if (!nxt[u][z]) nxt[u][z] = ++id; u = nxt[u][z];
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> L >> R; int res = 1;
  add(string(19, '0'), 1);
  for (ll x = L; x <= R; ++x) {
    string s = to_string(x);
    while (s.size() < 19) s += '/';
    int val = get(s); add(s, val); add(res, val);
  }
  cout << res;
	return 0;
}


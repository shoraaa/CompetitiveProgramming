#include<bits/stdc++.h>
using namespace std;
using ll = long long;

struct S {
  int l, r, c, d;
  S(int l, int r, int c, int d): l(l), r(r), c(c), d(d) {}
  bool operator < (const S& s) const {
    return d > s.d;
  }
};

const int N = 1005, inf = 1e9;
string s, t[N];
int nxtl[51][N], nxtr[51][N];
int dp[51][51][26];
vector<int> adj[26];
int n, k;

#define fi first
#define se second

void cmin(int& x, int y) {
  x = min(x, y);
}

void add(string& s) {
  
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> s >> n;
  for (int i = 0; i < n; ++i) {
    cin >> t[i];
    if (t[i].front() == t[i].back())
      adj[t[i][0] - 'a'].emplace_back(i);
  }

  k = s.size(); s = ' ' + s + ' ';
  int res = inf;
  for (int p = 4; p <= 4; ++p) {
    priority_queue<S> q;
    memset(dp, 0x3f, sizeof(dp));
    for (int i = p; i <= k; ++i) {
      // da an dc [s[p]..s[i])
      for (int j = 0; j < n; ++j) {
        int id = i;
        for (int i = 0; i < t[j].size(); ++i)
          if (t[j][i] == s[id]) id++;
        nxtr[i][j] = id;
      }
    }
    for (int i = p-1; i; --i) {
      // da an dc (s[i]..s[p]]
      for (int j = 0; j < n; ++j) {
        int id = i;
        for (int i = t[j].size() - 1; ~i; --i)
          if (id > 0 && t[j][i] == s[id]) id--;
        nxtl[i][j] = id;
      }
    }
    memset(dp, 0x3f, sizeof(dp));
    for (int j = 0; j < n; ++j) {
      int id1 = 0, id2 = 1 + (t[j][t[j].size() / 2] == s[p-1]);
      for (int i = (t[j].size() + 1) / 2; i < t[j].size(); ++i) {
        if (p + id1 <= k && t[j][i] == s[p + id1]) id1++;
        if (p - id2 >= 1 && t[j][i] == s[p - id2]) id2++;
      }
      cmin(dp[p - id2][p + id1][t[j].back() - 'a'], t[j].size());
      q.emplace(p - id2, p + id1, t[j].back() - 'a', t[j].size());
    }
    
    while (!q.empty()) {
      auto s = q.top(); q.pop();
      int l = s.l, r = s.r, c = s.c, d = s.d;
      if (d != dp[l][r][c]) continue;
      if (l == 0 && r == k) {
        res = min(res, d); 
        break;
      }
      for (int c = 0; c < 26; ++c) if (nxt1)
    }
  }
  if (res == inf) res = -1;
  cout << res;
	return !!0;
}


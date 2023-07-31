#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 205;
const ll inf = (ll)9e18 + 5;

void add(ll& x, ll y) {
  if (x > inf - y) x = inf;
  else x += y;
}

ll mul(ll x, ll y) {
  if (x == 0 || y == 0) return 0;
  if (x > inf / y) return inf;
  return x * y;
}

string s[N];
int n, m, q;
ll dp[N][N], cnt[2][N][N], k;

vector<pair<int, int>> pos[27];

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("ducvodichworldcup.inp", "r"))  
    freopen("ducvodichworldcup.inp", "r", stdin),
    freopen("ducvodichworldcup.out", "w", stdout);
  //freopen("in", "r", stdin);
  int T; cin >> T;
  
  cin >> n >> m >> q;
  for (int i = 0; i < n; ++i) 
    cin >> s[i];
  
  dp[n-1][m-1] = dp[n][m] = 1; pos[0].emplace_back(n, m);
  for (int i = n-1; ~i; --i) for (int j = m-1; ~j; --j) {
    pos[s[i][j] - 'a' + 1].emplace_back(i, j);
    if (i > 0) add(dp[i - 1][j], dp[i][j]);
    if (j > 0) add(dp[i][j - 1], dp[i][j]);
    if (i > 0 && j > 0) add(dp[i - 1][j - 1], dp[i][j]);
  }
  
  while (q--) {
    cin >> k; 
    memset(cnt, 0, sizeof(cnt));

    cnt[0][0][0] = 1;
    string res; ll tot = 0;
    int flag = 0;
    for (int t = 0; t < n + m - 1; ++t) {
      int cur = t&1, nxt = cur^1;
      memset(cnt[nxt], 0, sizeof(cnt[nxt]));
      
      for (int c = 0; c <= 26; ++c) {
        ll tmp = tot; 
        for (auto p : pos[c]) {
          int i, j; tie(i, j) = p; if (!cnt[cur][i][j]) continue;
          add(tot, mul(dp[i][j], cnt[cur][i][j]));
        }
        if (tot >= k) {
          if (!c) { flag = 1; break; }
          res += char(c + 'a' - 1); tot = tmp;
          for (auto& p : pos[c]) {
            int i, j; tie(i, j) = p; if (!cnt[cur][i][j]) continue;
            if (i < n-1) add(cnt[nxt][i+1][j], cnt[cur][i][j]);
            if (j < m-1) add(cnt[nxt][i][j+1], cnt[cur][i][j]);
            if (i < n-1 && j < m-1) add(cnt[nxt][i+1][j+1], cnt[cur][i][j]);
            
            if (i == n-1 && j == m-1) add(cnt[nxt][n][m], cnt[cur][i][j]);
          }
          break;
        }
        if (flag) break;
      }
    }
    cout << res << '\n';
  }
  
	return 0;
}


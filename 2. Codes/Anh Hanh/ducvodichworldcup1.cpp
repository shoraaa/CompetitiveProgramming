#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1005;
const ll inf = 9e18;

void add(ll& x, ll y) {
  if (x >= inf - y) x = inf;
  else x += y;
}

ll mul(ll x, ll y) {
  if (x == 0 || y == 0) return 0;
  if (x >= inf / y) return inf;
  return x * y;
}

string s[N];
int n, m, q;
ll dp[N][N], cnt[N][N], k;

vector<pair<int, int>> cur[26], nxt[26], pos[26][N * 2];

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
  
  dp[n-1][m-1] = 1;
  for (int i = n-1; ~i; --i) for (int j = m-1; ~j; --j) {
    pos[s[i][j] - 'a'][i + j].emplace_back(i, j);
    if (i > 0) add(dp[i - 1][j], dp[i][j]);
    if (j > 0) add(dp[i][j - 1], dp[i][j]);
  }
  
  while (q--) {
    cin >> k; 
    memset(cnt, 0, sizeof(cnt));

    if (n > 1) cnt[1][0] = 1;
    if (m > 1) cnt[0][1] = 1;
    string res; res += s[0][0]; ll pre = 0;
    
    for (int t = 1; t < n + m - 1; ++t) {
      ll tot = pre; 
      for (int c = 0; c < 26; ++c) {
        ll tmp = tot; 
        for (auto p : pos[c][t]) {
          int i, j; tie(i, j) = p; 
          add(tot, mul(dp[i][j], cnt[i][j]));
        }
        if (tot >= k) {
          res += char(c + 'a'); tot = tmp;
          for (auto& p : pos[c][t]) {
            int i, j; tie(i, j) = p;
            if (i < n-1) add(cnt[i+1][j], cnt[i][j]);
            if (j < m-1) add(cnt[i][j+1], cnt[i][j]);
          }
          break;
        }
        pre = tot;
        
      }
    }
    cout << res << '\n';
  }
  
	return 0;
}


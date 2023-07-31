#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 5;
const ll inf = 1e18;
int a[N];
vector<int> b[N];
int n, k, q;

int cnt[N]; int tot = 0;
void insert(int x) {
  if (!cnt[x]) tot++; cnt[x]++;
}
void erase(int x) {
  cnt[x]--; if (!cnt[x]) tot--;
}
#define fi first
#define se second
ll dp[N];
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("guard.inp", "r"))
    freopen("guard.inp", "r", stdin),
    freopen("guard.out", "w", stdout);
  int omg, T; 
  cin >> omg >> T;
  while (T--) {
    cin >> n >> k >> q;
    for (int i = 1; i <= q; ++i)
      cin >> a[i];
    for (int i = 1, sz; i <= q; ++i) {
      cin >> sz; b[i].resize(sz);
      for (int& x : b[i]) cin >> x;
    }
    // dp[i-1] update cho [i, j] voi j la vi tri lon nhat ma Union(i->j) <= k
    for (int i = 0; i <= q; ++i) dp[i] = inf;
    for (int i = 0; i <= n; ++i) cnt[i] = 0;
    dp[0] = 0; tot = 0; a[1] = 0;
    
    deque<pair<int, ll>> cur; b[q + 1].clear();
    for (int i = 1, j = 0; i <= q; ++i) {
      while (!cur.empty() && cur.front().fi == i) cur.pop_front();
      
      while (j <= q && tot <= k) {
        j++; for (int x : b[j]) insert(x);
      }
      while (!cur.empty() && cur.back().se > dp[i - 1] + a[i]) cur.pop_back();
      cur.emplace_back(j, dp[i - 1] + a[i]);
      
      dp[i] = cur.front().se;
      for (int x : b[i]) erase(x);
    }
    cout << dp[q] << ' ';
  }
	return 0;
}


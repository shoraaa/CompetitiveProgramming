#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 5;
const int INF = 1e9;

int vis[N][2]; pair<int, int> ans[N];
set<pair<ll, pair<int, int>>> cdt;

#define fi first
#define se second

set<int> cur;

int n, m;

ll sqr(ll x) { return x * x; }

void update(int l, int r, int m, int k) {
  for (int i = 0; i < 2; ++i) {
    ll delta = min(sqr(r - m) + (r != +INF && !vis[r][i]), 
                   sqr(m - l) + (l != -INF && !vis[l][i]));      
    if (k == 1) cdt.insert({-delta, {m, i}});
    else cdt.erase({-delta, {m, i}});
  }
}

void update(int l, int r, int k) {
  int m = max(1, min(n, (l + r) >> 1));
  if (m + 1 <= min(r, n)) update(l, r, m + 1, k);
  if (m - 1 >= max(l, 1)) update(l, r, m - 1, k);
  update(l, r, m, k);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  cur.insert(-INF), cur.insert(INF);
  update(-INF, INF, 1);
  for (int i = 0, x; i < m; ++i) {
    char ch; cin >> ch;
    if (ch == 'E') {
      auto p = cdt.begin()->se;
      auto it = cur.lower_bound(p.fi);
      
      update(*prev(it), *it, -1);
      if (*it == p.fi) update(*it, *next(it), -1);

      ans[i] = p, vis[p.fi][p.se] = 1;
      cur.insert(p.fi); it = cur.find(p.fi);
      cout << p.fi << ' ' << p.se+1 << '\n';
      
      update(*prev(it), *it, 1);
      update(*it, *next(it), 1);
    } else {
      cin >> x, x--;
      auto p = ans[x]; 
      auto it = cur.lower_bound(p.fi);
      
      update(*prev(it), *it, -1);
      update(*it, *next(it), -1);
      
      vis[p.fi][p.se] = 0;
      
      if (!vis[p.fi][p.se^1]) {
        update(*prev(it), *next(it), 1);
        cur.erase(p.fi); 
      } else {
        update(*prev(it), *it, 1);
        update(*it, *next(it), 1);
      }
    }
  }
	return 0;
}


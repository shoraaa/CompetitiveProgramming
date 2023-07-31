#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const ll inf = 1e18;
void add(ll& x, ll y) {
  if (x > inf - y) x = inf;
  else x += y;
}

const int N = 5e5 + 5;
int p[N], L[N], R[N], A[N], lo[N], hi[N], ans[N];
vector<int> adj[N], check[N];
int n, m, k;

ll bit[N];
void update(int i, int x) {
  for (; i <= m; i += i & -i)
    add(bit[i], x);
}
ll get(int i) {
  ll res = 0;
  for (; i; i -= i & -i)
    add(res, bit[i]);
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 1, j; i <= m; ++i)
    cin >> j, adj[j].emplace_back(i);
  for (int i = 1; i <= n; ++i)
    cin >> p[i];
    
  cin >> k;
  for (int i = 1; i <= k; ++i)
    cin >> L[i] >> R[i] >> A[i];
  
  for (int i = 1; i <= n; ++i)
    lo[i] = 1, hi[i] = k, ans[i] = -1;
  
  for (;;) {
    int flag = 0;
    for (int i = 1; i <= n; ++i) 
      if (lo[i] <= hi[i]) check[lo[i] + hi[i] >> 1].emplace_back(i), flag = 1;
    if (!flag) break;
    
    for (int i = 1; i <= m; ++i) bit[i] = 0;
    for (int i = 1; i <= k; ++i) {
      if (L[i] <= R[i]) update(L[i], A[i]), update(R[i] + 1, -A[i]);
      else update(1, A[i]), update(R[i] + 1, -A[i]), update(L[i], A[i]);
      
      while (!check[i].empty()) {
        int j = check[i].back(); check[i].pop_back();
        ll cur = 0;
        for (int k : adj[j]) add(cur, get(k));
        if (cur >= p[j]) ans[j] = i, hi[j] = i - 1;
        else lo[j] = i + 1;
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (ans[i] == -1) cout << "NIE\n";
    else cout << ans[i] << '\n';
  }
  
	return 0;
}


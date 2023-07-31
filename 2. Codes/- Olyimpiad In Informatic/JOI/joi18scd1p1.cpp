#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
vector<int> adj[N];
int a[N], c[N];
int n;
int siz[N], par[N], dep[N];
int size(int u) {
  siz[u] = 1;
  for (int& v : adj[u]) {
    adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
    par[v] = u, dep[v] = dep[u] + 1;
    siz[u] += size(v);
    if (siz[v] > siz[adj[u][0]])
      swap(v, adj[u][0]);
  }
  return siz[u];
}

int nxt[N];
void hld(int u) {
  for (int v : adj[u]) {
    nxt[v] = v == adj[u][0] ? nxt[u] : v;
    hld(v);
  }
}
int m;
int bit[N];
int cnt(int i) {
  int res = 0;
  for (; i; i -= i & -i)
    res += bit[i];
  return res;
}

void add(int i, int x) {
  for (; i <= m; i += i & -i)
    bit[i] += x;
}

#define Tp pair<int, int>
#define fi first
#define se second
deque<Tp> seq[N];

ll get(int u) {
  vector<Tp> cur;
  for (int v = u; ~v; v = par[nxt[v]]) {
    int len = dep[v] - dep[nxt[v]] + 1;
    vector<Tp> tmp;
    for (auto& p : seq[nxt[v]]) {
      if (len >= p.se)
        len -= p.se, tmp.emplace_back(p);
      else {
        tmp.emplace_back(p);
        tmp.back().se = len; break;
      }
    }
    reverse(tmp.begin(), tmp.end());
    for (auto& p : tmp) cur.emplace_back(p);
  }
  ll res = 0;
  for (auto& p : cur) 
    res += p.se * cnt(p.fi - 1), add(p.fi, p.se);
  for (auto& p : cur) add(p.fi, -p.se);
  return res;
}

void update(int u) {
  for (int v = u; ~v; v = par[nxt[v]]) {
    int len = dep[v] - dep[nxt[v]] + 1;
    while (!seq[nxt[v]].empty()) {
      if (len >= seq[nxt[v]].front().se)
        len -= seq[nxt[v]].front().se, seq[nxt[v]].pop_front();
      else {
        seq[nxt[v]].front().se -= len; break;
      }
    }
    seq[nxt[v]].emplace_front(a[u], dep[v] - dep[nxt[v]] + 1);
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i], c[i] = a[i];
  sort(c, c + n); m = unique(c, c + n) - c;
  for (int i = 0; i < n; ++i)
    a[i] = lower_bound(c, c + m, a[i]) - c + 1;
  vector<pair<int, int>> edges;
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u),
    edges.emplace_back(u, v);
  par[0] = -1, size(0), hld(0);
  update(0);
  for (int i = 0, u, v; i < n-1; ++i) {
    tie(u, v) = edges[i];
    cout << get(u) << '\n';
    update(v);
  }
	return 0;
}


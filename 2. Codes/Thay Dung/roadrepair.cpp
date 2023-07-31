#include<bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge {
  int u, v, d, w;
  Edge(int u, int v, int d, int w): u(u), v(v), d(d), w(w) {}
  bool operator < (const Edge& e) const {
    return w < e.w;
  }
};

const int N = 2e4 + 6;
ll C1, C2, cnt, cur = 0, res = 9e18;

vector<Edge> e;
vector<int> c1, c2, e1[N], e2[N];
int n, m;

int lin[N], siz[N];
int find(int u) {
  if (u == lin[u]) return u;
  return find(lin[u]);
}
#define fi first
#define se second

int unite(int i, stack<tuple<int, int, int>>& st) {
  int u = find(e[i].u), v = find(e[i].v);
  
  if (u == v) return 0;
  
  if (siz[u] < siz[v]) swap(u, v);
  st.emplace(v, lin[v], i);
  lin[v] = u, siz[u] += siz[v];
  return 1;
} 

void rollback(stack<tuple<int, int, int>>& st) {
  while (!st.empty()) {
    auto p = st.top(); st.pop(); 
    int v, par, id; tie(v, par, id) = p;
    siz[lin[v]] -= siz[v], lin[par] = v, cnt++;
  }
}

int vis_a[N], vis_b[N];
void solve(int l, int r, int x, int y) {
  if (l > r) return;
  int m1 = (l + r) >> 1, m2 = x;
  stack<tuple<int, int, int>> st1, st2;
  
  for (int i = l; i <= m1; ++i) {
    for (int id : e1[i]) {
      if (vis_b[id] && unite(id, st1)) cnt--;
      vis_a[id] = 1; 
    }
  }
  
  while (m2 < y) {
    if (cnt == 1) break;
    for (int id : e2[m2]) {
      if (vis_a[id] && unite(id, st2)) cnt--;
      vis_b[id] = 1;
    }
    m2++;
  }

  if (cnt == 1) res = min(res, C1 * c1[m1] + C2 * c2[m2 - 1]);
  
  for (int i = x; i < m2; ++i) 
    for (int id : e2[i]) vis_b[id] = 0;
  rollback(st2);
  
  solve(m1 + 1, r, x, m2);

  for (int i = l; i <= m1; ++i) 
    for (int id : e1[i]) vis_a[id] = 0;
  rollback(st1);
  for (int i = x; i < m2; ++i) {
    for (int id : e2[i]) {
      if (vis_a[id] && unite(id, st2)) cnt--;
      vis_b[id] = 1;
    }
  }
  
  solve(l, m1 - 1, m2, y);
  
  for (int i = x; i < m2; ++i) 
    for (int id : e2[i]) vis_b[id] = 0;
 rollback(st2);
  
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> C1 >> C2; 
  for (int i = 0, u, v, d, w; i < m; ++i)
    cin >> u >> v >> d >> w, u--, v--,
    e.emplace_back(u, v, d, w),
    c1.emplace_back(d), c2.emplace_back(w);
  sort(c1.begin(), c1.end());
  sort(c2.begin(), c2.end());
  c1.erase(unique(c1.begin(), c1.end()), c1.end());
  c2.erase(unique(c2.begin(), c2.end()), c2.end());
  
  for (int i = 0; i < m; ++i) {
    auto ed = e[i];
    int u = ed.u, v = ed.v, d = ed.d, w = ed.w; 
    e1[lower_bound(c1.begin(), c1.end(), d) - c1.begin()].emplace_back(i);
    e2[lower_bound(c2.begin(), c2.end(), w) - c2.begin()].emplace_back(i);
  }
  for (int i = 0; i < c1.size(); ++i) {
    sort(e1[i].begin(), e1[i].end(), [&](int i, int j) {
      return e[i].d < e[j].d;
    });
    sort(e2[i].begin(), e2[i].end(), [&](int i, int j) {
      return e[i].w < e[j].w;
    });
  }

  cnt = n;
  for (int i = 0; i < n; ++i) lin[i] = i, siz[i] = 1;
  solve(0, c1.size() - 1, 0, c2.size());
  cout << (res == 9e18 ? -1 : res);
	return 0;
}


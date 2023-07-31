#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5, M = 2e5 + 5, inf = 2e9;
#define int ll

#define fi first
#define se second

struct ConvexHull {
  deque<pair<int, int>> dq;
  int eval(pair<int, int>& l, int x) {
    return l.fi * x + l.se;
  }
  int better(const pair<int, int>& L, pair<int, int>& L1, pair<int, int>& L2) {
    return (L2.se - L.se) * (L1.fi - L2.fi) >= (L2.se - L1.se) * (L.fi - L2.fi);
  }
  void add(int a, int b) {
    while (dq.size() >= 2 && better({a, b}, dq[dq.size() - 2], dq[dq.size() - 1])) dq.pop_back();
    dq.emplace_back(a, b);
  }
  int get(int x) {
    while (dq.size() >= 2 && eval(dq[0], x) > eval(dq[1], x)) dq.pop_front();
    return eval(dq[0], x);
  }
} cvh[N];


struct Edge {
  int u, v, x, y, dp;
} a[M];
int n, m, A, B, C;

vector<int> add[N];

signed main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> A >> B >> C;
  for (int i = 0; i < m; ++i)
    cin >> a[i].u >> a[i].v >> a[i].x >> a[i].y,
    a[i].u--, a[i].v--;
    
  sort(a, a + m, [](Edge& u, Edge& v) {
    return u.x < v.x;
  });
  int res = inf;
  cvh[0].add(0, 0);
  for (int i = 0, t = 0; i < m; ++i) {
    int u = a[i].u, v = a[i].v;
    
    while (t <= a[i].x) {
      for (int j : add[t]) 
        cvh[a[j].v].add(-2 * A * a[j].y, A * a[j].y * a[j].y - B * a[j].y + a[j].dp);
      t++;
    }

    if (!cvh[u].dq.empty()) {
      a[i].dp = cvh[u].get(a[i].x) + A * a[i].x * a[i].x + B * a[i].x + C;
      add[a[i].y].emplace_back(i);
      if (v == n - 1) 
        res = min(res, a[i].dp + a[i].y);
    }
  }
  cout << res;
	return 0;
}

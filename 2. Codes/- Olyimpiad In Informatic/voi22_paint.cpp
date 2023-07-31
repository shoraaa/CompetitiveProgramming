#include<bits/stdc++.h>
using namespace std;
using ll = long long;

ll W, H;
int n, m, q;

struct Point {
  ll x, y;
  Point(ll x, ll y): x(x), y(y) {}
  
  friend Point operator - (Point a, const Point& b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
  }
};

ll cross(const Point& a, const Point& b) {
  return a.x * b.y - a.y * b.x;
}

ll orient(const Point& a, const Point& b, const Point& c) {
  ll val = cross(b - a, c - a);
  if (val == 0) return 0;
  if (val > 0) return 1;
  return -1;
}

ll doubled_area(const vector<Point>& a) {
  ll res = 0;
  for (int i = 0; i < a.size(); ++i) {
    auto p = i ? a[i - 1] : a.back(), q = a[i];
    res += (p.x - q.x) * (p.y + q.y);
  }
  return abs(res);
}

struct Polygon {
  vector<Point> a;
  ll area;
  void calc() {
    area = abs(doubled_area(a));
  }
  
  int inside(const Point& z) {
    ll sgn = orient(z, a[0], a.back());
    for (int i = 1; i < a.size(); ++i) {
      if (orient(z, a[i], a[i - 1]) != sgn) {
        return 0;
      } 
    }
    return 1;
  }
  
  bool operator < (const Polygon& p) const {
    return area < p.area;
  }
  
  
  
} a[2005];

void task1() {
  
  ll total = W * H * 2;
  
  for (int i = 1; i <= n; ++i) {
    
    for (int j = 0, x, y; j < m; ++j) {
      cin >> x >> y;
      a[i].a.emplace_back(x, y);
    }
    a[i].calc();
    
  }
  
  sort(a + 1, a + n + 1);
  
  for (int i = n; i; --i) {
    
    int par = -1;
    for (int j = i + 1; j <= n; ++j) {
      
      if (a[j].inside(a[i].a[0])) {
        par = j;
        break;
      }
      
    }
    
    if (par != -1) {
      a[par].area -= a[i].area;
    } else {
      total -= a[i].area;
    }
  }
  
  
  for (int i = 1, x, y; i <= q; ++i) {
    cin >> x >> y;
    
    ll res = total;
    Point p(x, y);
    
    for (int j = n; j; --j) {
      if (a[j].inside(p)) {
        res = a[j].area;
      } 
    }
    
    cout << fixed << setprecision(1) << res / 2.0 << '\n';
  }
  
  
}

const int INF = 1e9;
const int N = 1e5 + 5;

#define fi first
#define se second

struct Node {
  int l, r, par;
  ll area;
  
  bool operator < (const Node& r) const {
    return area < r.area;
  }
} node[N];

vector<int> adj[N];

void add_edge(int u, int v) {
  adj[u].emplace_back(v);
  node[v].par = u;
}

int x_val[N];
ll ans[N];
vector<pair<int, int>> seg;

void dfs(int u, int p = -1) {
  
  for (int v : adj[u]) {
    node[u].area -= node[v].area;
    dfs(v);
  }

  
}

void task2() {
  
  node[0].r = W;
  node[0].area = W * H;
  
  
  for (int i = 1; i <= n; ++i) {
    int l, r, d, t;
    l = d = INF, r = t = -INF;
    for (int i = 1, x, y; i <= m; ++i) {
      cin >> x >> y;
      l = min(l, x); r = max(r, x);
      d = min(d, y); t = max(t, y);
    }

    node[i].l = l; node[i].r = r;
    node[i].area = 1LL * (r - l) * (t - d);
    
    seg.emplace_back(d, i);
    seg.emplace_back(t + 1, -i);
    
  } 
  
  
  for (int i = 1, x, y; i <= q; ++i) {
    cin >> x >> y;
    x_val[i] = x;
    seg.emplace_back(y, n + i);
    
  }
  
  sort(seg.begin(), seg.end());
  
  set<pair<int, int>> s;
  s.emplace(W, 0);

  for (int i = 0; i < seg.size();) {
    
    int j = i;
    while (j < seg.size() && seg[j].fi == seg[i].fi) {
      
      int k = seg[j].se;
      
      if (k < 0) {
        // erase 
        k = -k;
        s.erase({node[k].l, k});
        s.erase({node[k].r, k});
      } else if (k <= n) {
        // insert
        int p = s.upper_bound({node[k].r, INF})->se;
        if (node[p].l > node[k].l) p = node[p].par; 
  
        add_edge(p, k);
  
        s.emplace(node[k].l, k);
        s.emplace(node[k].r, k);
        
      } else {
        
        k -= n;
        
        int p = s.upper_bound({x_val[k], INF})->se;
        if (node[p].l > x_val[k]) p = node[p].par; 
        
        ans[k] = p;
        
      }
      
      j++;
    }
    
    i = j;
    
  }
  
  dfs(0);
  
  for (int i = 1; i <= q; ++i) {
    cout << node[ans[i]].area << ".0\n";
  }
  
  
  
  
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("paint.inp", "r")) {
    freopen("paint.inp", "r", stdin);
    freopen("paint.out", "w", stdout);
  }
  
  cin >> W >> H >> n >> m >> q;
  
  if (n <= 2000 && q <= 2000) {
    task1(); 
  } else if (m == 4) {
    task2();
  } else {
    assert(0);
  }
  
	return 0;
}

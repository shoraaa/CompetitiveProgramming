#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using T = long double;
const ll inf = numeric_limits<ll>::max();

struct pt {
  ll x, y;
  pt operator + (const pt & p) const {
      return pt{x + p.x, y + p.y};
  }
  pt operator - (const pt & p) const {
    return pt{x - p.x, y - p.y};
  }
  ll cross(const pt & p) const {
    return x * p.y - y * p.x;
  }
};

const int N = 205;
vector<pt> a[N];
ll adj[N][N], dis[N];
int n, s, t;
int vis[N];

ll sqr(ll x) { return x * x; }
T originDistance(pt& p, pt& q) {
  ll a2 = sqr(p.x - q.x) + sqr(p.y - q.y);
  ll b2 = sqr(q.x) + sqr(q.y);
  ll c2 = sqr(p.x) + sqr(p.y);
  if (b2 > a2 + c2 || c2 > a2 + b2)
    return min(sqrt(b2), sqrt(c2));
  T s2 = abs(p.x * q.y - q.x * p.y);
  return s2 / sqrt(a2);
}


void reorder_polygon(vector<pt> & P){
  size_t pos = 0;
  for(size_t i = 1; i < P.size(); i++){
    if(P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x))
      pos = i;
  }
  rotate(P.begin(), P.begin() + pos, P.end());
}

vector<pt> minkowski(vector<pt> P, vector<pt> Q){
  for (auto& p : Q) p.x = -p.x, p.y = -p.y;
    // the first vertex must be the lowest
  reorder_polygon(P);
  reorder_polygon(Q);
  // we must ensure cyclic indexing
  P.push_back(P[0]);
  P.push_back(P[1]);
  Q.push_back(Q[0]);
  Q.push_back(Q[1]);
  // main part
  vector<pt> result;
  size_t i = 0, j = 0;
  while(i < P.size() - 2 || j < Q.size() - 2){
    result.push_back(P[i] + Q[j]);
    auto cross = (P[i + 1] - P[i]).cross(Q[j + 1] - Q[j]);
    if(cross >= 0) ++i;
    if(cross <= 0) ++j;
  }
  return result;
}

ll polygon_distance(vector<pt>& p, vector<pt>& q) {
  vector<pt> m = minkowski(p, q);
  T d = numeric_limits<T>::max();
  for (int i = 0; i < m.size(); ++i) 
    d = min(d, originDistance(m[i], m[(i + 1) % int(m.size())]));
  return ll(1e6 * (d));
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> s >> t; s--, t--;
	for (int i = 0, k; i < n; ++i) {
	  cin >> k, a[i].resize(k);
	  for (auto& p : a[i]) cin >> p.x >> p.y;
	}
	
	for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) 
	  adj[i][j] = adj[j][i] = polygon_distance(a[i], a[j]);
	for (int i = 0; i < n; ++i) dis[i] = 1e18;
	dis[s] = 0;
  for (int i = 0; i < n; i++) {
    int u = -1;
    for (int j = 0; j < n; j++) if (!vis[j] && (u == -1 || dis[j] < dis[u])) u = j;
    if (dis[u] == inf) break;
    vis[u] = 1;
    for (int v = 0; v < n; ++v) if (u != v) {
      if (dis[u] + adj[u][v] < dis[v])
        dis[v] = dis[u] + adj[v][u];
    }
  }
  
  cout << dis[t];
 	return 0;	
}

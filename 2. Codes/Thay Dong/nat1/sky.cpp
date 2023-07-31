#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5e4 + 5, S = 100;
vector<int> adj[N];
int n, m;
vector<int> dog[N];

int dis[N][S + 5], b[N], p[N];

struct State {
  int u, l, d;
  State(int u, int l, int d): u(u), l(l), d(d) {}
  bool operator < (const State& s) const {
    return d > s.d;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;

  for (int i = 0, x; i < m; ++i) 
    cin >> b[i] >> p[i], dog[b[i]].emplace_back(p[i]);
    
  priority_queue<State> q;
  memset(dis, 0x3f, sizeof(dis));
  
  if (p[0] <= S) q.emplace(b[0], p[0], 0), dis[b[0]][p[0]] = 0;
  else {
    for (int i = 0; b[0] + i * p[0] < n; ++i) 
      q.emplace(b[0] + i * p[0], S + 1, i), dis[b[0] + i * p[0]][S + 1] = i;
    for (int i = 1; b[0] - i * p[0] >= 0; ++i)
      q.emplace(b[0] - i * p[0], S + 1, i), dis[b[0] - i * p[0]][S + 1] = i;
   }
  
  while (!q.empty()) {
    auto s = q.top(); q.pop();
    if (s.d != dis[s.u][s.l]) continue;
    if (s.u == b[1]) return cout << s.d, 0;
    if (s.l == S + 1) {
      for (int d : dog[s.u]) {
        if (d <= S) {
          if (s.d < dis[s.u][d]) dis[s.u][d] = s.d, q.emplace(s.u, d, s.d);
        } else {
          for (int i = 1; s.u + i * d < n; ++i) if (s.d + i < dis[s.u + i * d][s.l])
            q.emplace(s.u + i * d, s.l, s.d + i), dis[s.u + i*d][s.l] = s.d + i;
          for (int i = 1; s.u - i * d >= 0; ++i) if (s.d + i < dis[s.u - i * d][s.l]) 
            q.emplace(s.u - i * d, s.l, s.d + i), dis[s.u - i*d][s.l] = s.d + i;
        }
      }
    } else {
      if (s.d < dis[s.u][S + 1]) 
        dis[s.u][S+1] = s.d, q.emplace(s.u, S+1, s.d);  
      if (s.u + s.l < n && s.d + 1 < dis[s.u + s.l][s.l])
        dis[s.u + s.l][s.l] = s.d + 1,
        q.emplace(s.u + s.l, s.l, s.d + 1);
      if (s.u - s.l >= 0 && s.d + 1 < dis[s.u - s.l][s.l])
        dis[s.u - s.l][s.l] = s.d + 1,
        q.emplace(s.u - s.l, s.l, s.d + 1);
    }
  }
  cout << -1;
	return 0;
}


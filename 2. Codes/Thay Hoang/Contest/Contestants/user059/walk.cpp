#include<bits/stdc++.h>
using namespace std;

#define taskname "walk"

const long long inf = 1e17;
const int mod = 1e9 + 7;

template<class U, class V>
bool maxz(U &a, V b) {
  if (a < b) {
    return a = b, 1;
  }
  return 0;
}

int main() {
  if (fopen(taskname".inp", "r")) {
    freopen(taskname".inp", "r", stdin);
    freopen(taskname".out", "w", stdout);
  }
  
  cin.tie(0)->sync_with_stdio(0);
  
  int n, m; cin >> n >> m;
  vector<vector<int>> adj(n);
  m <<= 1;
  vector<pair<int, int>> es(m);
  for (int i = 0; i < m; i += 2) {
    int x, y, w;
    cin >> x >> y >> w;
    x--; y--;
    
    es[i] = {y, w};
    es[i ^ 1] = {x, w};
    adj[x].push_back(i);
    adj[y].push_back(i ^ 1);
  }
  
  priority_queue<tuple<long long, int>> pq;
  vector<long long> dst(n, inf);
  vector<int> par(n, -1);
  vector<bool> used(m, 0);
  pq.push({-(dst[0] = 0), 0});
  while (!pq.empty()) {
    long long cdst; 
    int u;
    tie(cdst, u) = pq.top(); pq.pop();
    cdst *= -1;
    
    if (cdst != dst[u]) {
      continue;
    }
    
    for (auto &ei: adj[u]) {
      if (dst[es[ei].first] > cdst + es[ei].second) {
        pq.push({-(dst[es[ei].first] = cdst + es[ei].second), es[ei].first});
        par[es[ei].first] = ei;
      }
    }
  }
  
  if (dst[n - 1] == inf) {
    cout << "-1\n"; return 0;
  }
  int x = n - 1;
  while (x) {
    auto &ei = par[x];
    used[ei] = 1;
    //cout << ei << " ";
    es[ei ^ 1].second *= -1;
    x = es[ei ^ 1].first;
  }
  
  queue<int> q;
  dst.assign(n, inf);
  par.assign(n, -1);
  dst[0] = 0;
  vector<bool> inQ(n);
  inQ[0] = 1;
  q.push(0);
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    inQ[u] = 0;
    for (auto &ei: adj[u]) {
      if (!used[ei] && dst[es[ei].first] > dst[u] + es[ei].second) {
        //cout << ei << " " << used[ei] << "\n";
        dst[es[ei].first] = dst[u] + es[ei].second;
        par[es[ei].first] = ei;
        if (!inQ[es[ei].first]) {
          inQ[es[ei].first] = 1;
          q.push(es[ei].first); 
        }
      }
    }
  }
  
  
  if (dst[n - 1] == inf) {
    cout << "-1\n"; return 0;
  }
  
  x = n - 1;
  while (x) {
    auto &ei = par[x];
    used[ei] = 1;
    x = es[ei ^ 1].first;
  }
  
  for (int i = 0; i < m; i += 2) {
    if (!used[i] && !used[i ^ 1]) {
      used[i] = used[i ^ 1] = 1;
    }
  }
  
  long long Res = 0;
  vector<vector<int>> res;
  function<void(int)> dfs = [&](int u) {
    res.back().push_back(u);
    if (!u) {
      return ;
    }
    for (auto &ei: adj[u]) {
      if (!used[ei]) {
        used[ei] = 1;
        Res += abs(es[ei].second);
        dfs(es[ei].first);
        break;
      }
    }
  };
  
  for (auto &ei: adj[n - 1]) {
    if (!used[ei]) {
      used[ei] = 1;
      res.push_back(vector<int>());
      Res += abs(es[ei].second);
      dfs(es[ei].first);
      if (res.size() == 2) {
        break;
      }
    }
  }
  
  swap(res[0], res[1]);
  reverse(res[0].begin(), res[0].end());
  res[0].push_back(n - 1);
  cout << Res << endl;
  for (int j = 0; j < res.size(); j++) {
    for (int i = 0; i < res[j].size(); i++) {
      cout << 1 + res[j][i] << (j && i == res[j].size() - 1 ? "": " ");
    }
  }
  
  return 0;
}
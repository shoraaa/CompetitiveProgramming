#include <bits/stdc++.h>

// #define Submit

#ifdef Submit
#include "swap.h"
#endif

using namespace std;
using ll = long long;

const int N = 3e5 + 5;

struct Edge {
  int u, v, w;
  Edge(int u = 0, int v = 0, int w = 0): u(u), v(v), w(w) {}
  bool operator < (const Edge& e) const {
    return w < e.w;
  }
} ed[N];

int n, m;

int lin[N], deg[N], ok[N], val[N];

int find(int i) {
  if (i == lin[i]) {
    return i;
  }
  return lin[i] = find(lin[i]);
}

vector<int> adj[N];

int unite(int u, int v, int w) {
  u = find(u); v = find(v);
  
  n++;
  lin[u] = lin[v] = lin[n] = n;
  val[n] = w;
  
  adj[n].emplace_back(u);
  ok[n] |= ok[u];

  if (u != v) {
    adj[n].emplace_back(v);
    ok[n] |= ok[v];
  } else {
    ok[n] = 1;
  }
  
  return n;
}

int dep[N], par[N][19];
void dfs(int u) {
  for (int v : adj[u]) {
    dep[v] = dep[u] + 1;
    par[v][0] = u; 
    for (int i = 1; i <= 18; ++i) {
      par[v][i] = par[par[v][i - 1]][i - 1];
    }
    dfs(v);
  }
}

int lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  
  for (int i = 18; ~i; --i) {
    if (dep[par[u][i]] >= dep[v]) {
      u = par[u][i];
    }
  }
  
  if (u == v) {
    return u;
  }
  
  for (int i = 18; ~i; --i) {
    if (par[u][i] != par[v][i]) {
      u = par[u][i]; v = par[v][i];
    }
  }
  
  return par[u][0];
}

void init(int N, int M, std::vector<int> U, std::vector<int> V, std::vector<int> W) {
  n = N; m = M;
  for (int i = 1; i <= m; ++i) {
    int u = U[i - 1] + 1, v = V[i - 1] + 1, w = W[i - 1];
    ed[i] = {u, v, w};
  }
  
  sort(ed + 1, ed + m + 1);
  
  for (int i = 1; i <= n; ++i) {
    lin[i] = i;
  }
  
  for (int i = 1; i <= m; ++i) {
    deg[ed[i].u]++; deg[ed[i].v]++;
    int id = unite(ed[i].u, ed[i].v, ed[i].w);
    ok[id] |= deg[ed[i].u] >= 3 || deg[ed[i].v] >= 3;
  }
  
  int root = find(1);
  dfs(root);
  
}

int getMinimumFuelCapacity(int X, int Y) {
  int u = X + 1, v = Y + 1;

  int z = lca(u, v);
  if (ok[z]) {
    return val[z];
  }
  
  for (int i = 18; ~i; --i) {
    if (par[z][i] && !ok[par[z][i]]) {
      z = par[z][i];
    }
  }
  z = par[z][0];
  
  return ok[z] ? val[z] : -1;
}

#ifndef Submit

int main() {
  int N, M;
  assert(2 == scanf("%d %d", &N, &M));
  
  std::vector<int> U(M), V(M), W(M);
  for (int i = 0; i < M; ++i) {
    scanf("%d", &U[i]);
  }
  for (int i = 0; i < M; ++i) {
    scanf("%d", &V[i]);
  }
  for (int i = 0; i < M; ++i) {
    scanf("%d", &W[i]);
  }

  int Q;
  assert(1 == scanf("%d", &Q));

  std::vector<int> X(Q), Y(Q);
  for (int i = 0; i < Q; ++i) {
    scanf("%d %d ", &X[i], &Y[i]);
  }

  init(N, M, U, V, W);
  
  std::vector<int> minimum_fuel_capacities(Q);
  for (int i = 0; i < Q; ++i) {
    minimum_fuel_capacities[i] = getMinimumFuelCapacity(X[i], Y[i]);
  }

  for (int i = 0; i < Q; ++i) {
    printf("%d\n", minimum_fuel_capacities[i]);
  }
  
  return 0;
}
#endif
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1000,
          MAX_M = 4 * 1000;

const long long INF = 1e15;

struct TEdge {
  int u, v, c, f, w;
};

long long d[MAX_N + 1],
          p[MAX_N + 1];

struct TPQ_Item {
  int u;
  long long d_u;

  bool valid() {
    return d_u == d[u];
  }
};

bool operator < (TPQ_Item a, TPQ_Item b) {
  return a.d_u > b.d_u;
}

bool minimize(long long &target, long long value) {
  if (target <= value)
    return false;

  target = value;
  return true;
}

long long get_wp(TEdge edge) {
  int u = edge.u,
      v = edge.v,
      w = edge.w;

  return w + p[u] - p[v];
}

int get_cf(TEdge edge) {
  return edge.c - edge.f;
}

TEdge edges[MAX_M + 1];

vector <int> adj[MAX_N + 1];

int trace[MAX_N + 1];

void ijk(int s, int t, int n) {
  fill(d + 1, d + n + 1, INF);

  priority_queue <TPQ_Item> pq;

  d[s] = 0;
  pq.push({s, 0});

  while (pq.empty() == false) {
    TPQ_Item item = pq.top();
    pq.pop();

    if (item.valid() == false)
      continue;

    int u = item.u;

    for (int i : adj[u]) {
      int v = edges[i].v;

      if (get_cf(edges[i]) == 0)
        continue;

      if (minimize(d[v], d[u] + get_wp(edges[i])))
        trace[v] = i,
        pq.push({v, d[v]});
    }
  }

  for (int u = 1; u <= n; u++)
    p[u] += d[u];
}

void increase_flow(int s, int t) {
  int v = t;

  while (v != s) {
    int i = trace[v];

    edges[i].f++;
    edges[i ^ 1].f--;

    v = edges[i].u;
  }
}

void add_edge(int &i, int u, int v, int c, int w) {
  adj[u].push_back(i);
  edges[i++] = {u, v, c, 0, w};

  adj[v].push_back(i);
  edges[i++] = {v, u, 0, 0, -w};  
}

int input() {
  int n, m;
  cin >> n >> m;

  int i = 0;

  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;

    add_edge(i, u, v, 1, w);
    add_edge(i, v, u, 1, w);
  }

  return n;
}

void trace_path(vector <int> &path, long long &w, int s, int t) {

  path = {s};
  int u = s;

  while (u != t) 
    for (int i : adj[u]) {
      if (edges[i].f != 1)
        continue;

      edges[i].f = 0;

      path.push_back(edges[i].v);
      w += edges[i].w;

      u = edges[i].v;
      break;
    }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin.tie(0);

  freopen("walk.inp", "r", stdin);
  freopen("walk.out", "w", stdout);

  int n = input();

  int s = 1, t = n;

  for (int path = 1; path <= 2; path++) {
    ijk(s, t, n);
    
    if (d[t] == INF) {
      cout << -1;
      return 0;
    }   

    increase_flow(s, t);
  }

  long long w = 0;
  vector <int> path1, path2;

  trace_path(path1, w, s, t);
  trace_path(path2, w, s, t);

  path2.pop_back();
  reverse(path2.begin(), path2.end());

  cout << w << '\n';

  for (int u : path1)
    cout << u << ' ';

  for (int u : path2)
    cout << u << ' ';
}
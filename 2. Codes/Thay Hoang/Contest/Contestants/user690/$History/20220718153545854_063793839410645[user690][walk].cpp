#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1000,
          MAX_M = 4 * 1000;

const long long INF = 1e15;

struct Edge {
  int u, v, c, f, w;
};


Edge edges[MAX_M + 1];


vector <int> adj[MAX_N + 1];


int trace[MAX_N + 1];
long long dist[MAX_N + 1];
bool in_q[MAX_N + 1];


void spfa(int s, int t, int n) {
  fill(dist + 1, dist + n + 1, INF);
  fill(in_q + 1, in_q + n + 1, false);

  queue <int> q;

  dist[s] = 0;
  in_q[s] = true;
  q.push(s);

  while (q.empty() == false) {
    int u = q.front();
    q.pop();

    if (u == t)
      return;

    for (int id : adj[u]) {
      int v = edges[id].v,
          c = edges[id].c,
          f = edges[id].f,
          w = edges[id].w;

      if (f == c)
        continue;

      if (dist[u] + w >= dist[v])
        continue;

      trace[v] = id;
      dist[v] = dist[u] + w;

      if (in_q[v] == false)
        in_q[v] = true,
        q.push(v);
    }
  }
}

void increase_flow(int s, int t, int n) {
  int v = t;

  while (v != s) {
    int id = trace[v];

    edges[id].f++;
    edges[id ^ 1].f--;

    v = edges[id].u;
  }
}

int input() {
  int n, m;
  cin >> n >> m;

  int id = 0;

  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;

    edges[id++] = {u, v, 1, 0, w};
    edges[id++] = {v, u, 0, 0, -w};

    edges[id++] = {v, u, 1, 0, w};
    edges[id++] = {u, v, 0, 0, -w};
  }

  for (int i = 0; i < id; i++) {
    int u = edges[i].u;
    adj[u].push_back(i);
  }

  return n;
}

vector <int> trace_path(int s, int t, long long &total_w) {
  vector <int> path = {s};

  int u = s;

  while (u != t)
    for (int id : adj[u]) {
      int v = edges[id].v,
          w = edges[id].w;

      if (edges[id].f != 1)
        continue;

      edges[id].f = 0;

      total_w += w;
      path.push_back(v);

      u = v;

      break;
    }

  return path;
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
    spfa(s, t, n);
    
    if (dist[t] == INF) {
      cout << -1;
      return 0;
    }   

    increase_flow(s, t, n);
  }


  long long total_w = 0;

  vector <int> path1 = trace_path(s, t, total_w),
               path2 = trace_path(s, t, total_w);

  path2.pop_back();
  reverse(path2.begin(), path2.end());

  cout << total_w << '\n';

  for (int u : path1)
    cout << u << ' ';

  for (int u : path2)
    cout << u << ' ';
}
#include <bits/stdc++.h>
using namespace std;

#define taskname "dcpp"

const long long inf = 1e15;

struct MinCost {
  const long long inf = 1e15;

  struct Ed {
    int u, v;
    long long flow = 0, cap, cst;
    Ed() {}
    Ed(int u, int v, long long cap, long long cst): u(u), v(v), cap(cap), cst(cst) {}
  };
  int n, m = 0, s, t;
  vector<vector<int>> adj;
  MinCost(int n, int s, int t): n(n), s(s), t(t) {
    adj.resize(n);
  }

  vector<Ed> eds;  
  void add_edge(int u, int v, long long cap, long long cst) {
    eds.push_back(Ed(u, v, cap, cst));
    eds.push_back(Ed(v, u, 0, -cst));
    adj[u].push_back(m);
    adj[v].push_back(m ^ 1);
    m += 2;
  }

  void bellman(vector<long long> &dst, vector<int> &p) {
    dst.assign(n, inf);
    dst[s] = 0;
    p.assign(n, -1);
    vector<bool> inQ(n);
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      inQ[u] = 0;
      for (auto &ei: adj[u]) {
        int v = eds[ei].v;
        if (eds[ei].cap - eds[ei].flow > 0 && dst[v] > dst[u] + eds[ei].cst) {
          dst[v] = dst[u] + eds[ei].cst;
          p[v] = ei;
          if (!inQ[v]) {
            inQ[v] = 1;
            q.push(v);
          }
        }
      }
    }
  }

  long long calc(long long K) {
    long long f = 0, cst = 0;
    vector<long long> dst;
    vector<int> p;
    while (f < K) {
      bellman(dst, p);
      // break;
      if (dst[t] == inf) {
        break;
      }
      long long F = K - f;
      int cr = t;
      while (cr ^ s) {
        F = min(F, eds[p[cr]].cap - eds[p[cr]].flow);
        cr = eds[p[cr]].u;
      }

      f += F;
      cst += dst[t] * F;
      cr = t;
      while (cr ^ s) {
        eds[p[cr]].flow += F;
        eds[p[cr] ^ 1].flow -= F;
        cr = eds[p[cr]].u;
      }
    }
    // cerr << f << "\n";
    if (f < K) return -1;
    return cst;
  }
};

int main() {
  if (fopen(taskname".inp", "r")) {
    freopen(taskname".inp", "r", stdin);
    freopen(taskname".out", "w", stdout);
  }
  
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;
  vector<int> out(n + 1), in(n + 1);
  vector<vector<array<int, 2>>> adj(n + 1);
  vector<array<int, 3>> es(m + 1);
  long long res = 0;
  for (int i = 1; i <= m; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    out[x]++;
    in[y]++;
    res += w;
    es[i] = {x, y, w};
    adj[x].push_back({y, w});
  }

  // vector<vector<long long>> dst(n + 1, vector<long long>(n + 1, inf));
  // for (int i = 1; i <= n; i++) {
  //   dst[i][i] = 0;
  //   priority_queue<pair<long long, int>> pq;
  //   pq.push({0, i});
  //   while (!pq.empty()) {
  //     auto u = pq.top(); pq.pop();
  //     u.first *= -1;
  //     if (dst[i][u.second] ^ u.first) {
  //       continue;
  //     }
  //     for (auto &to: adj[u.second]) {
  //       if (dst[i][to[0]] > u.first + to[1]) {
  //         pq.push({-(dst[i][to[0]] = u.first + to[1]), to[0]});
  //       }
  //     }
  //   }
  // }

  vector<int> c, d;
  MinCost mc(n + 2, 0, n + 1);
  for (int i = 1; i <= n; i++) {
    if (in[i] > out[i]) {
      c.push_back(i);
    }
    else {
      d.push_back(i);
    }
  }

  int M = 0, M2 = 0;
  for (int i = 0; i < c.size(); i++) {
    mc.add_edge(0, c[i], in[c[i]] - out[c[i]], 0);
    M += in[c[i]] - out[c[i]];
  }
  for (int j = 0; j < d.size(); j++) {
    mc.add_edge(d[j], n + 1, out[d[j]] - in[d[j]], 0);
    M2 += out[d[j]] - in[d[j]];
  }
  // assert(M == M2);
  // for (int i = 0; i < c.size(); i++) {
  //   for (int j = 0; j < d.size(); j++) {
  //     mc.add_edge(i + 1, c.size() + j + 1, 1, dst[c[i]][d[j]]);
  //   }
  // }
  for (int i = 1; i <= m; i++) {
    mc.add_edge(es[i][0], es[i][1], 1, es[i][2]);
  }

  cout << res + mc.calc(M) << "\n";

  return 0;
}
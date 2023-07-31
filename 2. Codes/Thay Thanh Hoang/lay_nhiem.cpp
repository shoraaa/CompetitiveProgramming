#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;

struct Edge {
  int u, v;
} ed[N];

int bad[N], par[N];
int n, m;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);

  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> bad[i];
  }
  
  for (int i = 1; i <= m; ++i) {
    cin >> ed[i].u >> ed[i].v;
  }
  
  for (int i = m; i; --i) {
    int u = ed[i].u, v = ed[i].v;
    if (!bad[u]) bad[v] = 0;
    if (!bad[v]) bad[u] = 0;  
  }
  
  for (int i = 1; i <= n; ++i) {
    if (!bad[i]) continue;
    par[i] = i;
  }
  
  for (int i = 1; i <= m; ++i) {
    int u = ed[i].u, v = ed[i].v;
    if (par[u] == par[v]) continue;
    if (par[u] && par[v]) {
      par[u] = par[v] = n + 1;
    } else if (par[u]) {
      par[v] = par[u];
    } else if (par[v]) {
      par[u] = par[v];
    }
  }
  
  set<int> s;
  for (int i = 1; i <= n; ++i) {
    s.insert(par[i]);
  }
  
  for (int i = 1; i <= n; ++i) {
    cout << (!bad[i] || !s.count(i));
  }

	return 0;
}


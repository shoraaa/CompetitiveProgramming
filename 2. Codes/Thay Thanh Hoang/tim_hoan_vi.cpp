#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 3e5 + 5;
int n, m;
map<int, bool> adj[N];
deque<int> dq[N];

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0, u, v; i < m; ++i)
    cin >> u >> v, u--, v--,
    adj[u][v] = adj[v][u] = 1;
    
  dq[1].emplace_back(0);
  int C = 0;
  for (int i = 1; i < n; ++i) {
    int B = C^1;
    if (adj[dq[B].back()][i] != C) {
      dq[B].emplace_back(i);
      if (!dq[C].empty() && adj[dq[C].front()][dq[B].back()] != C)
        dq[B].emplace_back(dq[C].front()), dq[C].pop_front();
    } else {
      if (dq[B].size() == 1) {
        if (dq[C].empty() || adj[dq[C].front()][i] == C) dq[C].emplace_front(i);
        else dq[C].emplace_front(dq[B].back()), dq[B].pop_back(), dq[B].emplace_back(i), C ^= 1;
      } else {
        dq[C].emplace_front(dq[B].back());
        dq[B].pop_back(); 
        if (!dq[B].empty() && adj[dq[B].back()][i] != C) dq[B].emplace_back(i);
        else dq[C].emplace_front(i);
      }
    }
  }
  if (C) swap(dq[0], dq[1]);
  for (int i = 0; i < dq[1].size(); ++i) cout << dq[1][i] + 1 << ' ';
  for (int i = 0; i < dq[0].size(); ++i) cout << dq[0][i] + 1 << ' ';
	return 0;
}


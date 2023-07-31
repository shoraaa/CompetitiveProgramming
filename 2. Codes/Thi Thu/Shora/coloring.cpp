#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 5;
vector<pair<int, int>> adj[N];
int used[N];

int n, m;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("coloring.inp", "r")) {
    freopen("coloring.inp", "r", stdin);
    freopen("coloring.out", "w", stdout);
  }
  
  int T; 
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1, r, c; i <= n; ++i) {
      cin >> r >> c; c += 1 << 10;
      adj[r].emplace_back(c, i);
      adj[c].emplace_back(r, i);
    }
    
    m = 0;
    for (int i = 0; i < 2048; ++i) {
      if (adj[i].size() % 2 == 1) {
        m += 1;
        adj[i].emplace_back(2048, n + m);
        adj[2048].emplace_back(i, n + m);
      }
    }
    
    stack<int> st;
    for (int r = 0; r < 1 << 10; ++r) {
      if (adj[r].empty()) continue;
      
      st.push(r);
      while (!st.empty()) {
        int u = st.top();
        if (adj[u].empty()) {
          st.pop();
          continue;
        }
        
        auto p = adj[u].back();
        adj[u].pop_back();
        
        int v, i; tie(v, i) = p;
        if (used[i]) continue;
        if (u < 1024) used[i] = 1;
        else used[i] = 2;
        st.push(v);
      }

  }
      
    
    for (int i = 1; i <= n; ++i) {
      if (used[i] == 1) cout << 'R';
      else cout << 'B';
    }
    cout << '\n';
    
    for (int i = 1; i <= n + m; ++i) {
      used[i] = 0;
    }
    
    for (int i = 0; i <= 2048; ++i) {
      adj[i].clear();
    }
    
  }
	return 0;
}


#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int INF = 1e9 + 7;
const int R = 16, N = 727;

int hungarian(vector<vector<int>>& A, vector<int>& to) {
  int n = A.size() - 1, m = n;
  vector<int> u(n+1), v(m+1), p(m+1), way(m+1);
  for (int i=1; i<=n; ++i) {
  	p[0] = i;
  	int j0 = 0;
  	vector<int> minv (m+1, INF);
  	vector<char> used (m+1, false);
  	do {
  		used[j0] = true;
  		int i0 = p[j0],  delta = INF,  j1;
  		for (int j=1; j<=m; ++j)
  			if (!used[j]) {
  				int cur = A[i0][j]-u[i0]-v[j];
  				if (cur < minv[j])
  					minv[j] = cur,  way[j] = j0;
  				if (minv[j] < delta)
  					delta = minv[j],  j1 = j;
  			}
  		for (int j=0; j<=m; ++j)
  			if (used[j])
  				u[p[j]] += delta,  v[j] -= delta;
  			else
  				minv[j] -= delta;
  		j0 = j1;
  	} while (p[j0] != 0);
  	do {
  		int j1 = way[j0];
  		p[j0] = p[j1];
  		j0 = j1;
  	} while (j0);
  }
  
  for (int i = 1; i <= m; ++i){
    to[p[i]] = i;
  }
  
  return -v[0];
}

vector<int> adj[N];
int b[R][6 * R];

int p[N], q[N], cur[N], dis[N][N];

vector<int> to;

int n, r, m;

void add(int u, int v) {
  adj[u].emplace_back(v);
  adj[v].emplace_back(u);
}

void dfs(int u, int t) {
  if (u == t) return;
  
  for (int v : adj[u]) {
    if (dis[v][t] >= dis[u][t]) continue;
    if (!cur[v]) {
      cout << u << ' ' << v << '\n';
      
      swap(cur[u], cur[v]);
      dfs(v, t);
      return;
    }
  }
  
  for (int v : adj[u]) {
    if (dis[v][t] >= dis[u][t]) continue;
    
    dfs(v, t);
    swap(cur[u], cur[v]);
    cout << u << ' ' << v << '\n';
    return;
    
  }
  
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  
  int T; cin >> T;
  while (T--) {
  
    cin >> r >> m; 
    n = 1+3*r*(r+1); 
    
    for (int i = 1; i <= n; ++i) {
      adj[i].clear();
    }

    b[0][0] = 1;
    for (int i = 1, j = 2; i <= r; ++i) {
      for (int k = 0; k < 6*i; ++k, ++j) {
        // cin >> a[j]; 
        b[i][k] = j;
      }
      
      int sz = 6*i;
      for (int k = 0; k < sz; ++k) {
        int nv = k+1; if (nv >= sz) nv -= sz;
        add(b[i][k], b[i][nv]);
      }
      
      if (i == 1) {
        for (int u = 0; u < sz; ++u) {
          add(1, b[i][u]);
        }
      } else for (int u = 0, v = 0; u < sz-6; ++u, ++v) {
        for (int l = 0; l < 2; ++l) {
          add(b[i][v+l], b[i-1][u]);
        }
        if (u % (i-1) == (i-2)) {
          int nv = v+2; if (nv >= sz) nv -= sz;
          add(b[i][nv], b[i-1][u]);
          v++;
        }
      }
       
    }
    
    for (int i = 1; i <= m; ++i) {
      cin >> p[i];
    }
    
    for (int i = 1; i <= m; ++i) {
      cin >> q[i];
    }
    
    for (int i = 1; i <= n; ++i) {
      memset(dis[i], -1, sizeof(dis[i]));
      dis[i][i] = 0;
      queue<int> qu; qu.emplace(i);
      
      while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        for (int v : adj[u]) if (dis[i][v] == -1) {
          dis[i][v] = dis[i][u] + 1;
          qu.emplace(v);
        }
      }
    }
    
    vector<vector<int>> mat(m + 1, vector<int>(m + 1));
    
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= m; ++j) {
        mat[i][j] = dis[p[i]][q[j]];
      }
    }
    
    to = vector<int>(m + 1);
    auto res = hungarian(mat, to);
    cout << res << '\n';
    
    for (int i = 1; i <= n; ++i) {
      cur[i] = 0;
    }
    
    for (int i = 1; i <= m; ++i) {
      to[i] = q[to[i]];
      cur[p[i]] = i;
    }
    
    vector<int> vis(m + 1);
    for (int i = 1; i <= m; ++i) {
      if (cur[q[i]]) {
        vis[cur[q[i]]] = 1;
        dfs(q[i], to[cur[q[i]]]);
      }
    }
    
    for (int i = 1; i <= m; ++i) {
      if (!vis[i]) {
        dfs(p[i], to[i]);
      }
    }
    
    
  }
  return 0;
}

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1005;
vector<int> adj[N];
int n, k, L, R;

int siz[N];

ll f[N][N][5], tmp[N][N], ans[N];

void dfs(int u, int p) {
  siz[u] = 1;

  for (int v : adj[u]) if (v != p) {
    dfs(v, u);
  }
  
  f[u][0][0] = 1; // ko chon thang u
  f[u][0][1] = 1; // chon thang u
  
  for (int v : adj[u]) if (v != p) {
    
    // reset mang tmp
    for (int i = 0; i <= siz[u] + siz[v] - 1; ++i) {
      for (int j = 0; j <= k; ++j) {
        tmp[i][j] = 0;
      }
    }
    
    // them cay con goc v vao u
    for (int i = 0; i <= siz[u] - 1; ++i) {
      // chon i canh trong cay con goc u
      for (int j = 0; j <= min(k, siz[u]); ++j) {
        if (!f[u][i][j]) continue;
        // chon k dinh
        
        tmp[i][j] += f[u][i][j];
        
        for (int iv = 0; iv <= siz[v] - 1; ++iv) {
          // chon iv canh trong cay con goc v
          
          for (int jv = 1; jv <= min(k, siz[v]); ++jv) {
            if (!f[v][iv][jv]) continue;
            
            // chon jv dinh trong cay con goc v
            
            tmp[i + iv + 1][j + jv] += f[u][i][j] * f[v][iv][jv];

            
          }
          
          
        }
        
        
        
      }
      
      
    }
    
    siz[u] += siz[v];
    
    // gan lai cho f
    for (int i = 0; i <= siz[u] - 1; ++i) {
      for (int j = 0; j <= min(k, siz[u]); ++j) {
        f[u][i][j] = tmp[i][j];
      }
    }
    
  }
  
  // for (int i = 0; i <= siz[u] - 1; ++i) {
    // for (int j = 0; j <= min(k, siz[u]); ++j) {
      // if (!f[u][i][j]) continue;
      // cerr << i << ' ' << j << ' ' << f[u][i][j] << endl;
    // }
  // }
  
  if (k > siz[u]) return;
  
  for (int i = 1; i <= siz[u] - 1; ++i) {
    if (!f[u][i][k]) continue;
    
    ll cnt = f[u][i][k];
    for (int v : adj[u]) if (v != p) {
      // noi ca k dinh tu thang v len
      cnt -= f[v][i - 1][k];
      
    }
    ans[i] += cnt; 
  }
  
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k >> L >> R;
  for (int i = 1, u, v; i <= n - 1; ++i) {
    cin >> u >> v;
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }
  
  dfs(1, 0);
  
  ll res = 0;
  for (int i = L; i <= R; ++i) {
    res += ans[i];
  }
  cout << res;
  
	return 0;
}

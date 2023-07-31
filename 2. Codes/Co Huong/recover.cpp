#include<bits/stdc++.h>
using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = (1 << 19) + 5;
int a[N], b[N];
int n;

int id, ans[N];
vector<int> adj[N];
void dfs(int u) {
  sort(adj[u].rbegin(), adj[u].rend());
  for (int v : adj[u])
    dfs(v);
  ans[u] = id++;
}

bool solve() {
  for (int i = 1; i <= n + 1; ++i) adj[i].clear();
  stack<int> st; st.push(n + 1);
  for (int i = 1; i <= n; ++i) {
    while (i == st.top()) st.pop();
    if (a[i] == -1) a[i] = st.top();
    if (a[i] > st.top()) return 0;
    adj[a[i]].emplace_back(i), st.push(a[i]);
  }
  id = 1, dfs(n + 1);
  if (id != n + 2) return 0;
  
  st = stack<int>(); st.push(n + 1);
  for (int i = n; i; --i) {
    while (ans[i] > ans[st.top()]) st.pop();
    b[i] = st.top(); st.push(i);
  }
  for (int i = 1; i <= n; ++i) 
    if (a[i] != -1 && a[i] != b[i]) return 0;
  
  return 1;
} 

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("recover.inp", "r")) 
    freopen("recover.inp", "r", stdin),
    freopen("recover.out", "w", stdout);
  int sub, T; cin >> sub >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; ++i)
      cin >> a[i];
    if (!solve()) {
      cout << "No\n";
    } else {
      cout << "Yes\n";
      for (int i = 1; i <= n; ++i)
        cout << ans[i] << ' ';
      cout << '\n';
    }
  }
	return 0;
}


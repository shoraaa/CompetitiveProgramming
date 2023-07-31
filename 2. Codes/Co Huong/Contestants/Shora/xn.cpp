#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e3 + 5;
int comp[N][N];
int n, m, k;


vector<int> res[N]; int id = 0;
vector<int> maximal;
void call(vector<int>& idx) {
  if (idx.empty()) return;
  for (int i : idx) {
    if (maximal.empty()) {
      maximal.emplace_back(i);
    } else {
      int flag = 0;
      for (int j : maximal) if (comp[i][j] < 0) {
        flag = 1; break;
      }
      if (flag == 1) continue;
      vector<int> nxt;
      for (int j : maximal) if (comp[i][j] == 0)
        nxt.emplace_back(j);
      nxt.emplace_back(i);
      maximal.swap(nxt);
    }
  }
  res[id] = maximal; id++;
  for (int i : maximal)
    idx.erase(find(idx.begin(), idx.end(), i));
  maximal.clear();
  call(idx);
}

vector<int> a[N];
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("xn.inp", "r"))
    freopen("xn.inp", "r", stdin),
    freopen("xn.out", "w", stdout);
  cin >> n >> m >> k;
  for (int i = 1; i <= n; ++i) {
    a[i].resize(m);
    for (int j = 0; j < m; ++j)
      cin >> a[i][j];
  }
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      int greater = 1, less = 1;
      for (int k = 0; k < m; ++k)
        greater &= a[i][k] >= a[j][k], 
        less &= a[i][k] <= a[j][k];
      if (greater) comp[i][j] = 1;
      else if (less) comp[i][j] = -1;
    }
  vector<int> idx(n);
  for (int i = 0; i < n; ++i)
    idx[i] = i + 1;
  call(idx);
  if (id > k) 
    return cout << -1, 0;
  for (int i = 0; id < k; ++i) {
    while (id < k && res[i].size() >= 2) {
      int j = res[i].back(); res[i].pop_back();
      res[id] = { j }; id++;
    }
  }
  for (int i = 0; i < id; ++i) {
    for (auto& j : res[i]) 
      cout << j << ' ';
    cout << '\n';
  }
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
int a[N], max_row[N], max_col[N], row[N], col[N];
int n, m, q, size;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	if (fopen("ocell.in", "r"))
	  freopen("ocell.in", "r", stdin),
	  freopen("ocell.out", "w", stdout);
  cin >> n >> m >> q, size = n * m;
  for (int i = 0; i < size; ++i)
    cin >> a[i], 
    max_row[i / m] = max(max_row[i / m], a[i]),
    max_col[i % m] = max(max_col[i % m], a[i]);
  set<int> s;
  memset(row, -1, sizeof(row));
  memset(col, -1, sizeof(col));
  for (int i = 0; i < size; ++i) 
    if (a[i] == max_row[i / m] && a[i] == max_col[i % m])
      row[i / m] = col[i % m] = i, s.insert(i);
  for (int i = 0, r, c, v; i < q; ++i) {
    cin >> r >> c >> v, r--, c--; 
    int id = r*m+c;
    if (v > max_row[r]) {
      max_row[r] = v;
      if (row[r] != -1) {
        if (s.find(row[r]) != s.end()) s.erase(row[r]);
        row[r] = -1;
      }
    }
    if (v > max_col[c]) {
      max_col[c] = v;
      if (col[c] != -1) {
        if (s.find(col[c]) != s.end()) s.erase(col[c]);
        col[c] = -1;
      }
    }
    if (v == max_row[r] && v == max_col[c])
      row[r] = col[c] = id, s.insert(id);
    cout << s.size() << '\n';
  }
	return 0;
}


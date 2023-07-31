#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 305, S = 100000;

int n;
int f[S + 5]; 
pair<int, int> a[N];

#define fi first
#define se second

void insert(int id) {
  for (int i = S; i; --i) 
    if (i - a[id].fi >= 0 && ~f[i - a[id].fi] && !~f[i]) 
      f[i] = id;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n; 
  int s = 0;
  for (int i = 0; i < n; ++i)
    cin >> a[i].fi, a[i].se = i, 
    s += a[i].fi;
  sort(a, a + n);
  int half = s / 2; 
  memset(f, -1, sizeof(f)); 
  f[0] = 0; 
  for (int i = s, j = n-1; i > half; --i) {
    while (j >= 0 && i-a[j].fi <= half) 
      insert(j), j--;
    if (~f[i]) {
      vector<int> res;
      while (i) {
        res.emplace_back(a[f[i]].se);
        i -= a[f[i]].fi;
      }
      cout << res.size() << '\n';
      for (int i : res) cout << i+1 << ' '; 
      return 0;
    }
  }

	return 0;
}


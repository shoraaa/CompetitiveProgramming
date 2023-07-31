#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 9005;
int x[N];
vector<int> a;
int n, q;

ll get(int p) {
  // i <= p <= j, i <= j < p, p < i <= j
  ll res = 0;
  for (int i = 0, j = p; i <= p; ++i) {
    while (j < n && a[j] < a[i] + a[p]) j++;
    j--; if (a[j] >= a[i] + a[p]) break;
    res += j - p + 1;
  }
  for (int i = 0, j = p-1; i < p; ++i) {
    if (j < i) j = i;
    while (j >= i && a[p] < a[i] + a[j]) j--;
    j++; if (a[p] >= a[i] + a[j]) break;
    res += p-1 - j + 1;
  }
  for (int i = p+1, j = i; i < n; ++i) {
    if (j < i) j = i;
    while (j < n && a[j] < a[i] + a[p]) j++;
    j--; if (a[j] >= a[i] + a[p]) break; 
    res += j - i + 1;
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("tamgiac.inp", "r"))
    freopen("tamgiac.inp", "r", stdin),
    freopen("tamgiac.out", "w", stdout);
  cin >> n >> q; a.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> x[i], a[i] = x[i];
  sort(a.begin(), a.end());
  ll res = 0;
  for (int i = 0; i < n; ++i) {
    int k = n - 1;
    for (int j = n-1; j >= i; --j) {
      while (k >= j && a[k] >= a[i] + a[j]) k--;
      res += max(0, k - j + 1);
    }
  }
  cout << res << '\n';
  for (int i = 0, p, v, ov; i < q; ++i) {
    cin >> p >> v; p--;
    auto it = lower_bound(a.begin(), a.end(), x[p]); 
    res -= get(it - a.begin()); a.erase(it); 
    x[p] = v; it = lower_bound(a.begin(), a.end(), x[p]);
    a.insert(it, v); res += get(it - a.begin());
    cout << res << '\n';
  }
	return 0;
}


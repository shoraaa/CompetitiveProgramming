#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5, LIM = 1e7 + 5;
const ll INF = 9e18;
ll s[N], p[N];
int n, m, q;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> q;
  for (int i = 1; i <= n; ++i)
    cin >> s[i];
  for (int i = 0; i <= n; ++i)
    cin >> p[i];
  s[n + 1] = INF;
  
  vector<int> val;
  for (int i = 0, l, r; i < m; ++i) {
    cin >> l >> r;
    for (int j = l; j <= r; ++j) val.emplace_back(j);
	}
	sort(val.begin(), val.end());
	
  for (int i = 0; i < q; ++i) {
    ll t; cin >> t;
    ll cur = 0, tot = 0, ans = -1;
    for (int j = 0, i = 1; j < val.size(); ++j) {
    	while (cur >= s[i]) i++;
    	tot += val[j];
    	cur += p[i-1];
    	cerr << val[j] << ' ' << p[i-1] << '\n';
    	if (tot - cur >= t) {
    		ans = j + 1; break;
			}
		}
		cerr << tot << ' ' << cur << '\n';
		cout << ans << ' ';
  }
    
	return 0;
}



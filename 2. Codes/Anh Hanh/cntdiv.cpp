#include<bits/stdc++.h>
#define print(_v) for (auto& _e : _v) {cerr << _e << ' ';} cerr << '\n';
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "cntdiv";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e5 + 5;
const ll oo = 2e18;
int lp[N + 5];
vector<vector<ll>> pre, dp;
vector<ll> can;
vector<int> pr;
int n;
ll call(int p, int t) {
	if (p == pr.size()) 
		return can[t] == n ? 1 : oo;
	if (dp[p][t]) 
		return dp[p][t];
	ll res = oo;
	for (int i = 0; i < can.size(); ++i) if (pre[p][i] != -1 && n % (can[t] * can[i]) == 0) {
		ll nxt = call(p + 1, lower_bound(can.begin(), can.end(), can[t] * can[i]) - can.begin());
		if (nxt == oo || nxt > ll(1e18) / pre[p][i]) continue;
		res = min(res, nxt * pre[p][i]); 
	}
	return dp[p][t] = res;
}

ll pw(ll x, ll k) {
	ll res = 1;
	for (; k; k >>= 1) {
		if (k & 1) {
			if (res > ll(1e18) / x) return -1;
			res = res * x;
		}
		if (x > ll(1e18) / x) x = LLONG_MAX;
		else x = x * x;
	}
	return res;
}

int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	cin >> n;
	for (int i = 2; i <= n; ++i) {
	  if (lp[i] == 0) 
	      lp[i] = i,
	      pr.push_back(i);
	  for (ll p : pr) {
	  	if (p > lp[i] || i * p > n) break;
	  	lp[i * p] = p;
		}
	}
	for (int i = 1; i * i <= n; ++i)
		if (n % i == 0) can.emplace_back(i), can.emplace_back(n / i);
	sort(can.begin(), can.end());
	can.erase(unique(can.begin(), can.end()), can.end());
	
	pre.resize(pr.size(), vector<ll>(can.size(), -1));
	for (int i = 0; i < pr.size(); ++i) 
		for (int j = 0; j < can.size(); ++j) {
			pre[i][j] = pw(pr[i], can[j] - 1);
			if (pre[i][j] == -1) break;
		} 
		
	
	dp.resize(pr.size(), vector<ll>(can.size()));
	ll res = call(0, 0);
	if (res == oo) cout << -1;
	else cout << res;
	return 0;
}


#include<bits/stdc++.h>
#define print(_v) for (auto& _e : _v) {cerr << _e << ' ';} cerr << '\n';
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "minsum";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e5;
const ll oo = 1e18;
int lp[N + 5];
vector<int> pr;
vector<int> fac(int& n) {
	vector<int> res(pr.size());
	for (int i = 0; i < pr.size(); ++i) {
		int x = pr[i];
		while (n % x == 0) n /= x, res[i]++;
	}
	return res;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	int T;
	cin >> T;
	for (int i = 2; i <= N; ++i) {
	  if (lp[i] == 0) 
	      lp[i] = i,
	      pr.push_back(i);
	  for (ll p : pr) {
	  	if (p > lp[i] || i * p > N) break;
	  	lp[i * p] = p;
		}
	}
	int a, b;
	while (T--) {
		cin >> a >> b;	
		auto u = fac(a), v = fac(b);
		vector<int> p;
		for (int i = 0; i < u.size(); ++i) 
			if ((u[i] + v[i]) & 1) p.emplace_back(pr[i]); 	
		if (a > 1) p.emplace_back(a);
		if (b > 1) {
			if (a == b) p.pop_back();
			else p.emplace_back(b);
		}
		pair<ll, pair<ll, ll>> res = {oo, {0, 0}};
		for (int msk = 0; msk < 1 << int(p.size()); ++msk) {
			pair<ll, pair<ll, ll>> cur = {0, {1, 1}};
			for (int i = 0; i < p.size(); ++i) 
				if (msk >> i & 1) cur.second.first *= p[i];
				else cur.second.second *= p[i];
			cur.first = cur.second.second + cur.second.first;
			res = min(res, cur);
		} 
		cout << res.second.first << ' ' << res.second.second << '\n';
	}	
	return 0;
}


#include<bits/stdc++.h>
#define print(_v) for (auto& _e : _v) {cerr << _e << ' ';} cerr << '\n';
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "factorial";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e7;
int suf[N + 5], lp[N + 5];
vector<int> pr;
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	cin >> n;
	int M = 0;
	for (int i = 0, x; i < n; ++i) 
		cin >> x, M = max(M, x), suf[x]++;
	for (int i = M-1; i > 1; --i) 
		suf[i] += suf[i + 1];
	for (int i = 2; i <= M; ++i) {
	  if (lp[i] == 0) 
	      lp[i] = i,
	      pr.push_back(i);
	  for (ll p : pr) {
	  	if (p > lp[i] || i * p > M) break;
	  	lp[i * p] = p;
		}
	}
	
	vector<ll> cnt(pr.size());
	for (int i = 0; i < pr.size(); ++i) {
		for (int b = pr[i]; b <= M; b += pr[i]) {
			int add = 0, tmp = b;
			while (tmp % pr[i] == 0) tmp /= pr[i], add++;
			cnt[i] += add * suf[b];
		}
	}
	auto check = [&](ll mid) {
		vector<ll> cur(pr.size());
		for (int i = 0; i < pr.size(); ++i) {
			ll num = 1;
			for (int pw = 0; num <= mid; ++pw) {
				num *= pr[i];
				cur[i] += mid / num;
			}
		}
		for (int i = 0; i < pr.size(); ++i)
			if (cur[i] < cnt[i]) return 0;
		return 1;
	};
	ll lo = 0, hi = 1e14, mid, ans = -1;
	while (lo <= hi) {
		mid = (lo + hi) >> 1;
		if (check(mid))
			ans = mid,
			hi = mid - 1;
		else
			lo = mid + 1;
	}
	cout << ans;
	return 0;
}


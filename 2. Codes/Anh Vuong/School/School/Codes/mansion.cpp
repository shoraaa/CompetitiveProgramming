#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmin(X &a, const Y &b) {
	return a > b ? a = b, 1 : 0;
}

#define fi first
#define se second
#define eb emplace_back

using ii = pair <int, int>;
using ll = long long;

struct edge {
	int u, t; ll w;

	edge (int u, int t, ll w):
	u(u), t(t), w(w) {}

	bool operator < (const edge &o) const {
		return w > o.w;
	}
};

const int K = 200005;

vector <int> hx[K], hy[K];
map <int, int> idx, idy;
vector <ii> sw; ll d[K][2];
priority_queue <edge> pq;
int n, m, k, cntx, cnty;

void input() {
	cin >> n >> m >> k;
	memset(d, 0x3f, sizeof(d));
	for (int i = 0; i < k; i++) {
		int x, y; cin >> x >> y; sw.eb(x, y);
		if (x == 1) {
			d[i][0] = y - 1;
			pq.emplace(i, 0, y - 1);
		}
		if (!idx.count(x)) idx[x] = cntx++;
		if (!idy.count(y)) idy[y] = cnty++;
		hx[idx[x]].eb(i); hy[idy[y]].eb(i);
	}
	sw.eb(n, m);
	if (!idx.count(n)) idx[n] = cntx++;
	if (!idy.count(m)) idy[m] = cnty++;
	hx[idx[n]].eb(k); hy[idy[m]].eb(k);
}

void process() {
	auto cmpx = [&](int i, int j) {
		return sw[i].fi < sw[j].fi;
	};
	auto cmpy = [&](int i, int j) {
		return sw[i].se < sw[j].se;
	};
	for (int i = 0; i < cntx; i++)
		sort(hx[i].begin(), hx[i].end(), cmpy);
	for (int i = 0; i < cnty; i++)
		sort(hy[i].begin(), hy[i].end(), cmpx);
	while (pq.size()) {
		int i = pq.top().u, t = pq.top().t;
		ll w = pq.top().w; pq.pop();
		if (d[i][t] < w) continue;
		if (i == k) {
			cout << w << '\n'; return;
		}
		if (t) {
			auto it = lower_bound(hy[idy[sw[i].se]].begin(),
			hy[idy[sw[i].se]].end(), i, cmpx);
			if (it != hy[idy[sw[i].se]].begin()) {
				int j = *prev(it);
				if (cmin(d[j][t], w + sw[i].fi - sw[j].fi))
					pq.emplace(j, t, d[j][t]);
			}
			if (it != hy[idy[sw[i].se]].end()
			&& next(it) != hy[idy[sw[i].se]].end()) {
				int j = *next(it);
				if (cmin(d[j][t], w + sw[j].fi - sw[i].fi))
					pq.emplace(j, t, d[j][t]);
			}
		}
		else {
			auto it = lower_bound(hx[idx[sw[i].fi]].begin(),
			hx[idx[sw[i].fi]].end(), i, cmpy);
			if (it != hx[idx[sw[i].fi]].begin()) {
				int j = *prev(it);
				if (cmin(d[j][t], w + sw[i].se - sw[j].se))
					pq.emplace(j, t, d[j][t]);
			}
			if (it != hx[idx[sw[i].fi]].end()
			&& next(it) != hx[idx[sw[i].fi]].end()) {
				int j = *next(it);
				if (cmin(d[j][t], w + sw[j].se - sw[i].se))
					pq.emplace(j, t, d[j][t]);
			}
		}
		if (cmin(d[i][1 - t], w + 1))
			pq.emplace(i, 1 - t, w + 1);
	}
	cout << "-1\n";
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	input(); process();
}
#include <bits/stdc++.h>
#define FNAME "fibquery"
using namespace std;
mt19937 rnd(std::chrono::system_clock::now().time_since_epoch().count());
// uniform_int_distribution<int>(a, b)(rnd);
#define rd(a, b) uniform_int_distribution<int>(a, b)(rnd)

#define BIT(x, i) (x >> i & 1)
using ll = long long;

typedef pair<int, int> pii;
#define mp make_pair
#define fi first
#define se second

#define matrix vector<vector<ll> > 

const int MOD = 1e9 + 19972207;
const int N = 5e5 + 1;

int n, q, f1[N], f0[N], fib_base[2] = {0, 1}, a[N];
matrix mul(matrix x, matrix y) {
	matrix res(2, vector<ll>(2));
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			for (int k = 0; k < 2; ++k)
				res[i][j] += x[i][k] * y[k][j] % MOD,
				res[i][j] %= MOD;
	return res;
}
matrix pw(matrix base, ll p) {
	if (p == 1) return base;
	matrix tmp = pw(base, p / 2);
	if (p % 2) return mul(mul(tmp, tmp), base);
	else return mul(tmp, tmp);
}
int get_fib(ll k) {
	if (k <= 1) return fib_base[k];
	ll p = k - 1;
	matrix base(2, vector<ll>(2));
	base[0][0] = 0; base[1][0] = 1; 
	base[0][1] = 1; base[1][1] = 1;
	matrix matrix_get = pw(base, p);  
	
	ll ans = 0;
	for (int i = 0; i < 2; ++i)
		ans += matrix_get[i][1] * fib_base[i] % MOD,
		ans %= MOD;
	return ans;
}

int st[4 * N];
vector<pii> lazy[4 * N]; // val & idx

int get_mul(int idx, int l, int r) {
	if (idx == 1) return (f1[r] - f1[l - 1] + MOD) % MOD;
	int suml = 0, sumr = 0;
	if (l >= idx) suml = f0[l - idx + 1];
	if (r >= idx) sumr = f0[r - idx + 2];
	return (sumr - suml + MOD) % MOD;
}

void down(int id, int l, int r) {
	int mi = (l + r) / 2;
	for (pii &upd_val : lazy[id]) {
		// cout << "dcm " << l << ' ' << r << ' ' << upd_val.fi << ' ' << upd_val.se << '\n'; 
		int val = upd_val.fi, idx = upd_val.se;
	
		for (int i = 0, L, R; i < 2; ++i) {
			L = l; R = r;
			if (i) L = mi + 1;
			else R = mi;
			
			// cout << '*' << l << ' ' << r << ' '<< L << ' ' << R << ' ' << idx << ' ' << val << 
			// ' ' << 1LL * val * get_mul(idx, L, R) << '\n';
			
			st[2 * id + i] += 1LL * val * get_mul(idx, L, R) % MOD;
			st[2 * id + i] %= MOD;
			lazy[2 * id + i].push_back(upd_val);
		}
	}	
	lazy[id].clear(); lazy[id].shrink_to_fit();
}

void upd(int id, int l, int r, int u, int v, pii upd_val) {
	if (l > v || r < u) return;
	if (u <= l && r <= v) {
		int val = upd_val.fi, idx = upd_val.se;
		st[id] += 1LL * val * get_mul(idx, l, r) % MOD;
		st[id] %= MOD;
		
		// cout << idx << ' ' << l << ' ' << r << ' ' << st[id] << ' ' << upd_val.fi << ' ' << upd_val.se << '\n'; 
		
		lazy[id].push_back(upd_val);
		return;
	}
	down(id, l, r);
	int mi = (l + r) / 2;
	upd(2 * id, l, mi, u, v, upd_val); 
	upd(2 * id + 1, mi + 1, r, u, v, upd_val);
	st[id] = (st[2 * id] + st[2 * id + 1]) % MOD;	
}

int get(int id, int l, int r, int u, int v) {
	if (l > v || r < u) return 0;
	if (u <= l && r <= v) {
		// cout << l << ' ' << r << ' ' << st[id] << '\n';
		return st[id];
	}
	down(id, l, r);
	int mi = (l + r) / 2;
	return (get(2 * id, l, mi, u, v) + get(2 * id + 1, mi + 1, r, u, v)) % MOD;
}

void add(int val, int idx) {
	upd(1, 1, n, 1, n, {val, idx});
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cout.tie(0);
	if (fopen(FNAME".inp", "r")) {
		freopen(FNAME".inp", "r", stdin);
		freopen(FNAME".out", "w", stdout);
	}	
	cin >> n >> q;
	f1[1] = f0[2] = 1; 
	for (int i = 3; i <= n; ++i)
		f1[i] = (f1[i - 1] + f1[i - 2]) % MOD,
		f0[i] = (f0[i - 1] + f0[i - 2]) % MOD;
	
	for (int i = 1; i <= n; ++i)
		f1[i] = (f1[i] + f1[i - 1]) % MOD,
		f0[i] = (f0[i] + f0[i - 1]) % MOD;
	
	int idx, l, r; ll k;
	while (q--) {
		cin >> idx;
		if (idx == 1) {
			cin >> l >> r >> k;
			if (l == r) {
				int fib = get_fib(k);
				add(fib, l);
				if (l > 1 && l + 1 <= n) add((-fib + MOD) % MOD, l + 1);
				if (l + 2 <= n) add((-fib + MOD) % MOD, l + 2);			
			}
			else {
				int fib1 = get_fib(k), fib2 = get_fib(k + 1);
				add(fib1, l); add(fib2, l + 1);
				if (l > 1) add((-fib1 + MOD) % MOD, l + 1);
				
				fib1 = get_fib(k + r - l - 1); fib2 = get_fib(k + r - l);
				if (r + 1 <= n) 
					add(((-fib1 + MOD) % MOD + (-fib2 + MOD) % MOD) % MOD, r + 1);
				if (r + 2 <= n) 
					add((-fib2 + MOD) % MOD, r + 2);
			}
		}
		else {
			cin >> l >> r;
			cout << get(1, 1, n, l, r) << '\n';
		}
	}		
			
	return 0;
}

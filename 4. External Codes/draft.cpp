/// AC
#include<bits/stdc++.h>
#define int 					long long
#define FOR(i, a, b)			for (int i = a; i <= (int) b; ++i)
#define REP(i, a, b)			for (int i = a; i <  (int) b; ++i)
using namespace std;

struct ii {
	int t, w;
	ii() {}; ii(int t, int w) : t(t), w(w) {};
};

const int N = 1004, COOR = 1e4 + 4;
int n, A, B, D;
ii a[N];

int dp[N][COOR], sum[N];

void minimize(int &a, int b) { 
	if (b == -1) return;
	a = (a == -1 || a > b) ? b : a; 
}

void sol() {
	sort(a+1, a+n+1, [] (ii a, ii b) {
		return a.t * b.w < a.w * b.t;
	});
	for (int i = 1; i <= n; ++i) sum[i] = sum[i-1] + a[i].t;

	memset(dp, -1, sizeof(dp));
	for (int r = A; r <= B; ++r) {
		int l = r - a[1].t;
		if (l < A) continue;
		dp[1][r] = abs(r-D) * a[1].w;
	}

	REP(i, 1, n) FOR(r, A, B) {
		if (dp[i][r] == -1) continue;
		
		int l = r - sum[i];
		if (l < A) continue;

		/// Left 
		int nL = l - a[i+1].t, nR = r;
		if (A <= nL && nR <= B) {
			minimize(dp[i+1][nR], dp[i][r] + abs(l-D) * a[i+1].w);
		}	

		/// Right
		nL = l; nR = r + a[i+1].t;
		if (A <= nL && nR <= B) {
			minimize(dp[i+1][nR], dp[i][r] + abs(nR-D) * a[i+1].w);
		}
	}

	int res = -1;
	FOR(r, A, B) {
		minimize(res, dp[n][r]);
		if (res == 576) { cerr << "# " << r << '\n'; exit(0); }
	}
	cout << res << '\n';
}

main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	if (fopen("input.txt", "r")) {
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	}
	else if (fopen("dbg.inp", "r")) {
		freopen("dbg.inp", "r", stdin);
		freopen("dbg.out", "w", stdout);
	}

	cin >> n >> A >> B >> D;
	for (int i = 1; i <= n; ++i) cin >> a[i].t >> a[i].w;

	sol();

	return 0;
} 
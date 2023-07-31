#include <bits/stdc++.h>
using namespace std;
#define TASK "cwbrobot"
#define int long long
#define sqr(x) (1LL*x*x)
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define BIT(x, k) ((x >> k) & 1)
#define cntBit(x) __builtin_popcountll(x)
#define REP(i,a,b) for (int i = (int) a; i < (int) b; i++)
#define FOR(i,a,b) for (int i = (int) a; i <= (int) b; i++)
#define FORD(i,a,b) for (int i = (int) a; i >= (int) b; i--)

typedef pair <int, int> ii;

const int N = 1e5 + 5;
int n, k, d, w[30], s[N];

namespace sub1 {
    int vis[30];
	void solve() {
		int res = 0;
		for (int msk = 0; msk < (1 << n); msk++) {
            memset (vis, 0, sizeof vis);
			int cnt = 0, totW = 0;
			for (int b = 0; b < n; b++) if (BIT (msk, b)) {
                if (!vis[s[b+1]]) {
                    vis[s[b+1]] = 1;
                    totW += w[s[b+1]];
                } else cnt++;
            }
            if (totW > k) cnt = -1;
			res = max (res, cnt);
		}
		cout << res << '\n';
	}
}

namespace sub2 {

    int num;
    vector <int> List[3000];
    map < vector <int>, int> Mask;

    vector <int> msk;
    void gen(int cur, int totW) {
        if (totW > k) return;

        if (!Mask[msk]) {
            Mask[msk] = ++num;
            List[num] = msk;
        }

        if (cur == d) return;

        gen (cur + 1, totW);

        msk.push_back (cur + 1);
        gen (cur + 1, totW + w[cur+1]);
        msk.pop_back();
    }

    bool in(int q, int x) {
        vector <int> s = List[q];
        for (int u : s)
            if (u == x) return true;
        return false;
    }

    int add (int q, int x) {
        vector <int> s = List[q];
        s.push_back (x); sort (all (s));
        return Mask[s];
    }

    int del (int q, int x) {
        vector <int> s = List[q];
        int p = -1;
        for (int i = 0; i < s.size(); i++)
            if (s[i] == x) { p = i; break; }
        assert (p != -1);
        s.erase (s.begin()+p); return Mask[s];
    }

    int f[205][3000];

    void maximize(int &a, int b) { a = max (a, b); }
    void solve() {
        gen (0, 0);

        memset (f, -1, sizeof f);
        f[0][1] = 0; int res = 0;

        for (int i = 0; i <= n; i++)
            for (int msk = 1; msk <= num; msk++) {
                if (f[i][msk] == -1) continue;
                res = max (res, f[i][msk]);
                vector <int> cur = List[msk];
                bool inVector = in (msk, s[i+1]);
                if (inVector) {
                    maximize (f[i+1][msk], f[i][msk] + 1);
                    int nxt = del (msk, s[i+1]);
                    maximize (f[i+1][nxt], f[i][msk] + 1);
                }
                else {
                    int nxt = add (msk, s[i+1]);
                    maximize (f[i+1][nxt], f[i][msk]);
                    maximize (f[i+1][msk], f[i][msk]);
                }
            }
        
        cout << res << '\n';
    }
}

namespace sub3 {
    int f[203][1100];

    void maximize (int &a, int b) { a = max (a, b); }
    int upbit(int x, int k) { return x | (1 << k); }
    int downbit(int x, int k) { return x & (~(1 << k)); }

    void solve() {
        memset (f, -1, sizeof f);
        f[0][0] = 0; int res = 0;
        for (int i = 0; i <= n; i++)
            for (int msk = 0; msk < (1 << d); msk++) {
                if (f[i][msk] == -1) continue;
                res = max (res, f[i][msk]);
                int totW = 0;
                for (int bit = 0; bit < d; bit++) if (BIT (msk, bit))
                    totW += w[bit+1];
                if (totW > k) continue;
                int bit = s[i+1] - 1;
                if (BIT (msk, bit)) {
                    maximize (f[i+1][msk], f[i][msk] + 1);
                    maximize (f[i+1][downbit(msk, bit)], f[i][msk] + 1);
                }
                else {
                    maximize (f[i+1][msk], f[i][msk]);
                    maximize (f[i+1][upbit (msk, bit)], f[i][msk]);
                }
            }
        cout << res << '\n';
    }
}

namespace sub4 {
    int nxt[N][30];
    bool in(int a, vector <int> b) {
        for (int u : b) {
            if (u == a) {
                return true;
            }
        }
        return false;
    }

    void solve() {
        k /= w[1];
        for (int i = 1; i <= 26; i++)
            nxt[n+1][i] = INT_MAX;
        for (int i = n; i >= 1; i--) {
            for (int j = 1; j <= 26; j++)
                nxt[i][j] = nxt[i+1][j];
            nxt[i][s[i+1]] = i + 1;
        }
        vector <int> bag;
        int res = 0;
        for (int i = 1; i <= n; i++) {
            if (in(s[i], bag)) {
                res++;
                continue;
            }
            if (bag.size() < k) bag.push_back (s[i]);
            else {
                int p = -1, Next = -1;
                for (int u : bag) if (nxt[i][u] > Next) {
                    Next = nxt[i][u]; p = u;
                }
                if (Next > nxt[i][s[i]]) {
                    int x;
                    for (x = 0; x < bag.size(); x++)
                        if (bag[x] == p) break;
                    // cerr << x << '\n';
                    bag.erase (bag.begin() + x);
                    bag.push_back (s[i]);
                }
            }
        }

        cout << res << '\n';
    }
}

#undef int
int main() {
#define int long long

	ios :: sync_with_stdio (0);
	cin.tie (0); cout.tie (0);

	if (fopen ("main.in", "r"))
		freopen ("main.in", "r", stdin);
	else if (fopen (TASK".inp", "r"))
		freopen (TASK".inp", "r", stdin),
		freopen (TASK".out", "w", stdout);

	cin >> n >> k >> d;
	for (int i = 1; i <= n; i++) {
		char c; cin >> c;
		s[i] = c - 'a' + 1;
	}
	for (int i = 1; i <= d; i++) {
		cin >> w[i];
        assert (w[i] > 0);
    }

	if (n <= 20)
		sub1 :: solve();
	else if (n <= 200 && k <= 3)
        sub2 :: solve();
    else if (n <= 200 && d <= 10)
        sub3 :: solve();
    else
        sub4 :: solve();

	return 0;
}
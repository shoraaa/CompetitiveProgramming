#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmin(X &a, const Y &b) {
    return a > b ? a = b, 1 : 0;
}

#define eb emplace_back
#define fi first
#define se second

using ii = pair <int, int>;

const int N = 2505;
const int M = 5005;

vector <ii> g[N]; ii ed[M];
int d[N]; queue <int> q;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> ed[i].fi >> ed[i].se;
        g[ed[i].fi].eb(ed[i].se, i);
        g[ed[i].se].eb(ed[i].fi, i);
    }
    int res = -1;
    for (int i = 0; i < m; i++) {
        fill(d + 1, d + n + 1, -1);
        d[ed[i].fi] = 0;
        q.emplace(ed[i].fi);
        while (q.size()) {
            int u = q.front(); q.pop();
            for (ii e : g[u])
                if (e.se != i && d[e.fi] < 0) {
                    d[e.fi] = d[u] + 1;
                    q.emplace(e.fi);
                }
        }
        if (~d[ed[i].se]) {
            if (res < 0)
                res = d[ed[i].se] + 1;
            else cmin(res, d[ed[i].se] + 1);
        }
    }
    cout << res << '\n';
}
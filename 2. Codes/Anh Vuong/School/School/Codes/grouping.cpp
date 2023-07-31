#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 7505;
const ll inf = 0x3f3f3f3f3f3f3f3f;

struct edge {
    int u, v; ll w;
};

ll a, b, c;
int par[N], sz[N], mn[N];
edge mst[N];

ll cost(int i, int j) {
    if (i > j) swap(i, j);
    return (a * i + b * j) % c;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    cin >> a >> b >> c;
    for (int i = 2; i <= n; i++) mn[i] = 1;
    for (int cc = 1; cc < n; cc++) {
        int u = 0; ll ed = inf;
        for (int i = 1; i <= n; i++)
            if (mn[i] && cost(i, mn[i]) < ed) {
                ed = cost(i, mn[i]); u = i;
            }
        mst[cc] = {u, mn[u], cost(u, mn[u])};
        mn[u] = 0;
        for (int i = 1; i <= n; i++)
            if (mn[i] && cost(i, mn[i]) > cost(i, u))
                mn[i] = u;
    }
    sort(mst + 1, mst + n,
    [](edge p, edge q) {
        return p.w < q.w;
    });
    cout << mst[n - k + 1].w << '\n';
}

#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmax(X &a, const Y &b) {
    return a < b ? a = b, 1 : 0;
}

const int V = 200005;
const double inf = -1e18;

double f[V], g[V];

void solve() {
    int n, p; cin >> n >> p;
    fill(f + 1, f + V, inf); f[0] = 0;
    for (int i = 1; i <= n; i++) {
        int w, h; cin >> w >> h;
        int mi = 2 * (w + h + min(w, h));
        double ma = 2.0 * (w + h
        + sqrt(w * w + h * h));
        fill(g, g + V, inf);
        for (int i = 0; i < V - mi; i++)
            g[i + mi] = f[i] + ma - mi;
        int fix = 2 * (w + h);
        for (int i = 0; i < V - fix; i++)
            cmax(g[i + fix], f[i]);
        for (int i = V - 1; i > 0; i--)
            if (g[i - 1] >= 1)
                cmax(g[i], g[i - 1] - 1);
        swap(f, g);
    }
    double res = 0;
    for (int i = 0; i <= p; i++)
        cmax(res, i + f[i]);
    res = min(res, double(p));
    cout << res << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    cout << setprecision(6) << fixed;
    while (t--) solve();
}
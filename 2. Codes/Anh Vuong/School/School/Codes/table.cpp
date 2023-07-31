#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

const int Q = 5005;

pair <int, int> hor[Q], ver[Q];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    for (int i = 1; i <= q; i++) {
        int x, r, c, u, v, tot = 0;
        cin >> x >> r >> c; x--; r--; c--;
        u = x / n; v = x % n;
        for (int j = 1; j < i; j++) {
            if (u == hor[j].fi)
                v = (v + hor[j].se + n) % n;
            if (v == ver[j].fi)
                u = (u + ver[j].se + n) % n;
        }
        tot = (c - v + n) % n;
        tot += (r - u + n) % n;
        cout << tot << '\n';
        hor[i] = {u, c - v};
        ver[i] = {c, r - u};
    }
}
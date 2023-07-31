#include <bits/stdc++.h>
using namespace std;

struct seg {
    int l, r;
};

const int N = 500005;

seg a[2][N]; int c[N], q[2], cnt[2][N];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    stack <seg, vector <seg>> s;
    for (int i = 0; i < m; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        x--; l++; r++;
        a[x][q[x]++] = {l, r};
    }
    sort(a[0], a[0] + q[0],
    [](seg p, seg q) {
        return p.r < q.r;
    });
    for (int i = 0; i < q[0]; i++) {
        int l = a[0][i].l, r = a[0][i].r;
        while (s.size() && s.top().r >= l) {
            l = min(l, s.top().l); s.pop();
        }
        s.push({l, r});
    }
    q[0] = 0;
    while (!s.empty()) {
        a[0][q[0]++] = s.top(); s.pop();
    }
    reverse(a[0], a[0] + q[0]);
    a[0][q[0]] = {n + 1, n + 1};
    int col = 0;
    for (int i = 1; i < a[0][0].l; i++) {
        c[i] = col; col ^= 1;
    }
    for (int i = 0; i < q[0]; i++) {
        for (int j = a[0][i].l;
        j <= a[0][i].r; j++) c[j] = col;
        col ^= 1;
        for (int j = a[0][i].r + 1;
        j < a[0][i + 1].l; j++) {
            c[j] = col; col ^= 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        cnt[c[i]][i]++;
        cnt[0][i] += cnt[0][i - 1];
        cnt[1][i] += cnt[1][i - 1];
    }
    for (int i = 0; i < q[1]; i++) {
        int zero = cnt[0][a[1][i].r];
        int one = cnt[1][a[1][i].r];
        zero -= cnt[0][a[1][i].l - 1];
        one -= cnt[1][a[1][i].l - 1];
        if (!zero || !one) {
            cout << "0\n"; return 0;
        }
    }
    cout << "1\n";
    for (int i = 1; i <= n; i++)
        cout << (c[i] ? 'B' : 'R');
}
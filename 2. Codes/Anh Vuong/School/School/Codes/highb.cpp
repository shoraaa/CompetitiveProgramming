#include <bits/stdc++.h>

using namespace std;

const int N = 105;

int h[N];

void solve() {
    int n, a, b, c;
    cin >> n >> a >> b >> c;
    if (a + b - c > n) {
        cout << "IMPOSSIBLE\n"; return;
    }
    if (n == 1) {
        cout << "1\n"; return;
    }
    if (n == 2) {
        if (c == 2) {
            if (a < 2 || b < 2)
                cout << "IMPOSSIBLE\n";
            else cout << "1 1\n";
        }
        else {
            if (a == 1 && b == 1) {
                cout << "IMPOSSIBLE\n";
                return;
            }
            if (a == 1) cout << "2 1\n";
            else cout << "1 2\n";
        }
        return;
    }
    if (a == b && b == c && a == 1) {
        cout << "IMPOSSIBLE\n"; return;
    }
    if (a == c && b == c) {
        for (int i = 1; i < c; i++)
            cout << n << ' ';
        for (int i = 1; i <= n - c; i++)
            cout << n - 1 << ' ';
        cout << n << '\n'; return;
    }
    int d = n - (a + b - c);
    if (a == c) {
        for (int i = 1; i <= c; i++)
            cout << n << ' ';
        for (int i = 1; i <= d; i++)
            cout << n - 2 << ' ';
        for (int i = 1; i <= b - c; i++)
            cout << n - 1 << ' ';
        cout << '\n'; return;
    }
    if (b == c) {
        for (int i = 1; i <= a - c; i++)
            cout << n - 1 << ' ';
        for (int i = 1; i <= d; i++)
            cout << n - 2 << ' ';
        for (int i = 1; i <= c; i++)
            cout << n << ' ';
        cout << '\n'; return;
    }
    for (int i = 1; i <= a - c; i++)
        cout << n - 1 << ' ';
    for (int i = 1; i <= c; i++)
        cout << n << ' ';
    for (int i = 1; i <= d; i++)
        cout << n - 2 << ' ';
    for (int i = 1; i <= b - c; i++)
        cout << n - 1 << ' ';
    cout << '\n';
}

int main() {
    //freopen("highb.in", "r", stdin);
    //freopen("highb.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
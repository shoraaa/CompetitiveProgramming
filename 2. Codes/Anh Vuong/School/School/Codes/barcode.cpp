#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <class T>
T inverse(T a, T m) {
    T u = 0, v = 1;
    while (a != 0) {
        T t = m / a;
        m -= t * a; swap(a, m);
        u -= t * v; swap(u, v);
    }
    return u;
}

const int N = 1e6 + 5;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int q; cin >> q;
    while (q--) {
        int n, m; cin >> n >> m;
        int a = 1, b = 2 % m;
        for (int i = 2; i <= n; i++) {
            a = (b = a + b) - a;
            if (b >= m) b -= m;
        }
        if (n & 1) {
            cout << b << '\n';
            continue;
        }
        (b -= n / 2 + 1) %= m;
        a = 1; int cnt = 0;
        for (int i = 1; i <= n / 2; i++) {
            int j = i;
            while (j % m == 0) {
                j /= m; cnt--;
            }
            a = ll(a) * inverse(j, m) % m;
            j = i + n / 2;
            while (j % m == 0) {
                j /= m; cnt++;
            }
            a = ll(a) * j % m;
        }
        if (cnt) a = 0;
        (b += a) %= m;
        if (b < 0) b += m;
        cout << b << '\n';
    }
}
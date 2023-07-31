#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int bit[N];

void update(int i) {
    for (; i < N; i += i & -i)
        bit[i]++;
}

int query(int i) {
    int res = 0;
    for (; i > 0; i -= i & -i)
        res += bit[i];
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    long long m; int n;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int p, lo = 1, hi = n;
        long long mx = 1ll *
        (n - i) * (n - i - 1) / 2;
        while (lo <= hi) {
            int mi = (lo + hi) / 2;
            int ad = mi - query(mi) - 1;
            if (mx + ad >= m && ad >= 0) {
                p = mi; hi = mi - 1;
            }
            else lo = mi + 1;
        }
        m -= p - query(p) - 1;
        cout << p << ' '; update(p);
    }
}

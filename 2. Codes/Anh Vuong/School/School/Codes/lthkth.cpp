#include <bits/stdc++.h>

using namespace std;

const int N = 200005;
const int LG = 18;

int a[N], n, k; long long req;

int main() {
    freopen("lthkth.in", "r", stdin);
    freopen("lthkth.out", "w", stdout);
    cin >> n >> k >> req;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int lo = 1, hi = n;
    while (lo < hi) {
        int mi = (lo + hi) / 2;
        long long cnt = 0; int les = 0;
        for (int i = 1, j = 0; i <= n; i++) {
            while (les < k && j < n)
                les += a[++j] <= mi;
            if (les >= k) cnt += n - j + 1;
            les -= a[i] <= mi;
        }
        if (cnt >= req) hi = mi;
        else lo = mi + 1;
    }
    cout << hi << '\n';
}

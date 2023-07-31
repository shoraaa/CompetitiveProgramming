#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("sumdiv.inp", "r", stdin);
    freopen("sumdiv.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    long long a, b; cin >> a >> b;
    long long res = 0;
    for (long long i = 1; i <= b; i++) {
        long long k = b / i, j = b / k;
        long long l = (a - 1) / k + 1;
        if (max(i, l) <= j)
            res += (j + max(i, l))
            * (j - max(i, l) + 1);
        i = j;
    }
    cout << res / 2 << '\n';
}

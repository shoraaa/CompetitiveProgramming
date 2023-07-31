#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int long long inf = 1e15;

int n, k, a[N];

bool check(long long val) {
    long long sum = 0;
    for (int i = 1; i <= n; i++)
        sum += min (val, a[i] + 0LL);
    cout << sum << '\n';
    return sum >= val * k;
}

int main() {
    freopen ("group0.inp", "r", stdin);
    freopen ("group0.out", "w", stdout);

    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    check (3); exit (0);

    long long res = 0;
    for (long long low = 0, high = inf; low <= high; ) {
        long long mid = (low + high) >> 1;
        if (check (mid)) res = mid, low = mid + 1;
        else high = mid - 1;
    }

    cout << res << '\n';
}

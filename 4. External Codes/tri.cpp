#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, k, a[N];

int main() {
    freopen ("tri.inp", "r", stdin);
    freopen ("tri.out", "w", stdout);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];

    deque <int> dq; long long s = 0;
    for (int i = 1; i <= k - 1; i++) {
        while (dq.size() && a[dq.back()] <= a[i]) dq.pop_back();
        dq.push_back (i); s += a[i];
    }

    int res = 0;
    for (int i = 0; i <= n - k; i++) {
        s -= a[i]; s += a[i+k];
        while (dq.size() && dq.front() <= i) dq.pop_front();
        while (dq.size() && a[dq.back()] <= a[i+k]) dq.pop_back();
        dq.push_back (i+k);
        if (a[dq.front()] < s - a[dq.front()]) res++;
    }

    cout << res << '\n';

    return 0;
}

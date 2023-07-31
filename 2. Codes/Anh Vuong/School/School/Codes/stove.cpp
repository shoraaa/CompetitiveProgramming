#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("stove.in", "r", stdin);
    freopen("stove.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    int n, k; cin >> n >> k;
    vector <int> a(n), b(n - 1);
    for (int &x : a) cin >> x;
    long long res = n;
    for (int i = 1; i < n; i++)
        b[i - 1] = a[i] - a[i - 1];
    sort(b.begin(), b.end());
    for (int i = 0; i < n - k; i++)
        res += b[i] - 1;
    cout << res << '\n';
}

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int bit[N], a[N], p[N];

void update(int i) {
    for (; i > 0; i -= i & -i)
        bit[i]++;
}

int query(int i) {
    int res = 0;
    for (; i < N; i += i & -i)
        res += bit[i];
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n; cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++) {
        int x; cin >> x; p[x] = i;
    }
    long long res = 0;
    for (int i = 1; i <= n; i++) {
        res += query(p[a[i]]);
        update(p[a[i]]);
    }
    cout << res << '\n';
}

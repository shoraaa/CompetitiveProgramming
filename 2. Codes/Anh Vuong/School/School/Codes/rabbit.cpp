#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 200005;
const int INF = 0x3f3f3f3f;

int bit[N], id[N]; ll a[N];

void update(int i, int v) {
    for (; i > 0; i -= i & -i)
        bit[i] = min(bit[i], v);
}

int query(int i) {
    int res = INF;
    for (; i < N; i += i & -i)
        res = min(res, bit[i]);
    return res;
}    

int main() {
    freopen("rabbit.in", "r", stdin);
    freopen("rabbit.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    memset(bit, 0x3f, sizeof bit);
    int n; ll m; cin >> n >> m;
    vector <ll> val; int res = n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        val.push_back(a[i] - m * i);
    }
    val.push_back(0);   
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(),
    val.end()), val.end());
    for (int i = 0; i <= n; i++)
        id[i] = upper_bound(val.begin(),
        val.end(), a[i] - m * i) - val.begin();
    update(id[0], 0); int cur;
    for (int i = 1; i <= n; i++) {
        cur = min(INF, query(id[i]) + i - 1);
        res = min(res, cur + n - i);
        update(id[i], cur - i);
    }
    cout << res << '\n';
}
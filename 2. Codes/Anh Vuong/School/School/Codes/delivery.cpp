#include <bits/stdc++.h>

using namespace std;

template <class X, class Y>
bool cmin(X &a, const Y &b) {
    return a > b ? a = b, 1 : 0;
}


using ll = long long;

const int N = 100005;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll bit[2][N], suf[N];
int a[N], id[N];

void update0(int i, ll v) {
    for (; i < N; i += i & -i)
        cmin(bit[0][i], v);
}

void update1(int i, ll v) {
    for (; i > 0; i -= i & -i)
        cmin(bit[1][i], v);
}

ll query0(int i) {
    ll res = INF;
    for (; i > 0; i -= i & -i)
        cmin(res, bit[0][i]);
    return res;
}

ll query1(int i) {
    ll res = INF;
    for (; i < N; i += i & -i)
        cmin(res, bit[1][i]);
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    memset(bit, 0x3f, sizeof bit);
    vector <int> val;
    int n; ll res = INF; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i]; val.push_back(a[i]);
    }
    for (int i = n - 1; i > 0; i--)
        suf[i] = suf[i + 1] + abs(a[i] - a[i + 1]);
    val.push_back(0); ll pre = 0;
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(),
     val.end()), val.end());
    for (int i = 0; i <= n; i++)
        id[i] = upper_bound(val.begin(),
        val.end(), a[i]) - val.begin();
    for (int i = 1; i <= n; i++) {
        ll cur = min(query0(id[i]) - suf[i - 1] +
        a[i], query1(id[i]) - suf[i - 1] - a[i]);
        cmin(cur, pre + abs(a[i]));
        pre += abs(a[i] - a[i - 1]);
        cmin(res, cur + suf[i]);
        update0(id[i - 1], cur + suf[i] - a[i - 1]);
        update1(id[i - 1], cur + suf[i] + a[i - 1]);
    }
    cout << res << '\n';
}
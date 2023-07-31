#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int p[N], a[N], bit[2][N], kmp[N];

void update(int id, int i, int v) {
    if (i == 0) return;
    for (; i < N; i += (i & -i))
        bit[id][i] += v;
}

int query(int id, int i) {
    int res = 0;
    for (; i > 0; i -= i & -i)
        res += bit[id][i];
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x; p[x] = i;
    }
    for (int i = 1; i <= m; i++)
        cin >> a[i];
    {
        vector <int> cmp(a + 1, a + m + 1);
        sort(cmp.begin(), cmp.end());
        cmp.erase(unique(cmp.begin(),
        cmp.end()), cmp.end());
        for (int i = 1; i <= m; i++)
            a[i] = distance(cmp.begin(),
            upper_bound(cmp.begin(),
            cmp.end(), a[i]));
    }
    for (int i = 2, j = 0; i <= n; i++) {
        while (j > 0) {
            if (query(0, p[j + 1])
            == query(1, p[i])) break;
            for (int k = j; k > kmp[j]; k--)
                update(0, p[k], -1);
            for (int k = i - j;
            k < i - kmp[j]; k++)
                update(1, p[k], -1);
            j = kmp[j];
        }
        if (query(0, p[j + 1])
        == query(1, p[i])) j++;
        update(0, p[j], 1);
        update(1, p[i], 1);
        kmp[i] = j;
    }
    vector <int> ans;
    memset(bit[0], 0, sizeof bit[0])
 ;   memset(bit[1], 0, sizeof bit[1]);
    for (int i = 1, j = 0; i <= m; i++) {
        while (j > 0) {
            if (query(0, p[j + 1])
            == query(1, a[i])) break;
            for (int k = j; k > kmp[j]; k--)
                update(0, p[k], -1);
            for (int k = i - j;
            k < i - kmp[j]; k++)
                update(1, a[k], -1);
            j = kmp[j];
        }
        if (query(0, p[j + 1])
        == query(1, a[i])) j++;
        update(0, p[j], 1);
        update(1, a[i], 1);
        if (j == n) {
            ans.push_back(i - n + 1);
            for (int k = j; k > kmp[j]; k--)
                update(0, p[k], -1);
            for (int k = i - j + 1;
            k <= i - kmp[j]; k++)
                update(1, a[k], -1);
            j = kmp[j];
        }
        
    }
    cout << ans.size() << '\n';
    for (int x : ans) cout << x << ' ';
}
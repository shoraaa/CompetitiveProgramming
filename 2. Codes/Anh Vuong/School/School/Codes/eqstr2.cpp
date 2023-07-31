#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back

using ll = long long;
using ii = pair <int, int>;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7;
const int B = 5;
char s[N], t[N];
ll hss[N][26], hst[N][26], pw[N];
int mp[26], nrs[N][26], nrt[N][26];

void solve() {
    cin >> (s + 1) >> (t + 1);
    int n = strlen(s + 1);
    int dif = 0; pw[0] = 1;
    memset(mp, -1, sizeof mp);
    for (int i = 1; i <= n; i++) {
        if (mp[s[i] - 'a'] == -1)
            mp[s[i] - 'a'] = dif++;
        s[i] = 'a' + mp[s[i] - 'a'];
        pw[i] = pw[i - 1] * B % MOD;
        for (int c = 0; c < 26; c++)
            hss[i][c] = hss[i - 1][c] * B % MOD;
        ++hss[i][s[i] - 'a'] %= MOD;
    }
    dif = 0;
    memset(mp, -1, sizeof mp);
    for (int i = 1; i <= n; i++) {
        if (mp[t[i] - 'a'] == -1)
            mp[t[i] - 'a'] = dif++;
        t[i] = 'a' + mp[t[i] - 'a'];
        for (int c = 0; c < 26; c++)
            hst[i][c] = hst[i - 1][c] * B % MOD;
        ++hst[i][t[i] - 'a'] %= MOD;
    }
    for (int i = n; i > 0; i--) {
        for (int c = 0; c < 26; c++) {
            nrs[i][c] = nrs[i + 1][c];
            nrt[i][c] = nrt[i + 1][c];
        }
        nrs[i][s[i] - 'a'] = i;
        nrt[i][t[i] - 'a'] = i;
    }
    int q; cin >> q;
    while (q--) {
        vector <ii> f, g; int i, j, k;
        cin >> i >> j >> k;
        for (int c = 0; c < 26; c++) {
            if (nrs[i][c] && nrs[i][c] < i + k) {
                int x = hss[i + k - 1][c]
                - hss[i - 1][c] * pw[k] % MOD;
                if (x < 0) x += MOD;
                f.eb(nrs[i][c], x);
            }
            if (nrt[j][c] && nrt[j][c] < j + k) {
                int x = hst[j + k - 1][c]
                - hst[j - 1][c] * pw[k] % MOD;
                if (x < 0) x += MOD;
                g.eb(nrt[j][c], x);
            }
        }
        if (f.size() != g.size()) {
            cout << "no\n"; continue;
        }
        sort(f.begin(), f.end());
        sort(g.begin(), g.end());
        bool flag = 1;
        for (int x = 0; x < f.size(); x++)
            if (f[x].second != g[x].second) {
                flag = 0; break;
            }
        cout << (flag ? "yes\n" : "no\n");
    }
    for (int i = 1; i <= n; i++)
        for (int c = 0; c < 26; c++)
            nrs[i][c] = nrt[i][c] = 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
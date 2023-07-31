#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

const int N = 500005;

int cnt[N][2], s[N], t[N];
long long dp[N];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k; cin >> n >> k;
    s[0] = t[0] = -1;
    for (int i = 1; i <= n; i++) {
        char c; cin >> c;
        if (c == 'B') s[i] = 1;
    }
    deque <pair <int, int>> dq[2];
    for (int i = 1; i <= n; i++) {
        char c; cin >> c;
        if (c == 'B') t[i] = 1;
        cnt[i][0] = cnt[i - 1][0];
        cnt[i][1] = cnt[i - 1][1];
        if (t[i] != t[i - 1])
            cnt[i][t[i]]++;
        while (dq[0].size() &&
        dq[0].front().fi < i - k)
            dq[0].pop_front();
        while (dq[1].size() &&
        dq[1].front().fi < i - k)
            dq[1].pop_front();
        pair <int, int> cur(i - 1, 0);
        cur.se = dp[i - 1] - cnt[i - 1][0];
        cur.se += t[i - 1] == t[i] && !t[i];
        while (dq[0].size() &&
        dq[0].back().se >= cur.se)
            dq[0].pop_back();
        dq[0].push_back(cur);
        cur.se = dp[i - 1] - cnt[i - 1][1];
        cur.se += t[i - 1] == t[i] && t[i];
        while (dq[1].size() &&
        dq[1].back().se >= cur.se)
            dq[1].pop_back();
        dq[1].push_back(cur);
        if (s[i] == t[i]) dp[i] = dp[i - 1];
        else dp[i] = dq[1 - t[i]][0].se
                + 1 + cnt[i][1 - t[i]];
    }
    cout << dp[n] << '\n';
}
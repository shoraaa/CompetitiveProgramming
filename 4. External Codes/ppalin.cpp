#include <bits/stdc++.h>
using namespace std;

string s;
int k, n, cnt[2][300];
multiset < int > S[2];

void update(int ind, int w) {
    int type = ind % 2;
    if (S[type].find(cnt[type][s[ind]]) != S[type].end())
        S[type].erase (S[type].find(cnt[type][s[ind]]));
    cnt[type][s[ind]] += w;
    S[type].insert (cnt[type][s[ind]]);
}

bool check(int i, int j) {
    if (i == j) return true;
    int part1 = (j - i + 1) / 2;
    int type1 = (i + 1) % 2;
    auto it = prev(S[type1].end());
    int sum1 = part1 - *it;

    int part2 = (j - i + 1) - part1;
    int type2 = i % 2;
    it = prev(S[type2].end());
    int sum2 = part2 - *it;

    return (sum1 + sum2 <= k);
}

int main() {
    freopen ("ppalin.inp", "r", stdin);
    freopen ("ppalin.out", "w", stdout);

    cin >> s >> k;
    n = s.size(); s = ' ' + s;

    set <pair<char, int>> S1, S2;

    int res = 1;
    for (int i = 1, j = 1; i <= n; i++) {
        if (i > 1) update (i-1, -1);
        while (j <= n) {
            update (j, 1);
            if (!check(i, j)) {
                update (j, -1);
                break;
            }
            j++;
        }
        res = max (res, j - i);
    }

    cout << res << '\n';
}

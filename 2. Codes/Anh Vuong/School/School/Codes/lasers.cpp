#include <bits/stdc++.h>
using namespace std;

const int N = 500000;

vector <int> wood[N];
int ptr[N], len[N], sum[N];
multiset <int> ms;
vector <pair <int, int>> event, bor;

int main() {
    freopen("lasers.in", "r", stdin);
    freopen("lasers.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    int m, n; cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        cin >> len[i];
        wood[i].resize(len[i] + 1);
        for (int j = 1; j <= len[i]; j++) {
            cin >> wood[i][j];
            sum[i] += wood[i][j];
            wood[i][j] += wood[i][j - 1];
            bor.emplace_back(i, j);
        }
        ms.emplace(sum[i]);
    }
    sort(bor.begin(), bor.end(),
    [&](const pair <int, int> &a,
    const pair <int, int> &b) {
        return wood[a.first][a.second] < wood[b.first][b.second];
    });
    if (*ms.rbegin() < m) {
        event.emplace_back(1, 1);
        event.emplace_back(m - *ms.rbegin() + 1, -1);
    }
    for (int i = 0; i < bor.size(); i++) {
        ms.erase(ms.find(sum[bor[i].first] -
        wood[bor[i].first][bor[i].second - 1]));
        ms.insert(sum[bor[i].first] -
        wood[bor[i].first][bor[i].second]);
        if (i == bor.size() - 1 ||
        wood[bor[i].first][bor[i].second] !=
        wood[bor[i + 1].first][bor[i + 1].second]) {
            if (wood[bor[i].first][bor[i].second] < m - *ms.rbegin()) {
                event.emplace_back(wood[bor[i].first][bor[i].second] + 1, 1);
                event.emplace_back(m - *ms.rbegin() + 1, -1);
            }
        }
    }
    sort(event.begin(), event.end());
    int cur = 0, last = 1, res = m;
    for (auto ev : event) {
        if (cur > 0) res -= ev.first - last;
        last = ev.first; cur += ev.second;
    }
    cout << res << '\n';
}
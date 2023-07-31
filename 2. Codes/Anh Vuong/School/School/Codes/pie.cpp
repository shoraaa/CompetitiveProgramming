#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

const int N = 100005;

using ii = pair <int, int>;

int a[N][2], b[N][2], dis[N][2];
map <int, vector <int>> mp[2];
set <ii> sa, sb; queue <ii> q;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, d; cin >> n >> d;
    memset(dis, -1, sizeof dis);
    for (int i = 1; i <= n; i++) {
        cin >> a[i][0] >> a[i][1];
        if (a[i][1])
            sa.emplace(a[i][1], i);
        else {
            dis[i][1] = 1; q.emplace(i, 1);
        }
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i][0] >> b[i][1];
        if (b[i][0])
            sb.emplace(b[i][0], i);
        else {
            dis[i][0] = 1; q.emplace(i, 0);
        }
    }
    while (q.size()) {
        int i, t; tie(i, t) = q.front(); q.pop();
        if (t) {
            auto it = sb.lower_bound({a[i][0] - d, -1});
            while (it != sb.end() && it->fi <= a[i][0]) {
                dis[it->se][0] = dis[i][1] + 1;
                q.emplace(it->se, 0); it = sb.erase(it);
            }
        }
        else {
            auto it = sa.lower_bound({b[i][1] - d, -1});
            while (it != sa.end() && it->fi <= b[i][1]) {
                dis[it->se][1] = dis[i][0] + 1;
                q.emplace(it->se, 1); it = sa.erase(it);
            }
        }
    }
    for (int i = 1; i <= n; i++)
        cout << dis[i][1] << '\n';
}
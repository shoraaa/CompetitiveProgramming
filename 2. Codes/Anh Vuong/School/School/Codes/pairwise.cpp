#include <bits/stdc++.h>
using namespace std;

const int N = 505;
const int M = N * N;
const int LG = 18;

int a[M], b[N]; int bit[M];
vector <int> pos[M], cur[M];
map <int, int> id;

vector <vector <int>> ans;

void update(int i, int v) {
    for (; i < M; i += i & -i)
        bit[i] += v;
}

int get_pos(int k) {
    int p = 0;
    for (int b = LG - 1; ~b; b--)
        if (p + (1 << b) < M &&
        bit[p + (1 << b)] < k) {
            k -= bit[p + (1 << b)];
            p += 1 << b;    
        }
    return p + 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    int m = n * (n - 1) / 2;
    for (int i = 1; i <= m; i++)
        cin >> a[i];
    sort(a + 1, a + m + 1);
    int cnt = 0;
    for (int i = 1; i <= m; i++) {
        if (!id[a[i]]) id[a[i]] = ++cnt;
        cur[id[a[i]]].push_back(i);
    }
    int dif = 0;
    dif = a[2] - a[1];
    for (int i = 3; i <= n; i++) {
        if ((a[i] - dif) & 1) continue;
        b[2] = (a[i] - dif) / 2;
        b[3] = (a[i] + dif) / 2;
        b[1] = a[1] - b[2];
        for (int j = 3; j < i; j++)
            b[j + 1] = a[j] - b[1];
        for (int j = 1; j <= cnt; j++)
            pos[j] = cur[j];
        memset(bit, 0, sizeof bit);
        for (int j = 1; j <= m; j++)
            update(j, 1);
        bool flag = 1;
        vector <int> cur;
        for (int j = 1; j < i; j++)
            for (int k = j + 1; k <= i; k++) {
                int p = id[b[j] + b[k]];
                if (pos[p].empty()) goto kill;
                update(pos[p].back(), -1);
                pos[p].pop_back();
            }
        for (int j = i + 1; j <= n; j++) {
            int p = get_pos(1);
            b[j] = a[p] - b[1];
            for (int k = 1; k < j; k++) {
                p = id[b[j] + b[k]];
                if (pos[p].empty()) goto kill;
                update(pos[p].back(), -1);
                pos[p].pop_back();
            }
        }
        
        for (int j = 1; j <= n; j++)
            cur.push_back(b[j]);
        ans.push_back(cur); kill:;
    }
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(),
    ans.end()), ans.end());
    cout << ans.size() << '\n';
    for (int i = 0; i < n; i++)
        cout << ans[0][i] << ' ';
}
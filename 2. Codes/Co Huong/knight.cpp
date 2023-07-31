#include <bits/stdc++.h>

using namespace std;

#define fs first
#define sc second

const int MOD = 1e9 + 7;

using ll = long long;
using ii = pair<int, int>;

vector<ii> rec2, rec3;

ll C2(ll n) {
    if (n < 2) return 0;
    n %= MOD;
    return n * (n - 1) % MOD * 500000004 % MOD; 
}

ll C4(ll n) {
    if (n < 4) return 0;
    n %= MOD;
    return n * (n - 1) % MOD * (n - 2) % MOD * (n - 3) % MOD * 41666667 % MOD;
}

bool check(ii a, ii b) {
    int x = abs(a.fs - b.fs), y = abs(a.sc - b.sc);
    if ((x == 1 && y == 2) || (x == 2 && y == 1)) return true;
    return false;
}

void solve() {
    ll n, m; cin >> n >> m;
    if (n <= 1 || m <= 1) {
        cout << "0\n"; return;
    }
    /// số cách chọn 2 quân ăn nhau
    ll total_pair = ((n - 1) * (m - 2) + (n - 2) * (m - 1)) * 2;
    ll res = C4(n * m);
    /// số cách chọn 4 điểm mà có ít nhất 1 cặp ăn nhau
    res = (res - total_pair % MOD * C2(n * m - 2)) % MOD;
    ll cnt_2_pair = 0;
    for (auto r : rec2)
        cnt_2_pair += max(0ll, n - r.fs) * max(0ll, m - r.sc) % MOD;
    cnt_2_pair %= MOD;
    /// số cách chọn 4 điểm mà có ít nhất 2 cặp ăn nhau và 2 cặp có điểm chung
    res = (res + (n * m - 3) % MOD * cnt_2_pair) % MOD;
    /// số cách chọn 4 điểm mà có ít nhất 2 cặp ăn nhau và 2 cặp ko có điểm chung
    res = (res + C2(total_pair) - cnt_2_pair) % MOD;
    /// số cách chọn 4 điểm mà có ít nhất 3 cặp ăn nhau
    for (auto r : rec3) {
        res -= max(0ll, n - r.fs) * max(0ll, m - r.sc) % MOD;	
    }
    /// ko cần cộng số cách chọn có 4 điểm vì nó tự hủy với 1 cách chọn 3 cặp
    res = (res % MOD + MOD) % MOD;
    cout << res << '\n';
}

int main() {
    /// bao ham loai tru
    cin.tie(0)->sync_with_stdio(0);
    vector<pair<int, int>> a;
    /// sinh ra các cấu hình cần thiết
    /// rec2 là các cấu hình chọn 2 cặp có điểm chung
    /// rec3 là các cấu hình chọn 3 cặp
    for (int i = 0; i <= 6; i++)
        for (int j = 0; j <= 6; j++)
            a.emplace_back(i, j);
    for (int i = 0; i < a.size(); i++)
        for (int j = i + 1; j < a.size(); j++)
            for (int k = j + 1; k < a.size(); k++) {
                int cnt = check(a[i], a[j]);
                cnt += check(a[j], a[k]);
                cnt += check(a[k], a[i]);
                if (cnt == 2) {
                    if (min({a[i].fs, a[j].fs, a[k].fs}) == 0
                    && min({a[i].sc, a[j].sc, a[k].sc}) == 0)
                        rec2.emplace_back(max({a[i].fs, a[j].fs, a[k].fs}),
                                        max({a[i].sc, a[j].sc, a[k].sc}));
                        
                }
            }
    for (int i = 0; i < a.size(); i++)
        for (int j = i + 1; j < a.size(); j++)
            for (int k = j + 1; k < a.size(); k++)
                for (int l = k + 1; l < a.size(); l++) {
                    int cnt = check(a[i], a[j]);
                    cnt += check(a[i], a[k]);
                    cnt += check(a[i], a[l]);
                    cnt += check(a[j], a[k]);
                    cnt += check(a[j], a[l]);
                    cnt += check(a[k], a[l]);
                    if (min({a[i].fs, a[j].fs, a[k].fs, a[l].fs}) ||
                    min({a[i].sc, a[j].sc, a[k].sc, a[l].sc}))
                        continue;
                    if (cnt == 3) {     
                        rec3.emplace_back(max({a[i].fs, a[j].fs, a[k].fs, a[l].fs}),
                                        max({a[i].sc, a[j].sc, a[k].sc, a[l].sc})); 
                    } else if (cnt == 4) {
                        rec3.emplace_back(max({a[i].fs, a[j].fs, a[k].fs, a[l].fs}),
                                        max({a[i].sc, a[j].sc, a[k].sc, a[l].sc})); 
                        rec3.emplace_back(max({a[i].fs, a[j].fs, a[k].fs, a[l].fs}),
                                        max({a[i].sc, a[j].sc, a[k].sc, a[l].sc})); 
                        rec3.emplace_back(max({a[i].fs, a[j].fs, a[k].fs, a[l].fs}),
                                        max({a[i].sc, a[j].sc, a[k].sc, a[l].sc}));
                        /// 1 cách chọn 4 tự hủy với 1 cách chọn 3 nên ở đây chỉ push 3 lần
                    }
                }
    int t; cin >> t;
    while (t--) solve();
}
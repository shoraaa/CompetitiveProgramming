#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 10;
const int inf = 1e16 + 5;

int n, k, r, a[N];

vector <int> vec;
void compress() {
    vec.clear();
    for (int i = 1; i <= n; i++) {
        vec.push_back (a[i]);
        vec.push_back (a[i]-1);
    }
    vec.push_back (0);
    sort (vec.begin(), vec.end());
    vec.erase (unique (vec.begin(), vec.end()), vec.end());
}

int get_val(int x) {
    return lower_bound(vec.begin(), vec.end(), x) - vec.begin() + 1;
}

int sum[N], cnt[N];

int get_sum(int k) {
    int r = 0;
    for (; k > 0; k -= (k & -k)) r += sum[k];
    return r;
}

int get_cnt(int k) {
    int r = 0;
    for (; k > 0; k -= (k & -k)) r += cnt[k];
    return r;
}

void update(int k, int w) {
    for (; k <= 2 * n + 2; k += (k & -k)) sum[k] += w, cnt[k]++;
}

main() {
    ios :: sync_with_stdio (0);
    cin.tie (0);  cout.tie (0);

    freopen ("group.in", "r", stdin);
    freopen ("group.out", "w", stdout);

    int nTest; cin >> nTest;
    while (nTest--) {
        cin >> n >> k >> r;
        for (int i = 1; i <= n; i++)
            cin >> a[i];

        for (int i = 1; i <= 2 *n + 5; i++)
            cnt[i] = sum[i] = 0;

        compress();
        for (int i = 1; i <= r; i++)
            update (get_val(a[i]), a[i]);

        int prv = 0;
        for (int i = r + 1; i <= n; i++) {
            int res = 0;
            update (get_val(a[i]), a[i]);
            for (int low = prv, high = inf; low <= high; ) {
                int mid = (low + high) >> 1;
                int xxx = get_val (mid);
                int tong = get_sum (xxx) + (i - get_cnt(xxx)) * mid;
                if (tong >= k * mid) res = mid, low = mid + 1;
                else high = mid - 1;
            }
            cout << res << ' ';
            prv = res;
        }
        cout << '\n';
    }

    return 0;
}

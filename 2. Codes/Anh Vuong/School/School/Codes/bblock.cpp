#include <bits/stdc++.h>

using namespace std;

const int N = 200005;
const int K = 105;

bool pre[K][N], suf[K][N];
int sum[N], len[K], cnt[N];
char str[N];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int k; cin >> (str + 1) >> k;
    int n = strlen(str + 1);
    for (int i = 1; i <= k; i++) cin >> len[i];
    for (int i = 1; i <= n; i++) {
        cnt[i] = cnt[i - 1] + (str[i] != '_');
    }
    pre[0][-1] = suf[k + 1][n + 2] = 1;
    for (int i = 0; i <= n + 1; i++)
        if (str[i] != 'X') pre[0][i] = 1; else break;
    for (int i = n + 1; i >= 0; i--)
        if (str[i] != 'X') suf[k + 1][i] = 1; else break;
    for (int i = 1; i <= k; i++) {
        for (int j = len[i]; j <= n; j++) {
            if (cnt[j] - cnt[j - len[i]] == len[i]
            && str[j - len[i]] != 'X')
                pre[i][j] |= pre[i - 1][j - len[i] - 1];
            if (str[j] != 'X') pre[i][j] |= pre[i][j - 1];
        }
    }
    for (int i = k; i > 0; i--) {
        for (int j = n - len[i] + 1; j > 0; j--) {
            if (cnt[j + len[i] - 1] - cnt[j - 1] == len[i]
            && str[j + len[i]] != 'X')
                suf[i][j] |= suf[i + 1][j + len[i] + 1];
            if (str[j] != 'X') suf[i][j] |= suf[i][j + 1];
        }
    }
    for (int i = 1; i <= k; i++)
        for (int j = len[i]; j <= n; j++) {
            if (pre[i - 1][j - len[i] - 1] && suf[i + 1][j + 2]
            && str[j - len[i]] != 'X' && str[j + 1] != 'X'
            && cnt[j] - cnt[j - len[i]] == len[i]) {
                sum[j - len[i] + 1]++; sum[j + 1]--;
            }
        }
    for (int i = 1; i <= n; i++) {
        sum[i] += sum[i - 1];
        bool black = sum[i] > 0, white = 0;
        for (int j = 0; j <= k; j++)
            white |= pre[j][i - 1] && suf[j + 1][i + 1];
        if (str[i] == 'X') white = 0;
        if (black && white) cout << '?';
        else if (black) cout << 'X';
        else cout << '_';
    }
}
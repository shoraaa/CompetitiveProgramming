#include <cstdio>
#include <vector>
using namespace std;

int main() {
    freopen("ocell.in", "r", stdin);
    freopen("ocell.out", "w", stdout);
    
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);

    vector<vector<int>> A(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    vector<int> vr(n, -1), pr(n, -1);
    vector<int> vc(m, -1), pc(m, -1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (A[i][j] > vr[i]) {
                vr[i] = A[i][j];
                pr[i] = j;
            }
            if (A[i][j] > vc[j]) {
                vc[j] = A[i][j];
                pc[j] = i;
            }
        }
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
        if (A[i][pr[i]] == vc[pr[i]]) {
            ++ans;
        }
    }

    for (int i = 0; i < q; i++) {
        int r, c, x;
        scanf("%d %d %d", &r, &c, &x);
        --r, --c;
        A[r][c] = x;
        if (x > vr[r]) {
            ans -= vr[r] == vc[pr[r]];
            vr[r] = x;
            pr[r] = c;
        }
        if (x > vc[c]) {
            ans -= vc[c] == vr[pc[c]];
            vc[c] = x;
            pc[c] = r;
        }
        if (vr[r] == x && x == vc[c]) {
            ++ans;
        }
        printf("%d\n", ans);
    }
}

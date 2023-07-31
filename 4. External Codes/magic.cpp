#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000000 + 10;
const int MAXQ = 1000000 + 10;
const int NBIT = 30;
int n;
int a[MAXN];
int cnt[NBIT][2];
int n_col;
int res;

int get_bit(int x, int n) {
    return ((x >> n) & 1);
}

bool valid_col(int j) {
    return min(cnt[j][0], cnt[j][1]) == 0;
}

void update_col(int j, int a, int inc) {
    bool before = valid_col(j);
    int b = get_bit(a, j);
    cnt[j][b] += inc;
    bool after = valid_col(j);
    
    if (before != after) {
        if (before == true) n_col--;
        else {
            if (cnt[j][1] > 0) res |= (1 << j);
            else res &= (1 << NBIT) - 1 - (1 << j);
            n_col++;
        }
    }
    else {
        if (after == true) 
            if (cnt[j][1] > 0) res |= (1 << j);
            else res &= (1 << NBIT) - 1 - (1 << j); 
    }
    //cerr << j << " " << inc << " " << n_col << "\n";
}

void update_a(int p, int v, int inc) {
    for(int i = p - 1; i <= p + 1; i += 2) {
        if ((1 <= i) && (i <= n)) {
            int u = min(p, i);
            for(int j = NBIT - 1; j >= 0; --j) {
                if (get_bit(a[u], j) != get_bit(a[u + 1], j)) {
                    //cerr << p << " " << a[u] << " " << a[u + 1]  << " " << get_bit(a[u], j) << " " << cnt[j][get_bit(a[u], j)] << " " << inc << "\n";
                    update_col(j, a[u], inc);
                    break;
                }
            }
        }
    }
}

int main() {
    freopen("magic.in", "r", stdin);
    freopen("magic.out", "w", stdout);
    
    scanf("%d\n", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    
    for(int i = 1; i < n; ++i) {
        for(int j = NBIT - 1; j >= 0; --j)
            if (get_bit(a[i], j) != get_bit(a[i + 1], j)) {
                cnt[j][get_bit(a[i], j)]++;
                break;
            }
    }
    
    n_col = NBIT;
    for(int i = 0; i < NBIT; ++i) {
        if (valid_col(i) == false) {
            n_col--;
        }
        else if (cnt[i][1] > 0) res += (1 << i);
    }
    printf("%d\n", (n_col == NBIT ? res : -1));
    int q;
    scanf("%d\n", &q);
    for(int i = 1; i <= q; ++i) {
        int p, v;
        scanf("%d %d\n", &p, &v);
        update_a(p, a[p], -1);
        a[p] = v;
        update_a(p, v, 1);
        printf("%d\n", (n_col == NBIT ? res : -1));
    }
}
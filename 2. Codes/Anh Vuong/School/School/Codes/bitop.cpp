/// op_range(i, j) = op(a[i], a[i + 1], ..., a[j])
/// count number of pair {i, j} such that
/// i) and_range(i, j) = x
/// ii) or_range(i, j) = x
/// iii) xor_range(i, j) = x

/// idea:
/// i) a & b = c => c <= a => decreasing => binary search or 2-pointers work
/// ii) similar to i), note that it is increasing
/// iii) the linearity of xor operator, a ^ b = c <=> b = a ^ c

#include <bits/stdc++.h>
using namespace std;

#define ctz __builtin_ctz
#define clz __builtin_clz

using ll = long long;
const int N = 1e5 + 5;
int spt[18][N], n, x;
map <int, int> mp;

void build_spt(function <int(int, int)> op){
    for (int k = 1, p = 1; k <= 17; k++, p <<= 1)
        for (int i = 1; i + (p << 1) <= n + 1; i++)
            spt[k][i] = op(spt[k - 1][i], spt[k - 1][i + p]);
}

int query(int i, int j, function <int(int, int)> op){
    int k = 31 - clz(j - i + 1);
    return op(spt[k][i], spt[k][j + 1 - (1 << k)]);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n; ll cntand, cntor, cntxor;
    for (int i = 1; i <= n; i++) cin >> spt[0][i];
    auto andop = [&](int p, int q){return p & q;};
    auto orop = [&](int p, int q){return p | q;};
    cntand = 0; build_spt(andop); cin >> x;
    for (int i = 1, j = 1, k = 1; i <= n; i++){
        j = max(j, i); k = max(j, k);
        int p = j > i ? query(i, j - 1, andop) : -1;
        int q = k > i ? query(i, k - 1, andop) : -1;
        while (((p & spt[0][j]) & x) == x &&
            (p & spt[0][j]) != x && j <= n)
            p &= spt[0][j++];
        while (((q & spt[0][k]) & x) == x && k <= n)
            q &= spt[0][k++];
        cntand += k - j;
    }
    cntor = 0; build_spt(orop);
    for (int i = 1, j = 1, k = 1; i <= n; i++){
        j = max(j, i); k = max(j, k);
        int p = j > i ? query(i, j - 1, orop) : 0;
        int q = k > i ? query(i, k - 1, orop) : 0;
        while (((p | spt[0][j]) & x) == (p | spt[0][j])
            && (p | spt[0][j]) != x && j <= n)
            p |= spt[0][j++];
        while (((q | spt[0][k]) & x) == (q | spt[0][k])
            && k <= n) q |= spt[0][k++];
        cntor += k - j;
    }
    mp[0] = 1; cntxor = 0;
    for (int i = 1, cur = 0; i <= n; i++){
        cur ^= spt[0][i];
        cntxor += mp[cur ^ x];
        mp[cur]++; 
    }
    cout << cntand << '\n';
    cout << cntor << '\n';
    cout << cntxor << '\n';
}
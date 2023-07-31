#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool chkmax(X &a, const Y &b){
    return a < b ? a = b, 1 : 0;
}

struct item{
    int w, t, v, l;
};

const int N = 105;
int dp[N][N * N]; item a[N];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, s; cin >> n >> s;
    for (int i = 1; i <= n; i++){
        cin >> a[i].w >> a[i].t >> a[i].v >> a[i].l;
    }
    int sumw = 0, sumt = 0, res = 0;
    sort(a + 1, a + n + 1,
    [&](item p, item q){
        return p.t * q.l < p.l * q.t;
    });
    for (int i = 1; i <= n; i++){
        sumw += a[i].w; sumt += a[i].t;
        for (int j = min(sumw, s); j >= a[i].w; j--)
            for (int k = sumt; k >= a[i].t; k--)
                chkmax(dp[j][k], dp[j - a[i].w][k - a[i].t] +
                        a[i].v - (k - a[i].t) * a[i].l);
    }
    for (int j = 0; j <= min(sumw, s); j++)
        for (int k = 0; k <= sumt; k++)
            chkmax(res, dp[j][k]);
    cout << res << '\n';
}

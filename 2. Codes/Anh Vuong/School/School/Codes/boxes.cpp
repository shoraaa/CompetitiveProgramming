#include <bits/stdc++.h>
using namespace std;

struct item{
    int w, c;
};

using ll = long long;
const int N = 5005;
const ll inf = 0x3f3f3f3f3f3f3f3f;
item a[N]; ll dp[N];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].c >> a[i].w;
    sort(a + 1, a + n + 1,
    [&](item p, item q){
        return p.w + p.c < q.w + q.c;
    });
    memset(dp, 0x3f, sizeof dp); dp[0] = 0;
    for (int i = 1; i <= n; i++){
        for (int j = i; j > 0; j--)
            if (dp[j - 1] <= a[i].c)
                dp[j] = min(dp[j], dp[j - 1] + a[i].w);
    }
    for (int i = n; i > 0; i--)
        if (dp[i] < inf){
            cout << i << '\n'; break;
        }
}

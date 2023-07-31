#include <bits/stdc++.h>
using namespace std;
#define int long long
#define II pair <int, int>
#define fi first
#define se second
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define FOD(i, a, b) for(int i = a; i >= b; i--)
#define fast_machine ios ::sync_with_stdio(0), cin.tie(0), cout.tie(0)

const int N = 4005;
string a, b;
string tmp;
int f[N][N], l[N][N], m, n, res = 0;

void in() {
    cin >> a >> b;
    tmp = b;
    m = a.size(), n = b.size();
    a = ' ' + a, b = ' ' + b;
    FOD(i, m, 1) FOD(j, n, 1){
        if(a[i] == b[j]){
            l[i][j] = l[i + 1][j + 1] + 1;
            int t = l[i][j];
            f[i][j + t - 1] = max(f[i][j + t - 1], t);
        }
    }
    FOR(i, 1, m) FOR(j, 1, n){
        res = max(res, l[i][j] + f[i + l[i][j]][j - 1]);
    }
}

void process() {
    b = tmp;
    reverse(b.begin(), b.end());
    memset(l, 0, sizeof(l));
    memset(f, 0, sizeof(f));
    b = ' ' + b;
    FOD(i, m, 1) FOD(j, n, 1){
        if(a[i] == b[j]){
            l[i][j] = l[i + 1][j + 1] + 1;
            int t = l[i][j];
            f[i][j + t - 1] = max(f[i][j + t - 1], t);
        }
    }
    FOR(i, 1, m) FOR(j, 1, n){
        res = max(res, l[i][j] + f[i + l[i][j]][j - 1]);
    }
    cout << res;
}

#undef int
int main() {
    freopen("trim.in", "r", stdin);
    freopen("trim.out", "w", stdout);
    
    fast_machine;
    #define int long long
    in();
    process();
}

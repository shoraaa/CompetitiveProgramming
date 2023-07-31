#include    <bits/stdc++.h>
#define fo(i,a,b) for(int i=(a);i<=(b);++i)
#define fd(i,a,b) for(int i=(a);i>=(b);--i)
#define rep(i,a,b)  for(int i=(a);i<(b);++i)
#define fi  first
#define se  second
#define LL  unsigned long long
#define uint unsigned int
#define pb  push_back
#define eb  emplace_back
#define bit(s,i) ((s >> i) & 1)
#define off(s,i) (s & (~ (1 << i)))
#define ii pair <int , int>
#define iii1 pair <ii , int>
#define iii2 pair <int , ii>
#define TASK "AROBOT"
using   namespace   std;
const long long inf = 1e15;
const int oo = 0x3f;
int n , m , r;
long long dp[10][10][505][505];
ii null , f[505][505][4];
bool vs[505][505][4];
string s[505];
int dx[] = { 0 , -1 , 0 , 1};
int dy[] = { 1 , 0 , -1 , 0};
///--------------------------
ii F(int x,int y,int direct) {
    if (f[x][y][direct] != null) return f[x][y][direct];
    ii &res = f[x][y][direct];
    if (vs[x][y][direct]) {
        res = ii(x,y);
        return res;
    }
    vs[x][y][direct] = true;
    if (s[x][y] != 'A' && s[x][y] != 'C') {
        int nx = x + dx[direct] , ny = y + dy[direct];
        if (s[nx][ny] == 'x' || nx < 1 || nx > m || ny < 1 || ny > n) res = ii(x , y);
        else res = F(nx , ny , direct);
    } else {
        int ndirect = direct;
        if (s[x][y] == 'A') ndirect++;
        else ndirect--;
        ndirect = (ndirect + 4) % 4;
        int nx = x + dx[ndirect] , ny = y + dy[ndirect];
        if (nx < 1 || nx > m || ny < 1 || ny > n || s[nx][ny] == 'x') res = ii(x,y);
        else res = F(nx , ny , ndirect);
    }
    vs[x][y][direct] = false;
    return res;
}
///--------------------------
void readf() {
    cin >> r >> n >> m ;
    for (int i = 1 ; i <= m ; ++i) {
        cin >> s[i];
        s[i] = " " + s[i];
    }
}
///--------------------------
void solve() {
    for (int i = 1 ; i <= r ; ++i)
    for (int j = 1 ; j <= r ; ++j)
    for (int x = 1 ; x <= m ; ++x)
    for (int y = 1 ; y <= n ; ++y) dp[i][j][x][y] = inf;
    for (int i = 1 ; i <= m ; ++i)
    for (int j = 1 ; j <= n ; ++j) {
        if (s[i][j] != 'x') {
            for (int k = 0 ; k < 4 ; ++k)
            if (f[i][j][k] == null) f[i][j][k] = F(i , j , k);
        }
        if ('1' <= s[i][j] && s[i][j] <= '9') dp[s[i][j] - '0'][s[i][j] - '0'][i][j] = 0;
    }
    for (int d = 0 ; d < r ; ++d)
    for (int i = 1 ; i <= r - d ; ++i) {
        vector < iii2 > wa;
        int j = i + d;
        for (int x = 1 ; x <= m ; ++x)
        for (int y = 1 ; y <= n ; ++y) {
            for (int k = i ; k < j ; ++k)
            dp[i][j][x][y] = min(dp[i][j][x][y] , dp[i][k][x][y] + dp[k+1][j][x][y]);
            if (dp[i][j][x][y] < inf) wa.pb({dp[i][j][x][y] , {x , y}});
        }
        stack < iii2 > stk , pa;
        sort(wa.rbegin(),wa.rend());
        for (auto x : wa) stk.push(x);
        while (!stk.empty()) {
            int val = stk.top().fi;
            while (!stk.empty() && stk.top().fi == val) {
                pa.push(stk.top());
                stk.pop();
            }
            while (!pa.empty()) {
                int x = pa.top().se.fi , y = pa.top().se.se;
                pa.pop();
                for (int k = 0 ; k < 4 ; ++k) {
                    int nx = f[x][y][k].fi , ny = f[x][y][k].se;
                    if (nx == x && ny == y) continue;
                    if (dp[i][j][nx][ny] > val + 1) {
                        dp[i][j][nx][ny] = val + 1;
                        stk.push({val + 1 , f[x][y][k]});
                    }
                }
            }
        }
    }
    long long ans = inf;
    for (int i = 1 ; i <= m ; ++i)
    for (int j = 1 ; j <= n ; ++j) ans = min(ans , dp[1][r][i][j]);
    if (ans < inf) cout << ans;
    else cout << -1;
}
///--------------------------
int main() {
       freopen(TASK".inp", "r", stdin);
       freopen(TASK".out", "w", stdout);
   ios::sync_with_stdio(0);
   cin.tie(0);cout.tie(0);
   readf();
   solve();
}


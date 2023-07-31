#include<bits/stdc++.h>
using namespace std;
const int N = 1e2 + 5;
const int MOD = 1e9 + 7;

int r, c, n;
int b[N][N], a[N][N], s[N][N], p[15];
int f[N][N][15];

int get(int x, int y, int u, int v){
    return s[u][v] - s[u][y-1] - s[x-1][v] + s[x-1][y-1];
}

int add(int a, int b){
    a += b;
    if ( a >= MOD ) a -= MOD;
    if ( a < 0 ) a += MOD;
    return a;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    if ( fopen("trash.inp", "r") ){
        freopen("trash.inp", "r", stdin);
        freopen("trash.out", "w", stdout);
    }

    cin >> r >> c >> n;
    for (int i = 1; i <= r; i ++)
    for (int j = 1; j <= c; j ++)
        cin >> b[i][j];

    for (int i = 1; i <= r; i ++)
    for (int j = 1; j <= c; j ++)
        a[i][j] = b[r-i+1][c-j+1];

    for (int i = 1; i <= n; i ++)
        cin >> p[i];

    for (int i = 1; i <= r; i ++)
    for (int j = 1; j <= c; j ++)
        s[i][j] = s[i-1][j] + s[i][j-1] + a[i][j] - s[i-1][j-1];

    reverse(p + 1, p + 1 + n);

    for (int i = 1; i <= r; i ++)
    for (int j = 1; j <= c; j ++)
        if ( s[i][j] <= p[1] )
            f[i][j][1] = 1;

    for (int i = 1; i <= r; i ++)
    for (int j = 1; j <= c; j ++)
    for (int k = 1; k < n; k ++) if ( f[i][j][k]){
        // cut hor
        for (int ii = i + 1; ii <= r; ii ++)
            if ( get(i+1, 1, ii, j) <= p[k+1] && ii && j )
                f[ii][j][k+1] = add(f[ii][j][k+1], f[i][j][k]);

        // cut ver
        for (int jj = j + 1; jj <= c; jj ++)
            if ( get(1, j+1, i, jj) <= p[k+1] && i && jj )
                f[i][jj][k+1] = add(f[i][jj][k+1], f[i][j][k]);
    }

    cout << f[r][c][n];

    return 0;
}

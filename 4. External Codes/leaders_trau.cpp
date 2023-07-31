#include<bits/stdc++.h>
using namespace std;
#pragma GCC target ("avx2")
#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")
#define ll long long
#define fi first
#define se second
#define pb push_back
#define ld long double
#define pii pair <int, int>
#define piii pair <int, pair <int, int>>
void cmax(int& x, const int& y) {x = max(x, y);}
void cmin(int& x, const int& y) {x = min(x, y);}
int const nmax = 2003;
ll const INF = 1e12;
int const base = 2e9 + 1;
int n, m;
int adj[17][55], s[17];
ll ans = INF, res;
short p1[17], p2[17], id[17];
short p[17], pos;
bool ok;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> m >> n;
    for(short i = 1; i <= m; ++i)
    {
        cin >> id[i];
        for(short j = 1; j <= id[i]; ++j)
        {
            cin >> adj[i][j];
            if(s[i] > base - adj[i][j]) s[i] = base;
            else s[i] += adj[i][j];
        }
    }
    pos = 1;
    for(short i = 1; i <= m; ++i) p1[i] = p2[i] = i;
    while(pos > 0)
    {
        if(p[pos] == id[pos])
        {
            p[pos--] = 0;
            continue;
        }
        ++p[pos];
        if(pos == m)
        {
            sort(p1 + 1, p1 + 1 + m, [&](const short& x, const short& y)
            {
                return s[x] - adj[x][p[x]] < s[y] - adj[y][p[y]];
            });
            sort(p2 + 1, p2 + 1 + m, [&](const short& x, const short& y)
            {
                return adj[x][p[x]] < adj[y][p[y]];
            });
            ok = true; res = 0;
            for(short i = 1; i <= m; ++i)
                if(adj[p2[i]][p[p2[i]]] < s[p1[i]] - adj[p1[i]][p[p1[i]]])
                {
                    ok = false;
                    break;
                }
                else res += adj[p2[i]][p[p2[i]]];
            if(ok) ans = min(ans, res);
        }
        else ++pos;
    }
    if(ans == INF) cout << -1;
    else cout << ans;
    return 0;
}


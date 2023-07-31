#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 105;
const int M = 10005;
const int D = 55;

int n, m, mod;
int f[N][N][D], g[N][N][D]; 
vector <int> adj[N];

void madd(int &x, int y) {
    if ((x += y) >= mod) x -= mod;
}

void msub(int &x, int y) {
    if ((x -= y) < 0) x += mod;
}


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> mod;
    while (m--) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }
    for (int i = 1; i <= n; i++)
        f[i][i][0] = 1;
    for (int k = 0; k < D - 1; k++)
        for (int u = 1; u <= n; u++)
            for (int v = 1; v <= n; v++)
                for (int w : adj[v])
                    madd(f[u][w][k + 1], f[u][v][k]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k < D; k++)
                for (int u : {i, j})
                    for (int v : {i, j}) {
                        int cur = 0;
                        for (int w : {i, j})
                            for (int l = 1; l < k; l++)
                                madd(cur, ll(f[u][w][l])
                                * g[w][v][k - l] % mod);
                        g[u][v][k] = f[u][v][k];
                        msub(g[u][v][k], cur);
                    }
    int q; cin >> q;
    while (q--) {
        int u, v, d;
        cin >> u >> v >> d;
        cout << g[u][v][d] << '\n';
    }
}
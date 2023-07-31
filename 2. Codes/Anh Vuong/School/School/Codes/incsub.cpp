#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 3e5 + 5;
int in[N], out[N], dep[N], tim, n, q, a[N];
vector <int> adj[N]; ll bit[2][N];

void dfs(int u){
    in[u] = ++tim;
    for (int v : adj[u]){
        dep[v] = dep[u] + 1; dfs(v);
    }
    out[u] = tim;
}

void update(int id, int i, int val){
    for (; i <= n; i += i & -i)
        bit[id][i] += val;
}

ll query(int id, int i){
    ll res = 0;
    for (; i > 0; i -= i & -i)
        res += bit[id][i];
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; cin >> a[i++]);
    for (int i = 2, j; i <= n; i++){
        cin >> j; adj[j].push_back(i);
    }
    dfs(1);
    for (int i = 1; i <= n; i++){
        update(0, in[i], 2 * a[i]);
        update(0, in[i] + 1, -2 * a[i]);
    }
    char cmd; int u, t, c;
    while (q--){
        cin >> cmd >> u;
        if (cmd == '+'){
            cin >> t >> c;
            update(0, in[u], c);
            update(0, out[u] + 1, -c);
            if (t ^ (dep[u] & 1)){
                update(1, in[u], -c);
                update(1, out[u] + 1, c);
            }
            else {
                update(1, in[u], c);
                update(1, out[u] + 1, -c);
            }
        }
        else {
            ll res = query(0, in[u]);
            if (dep[u] & 1)
                res -= query(1, in[u]);
            else res += query(1, in[u]);
            cout << res / 2 << '\n';
        }
    }
}
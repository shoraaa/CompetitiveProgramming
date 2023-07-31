#include <bits/stdc++.h>
using namespace std;

#define popcnt __builtin_popcountll
using ll = long long;

const int N = 3e5 + 5;
int col[N], in[N], out[N], tim;
bitset <101> tree[4 * N], res;
vector <int> adj[N];

void dfs(int u){
    in[u] = ++tim;
    for (int v : adj[u]) dfs(v);
    out[u] = tim;
}

void update(int i, int lo, int hi, int p, int c){
    if (lo > p || hi < p) return;
    tree[i].flip(c);
    if (lo != hi){
        int mi = (lo + hi) / 2;
        update(i * 2, lo, mi, p, c);
        update(i * 2 + 1, mi + 1, hi, p, c);
    }
}

void query(int i, int lo, int hi, int l, int r){
    if (lo > r || hi < l) return;
    if (lo >= l && hi <= r){
        res ^= tree[i]; return;
    }
    int mi = (lo + hi) / 2;
    query(i * 2, lo, mi, l, r);
    query(i * 2 + 1, mi + 1, hi, l, r);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    for (int i = 1; i <= n; cin >> col[i++]);
    for (int i = 2, j; i <= n; i++){
        cin >> j; adj[j].push_back(i);
    }
    dfs(1); int k, u;
    for (int i = 1; i <= n; i++)
        update(1, 1, n, in[i], col[i]);
    while (q--){
        cin >> k >> u;
        if (k){
            update(1, 1, n, in[u], k);
            update(1, 1, n, in[u], col[u]);
            col[u] = k;
        }
        else {
            res.reset();
            query(1, 1, n, in[u], out[u]);
            cout << res.count() << '\n';
        }
    }
}
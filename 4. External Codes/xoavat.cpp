#include <bits/stdc++.h>

using namespace std;

const int base = 311;
const int maxn = 1e6 + 5;

map < long long , int > ha;
vector < int > vc[maxn];
int ma , h[maxn] , par[maxn] , a[maxn] , n , k;
long long hashs[maxn] , pw[maxn];
vector < int > g[maxn] , chl[maxn];
vector < vector < int > > res;
bool alive[maxn];

long long __get_hash(int i,int j) {
    if (i > j) return 0;
    return hashs[j] - hashs[i - 1] * pw[j - i + 1];
}

void DFS(int u) {
    alive[u] = 1;
    ma = max(ma , h[u]);
    vc[h[u]].push_back(u);
    for (auto v : g[u])
    if (!h[v]) {
        h[v] = h[u] + 1;
        par[v] = u;
        chl[u].push_back(v);
        DFS(v);
    }
}

int main() {
    freopen("xoavat.inp","r",stdin);
    freopen("xoavat.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    pw[0] = 1;
    for (int i = 1 ; i <= k ; ++i) pw[i] = pw[i - 1] * base;
    for (int i = 1 ; i <= n ; ++i) {
        for (int j = 1 ; j <= k ; ++j) {
            cin >> a[j];
            hashs[j] = (hashs[j - 1] * base + a[j] - 'a' + 1);
        }
        for (int j = 1 ; j <= k ; ++j) {
            long long cur = hashs[j - 1];
            cur = (cur * base + a[j] - 1 - 'a' + 1);
            cur = (cur * pw[k - j] + __get_hash(j + 1 , k));
            if (ha.find(cur) != ha.end()) {
                int j = ha[cur];
                g[i].push_back(j);
                g[j].push_back(i);
            }
            cur = (hashs[j - 1] * base + a[j] + 1 - 'a' + 1);
            cur = (cur * pw[k - j] + __get_hash(j + 1 , k));
            if (ha.find(cur) != ha.end()) {
                int j = ha[cur];
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
        ha[hashs[k]] = i;
    }
    vector < int > cur;
    for (int root = 1 ; root <= n ; ++root)
    if (!h[root]) {
        h[root] = 1;
        ma = 1;
        DFS(root);
        int cnt = chl[root].size();
        if (ma == 1) {
            cout << -1;
            exit(0);
        }
        for (int i = ma ; i > 1 ; --i) {
            for (auto u : vc[i])
            if (alive[u]) {
                int p = par[u];
                if (p == root) continue;
                if (par[p] == root && cnt == 1) {
                    cur.push_back(p);
                    alive[p] = 0;
                    cur.push_back(root);
                    alive[root] = 0;
                    for (auto v : chl[p])
                    if (alive[v]) {
                        cur.push_back(v);
                        alive[v] = 0;
                    }
                    res.push_back(cur);
                    cur.clear();
                    cnt = 0;
                    continue;
                }
                cnt -= (par[p] == i);
                vector < int > cur;
                cur.push_back(p);
                alive[p] = 0;
                for (auto v : chl[p])
                if (alive[v]) {
                    cur.push_back(v);
                    alive[v] = 0;
                }
                res.push_back(cur);
                cur.clear();
            }
        }
        if (alive[root]) {
            cur.push_back(root);
            alive[root] = 0;
            for (auto v : chl[root])
            if (alive[v]) {
                cur.push_back(v);
                alive[v] = 0;
            }
            res.push_back(cur);
            cur.clear();
        }
    }
    cout << res.size() << '\n';
    for (auto x : res) {
        cout << x.size() << ' ';
        for (auto v : x) cout << v << ' ';
        cout << '\n';
    }
}

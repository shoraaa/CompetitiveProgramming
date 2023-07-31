#include <bits/stdc++.h>
using namespace std;

namespace dinic {
    const int inf = INT_MAX;
 
    vector <int> head, dis, work;
    vector <int> to, nxt, capa, flow;
    int n; queue <int> q;
 
    void init(int n) {
        dinic::n = n;
        head.assign(n + 5, -1);
        dis.assign(n + 5, 0);
        work.assign(n + 5, 0);
        to.clear(); nxt.clear();
        capa.clear(); flow.clear();
    }
 
    void add_edge(int u, int v, int c, bool r = 0) {
        to.push_back(v); nxt.push_back(head[u]);
        capa.push_back(c); flow.push_back(0);
        head[u] = to.size() - 1;
        to.push_back(u); nxt.push_back(head[v]);
        capa.push_back(c * r); flow.push_back(0);
        head[v] = to.size() - 1;
    }
 
    bool bfs(int s, int t) {
        fill(dis.begin(), dis.end(), -1);
        dis[s] = 0; q.push(s);
        while (q.size()) {
            int u = q.front(); q.pop();
            for (int i = head[u]; i >= 0; i = nxt[i])
                if (flow[i] < capa[i] && dis[to[i]] < 0) {
                    dis[to[i]] = dis[u] + 1; q.push(to[i]);
                }
        }
        return dis[t] >= 0;
    }
 
    int dfs(int s, int t, int f) {
        if (s == t) return f;
        for (int &i = work[s]; i >= 0; i = nxt[i])
            if (flow[i] < capa[i] && dis[to[i]] == dis[s] + 1) {
                int d = dfs(to[i], t, min(f, capa[i] - flow[i]));
                if (d > 0) {
                    flow[i] += d; flow[i ^ 1] -= d; return d;
                }
            }
        return 0;
    }
 
    int max_flow(int s, int t) {
        int res = 0, aug;
        while (bfs(s, t)) {
            copy(head.begin(), head.end(), work.begin());
            while ((aug = dfs(s, t, inf)) > 0) res += aug;
        }
        return res;
    }
};

const int N = 55;

char s[N][N]; int n;

int id(int i, int j, int t) {
    return (i - 1) * n + j + t * n * n;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n; int sink = 0, src;
    for (int i = 1; i <= n; i++)
        cin >> (s[i] + 1);
    dinic::init(id(n, n, 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if (s[i][j] == 'b') {
                dinic::add_edge(id(i, j, 1), 0, n * n);
                dinic::add_edge(id(i, j, 0), id(i, j, 1), n * n);
            }
            else if (s[i][j] == '$') {
                dinic::add_edge(id(i, j, 0), id(i, j, 1), n * n);
                src = id(i, j, 0);
            }
            else dinic::add_edge(id(i, j, 0), id(i, j, 1), s[i][j] != 'H');
            if (i + 3 <= n) {
                if (s[i + 1][j] == '$' || s[i + 1][j] == 'b'
                || s[i + 2][j] == '$' || s[i + 2][j] == 'b')
                    dinic::add_edge(id(i, j, 1), id(i + 3, j, 0), n * n);
                else dinic::add_edge(id(i, j, 1), id(i + 3, j, 0),
                (s[i + 1][j] != 'H') + (s[i + 2][j] != 'H'));
            }
            if (j + 3 <= n) {
                if (s[i][j + 1] == '$' || s[i][j + 1] == 'b'
                || s[i][j + 2] == '$' || s[i][j + 2] == 'b')
                    dinic::add_edge(id(i, j, 1), id(i, j + 3, 0), n * n);
                else dinic::add_edge(id(i, j, 1), id(i, j + 3, 0),
                (s[i][j + 1] != 'H') + (s[i][j + 2] != 'H'));    
            }
            if (i - 3 > 0) {
                if (s[i - 1][j] == '$' || s[i - 1][j] == 'b'
                || s[i - 2][j] == '$' || s[i - 2][j] == 'b')
                    dinic::add_edge(id(i, j, 1), id(i - 3, j, 0), n * n);
                else dinic::add_edge(id(i, j, 1), id(i - 3, j, 0),
                (s[i - 1][j] != 'H') + (s[i - 2][j] != 'H'));
            }
            if (j - 3 > 0) {
                if (s[i][j - 1] == '$' || s[i][j - 1] == 'b'
                || s[i][j - 2] == '$' || s[i][j - 2] == 'b')
                    dinic::add_edge(id(i, j, 1), id(i, j - 3, 0), n * n);
                else dinic::add_edge(id(i, j, 1), id(i, j - 3, 0),
                (s[i][j - 1] != 'H') + (s[i][j - 2] != 'H'));     
            }
        }
    int res = dinic::max_flow(src, sink);
    cout << (res == n * n ? -1 : res) << '\n';
}
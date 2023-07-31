#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 5;
const long long INF = 1e15;

struct Edge {
    int u,v,c,f,w;
};

typedef pair <long long, int> pii;

vector <int> adj[MAX_N];
Edge edge[MAX_N * 4];
int trace[MAX_N];
long long d[MAX_N], p[MAX_N];

long long wp(int id){
    return edge[id].w + p[edge[id].u] - p[edge[id].v];
}

void ijk(int s, int t, int n){
    fill(d + 1, d + n + 1, INF);

    priority_queue <pii, vector <pii>, greater <pii>> pq;

    pq.push({0, s});
    d[s] = 0;

    while(pq.size()){
        int u = pq.top().second;
        long long du = pq.top().first;
        pq.pop();

        if(du != d[u]) continue;

        for(auto & id : adj[u]){
            int v = edge[id].v;

            if (edge[id].f == edge[id].c)
                continue;

            //cout << u << ' ' << v << '\n';

            if(edge[id].f != edge[id].c && d[v] > d[u] + wp(id)){
                d[v] = d[u] + wp(id);
                trace[v] = id;
                pq.push({d[v], v});
            }
        }
    }

    for(int i = 1; i <= n; i++)
        p[i] += d[i];
}

void get(int s, int t, int n){
    int delta = INT_MAX;
    int v = t;
    while(v != s){
        int id = trace[v];
        delta = min(delta, edge[id].c - edge[id].f);
        v = edge[id].u;
    }

    v = t;
    while(v != s){
        int id = trace[v];
        edge[id].f += delta;
        edge[id ^ 1].f -= delta;
        v = edge[id].u;
    }
}

long long res = 0;

vector <int> path(int s, int t){
    vector <int> p;

    int u = s;
    p.push_back(s);

    while(u != t){
        for(auto & id : adj[u]){
            int v = edge[id].v;
            if(edge[id].f == 1){
                //cout << 1;
                res += edge[id].w;
                edge[id].f = 0;
                u = v;
                break;
            }
        }

        p.push_back(u);
    }

    return p;
}

vector <int> path1, path2;

int main(){
    freopen("walk.inp", "r", stdin);
    freopen("walk.out", "w", stdout);

    int n,m;
    cin >> n >> m;
    for(int i = 1, u,v,w,id = 0; i <= m; i++){
        cin >> u >> v >> w;
        adj[u].push_back(id);
        edge[id++] = {u, v, 1, 0, w};
        adj[v].push_back(id);
        edge[id++] = {v, u, 0, 0, -w};
        adj[v].push_back(id);
        edge[id++] = {v, u, 1, 0, w};
        adj[u].push_back(id);
        edge[id++] = {u, v, 0, 0, -w};
    }

    for(int i : {1, 2}){
        ijk(1, n, n);
        get(1, n, n);
    }

 //   for(int i = 1; i <= n; i++)
//        cout << d[i] << ' ';

    path1 = path(1, n);
    path2 = path(1, n);

    if(path1.back() != n || path2.back() != n){
        cout << -1;
        return 0;
    }

    path1.pop_back();
    reverse(path2.begin(), path2.end());

    cout << res << '\n';
    for(auto & it : path1)
        cout << it << ' ';
    for(auto & it : path2)
        cout << it << ' ';
    return 0;
}

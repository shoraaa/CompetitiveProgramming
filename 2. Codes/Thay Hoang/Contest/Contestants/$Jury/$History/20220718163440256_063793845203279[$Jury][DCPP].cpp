#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
const int maxN = 1e3 + 1;
const int maxM = 1e4;
const int maxW = 1e6;
const int infty = maxN * maxW;

struct TEdge
{
    int x, y, c, f, w;
};

int n, m;
TEdge e[2 * maxM];
vector<int> adj[maxN];
int deg[maxN]; //bậc vào - bậc ra
vector<int> x;
int trace[maxN];

int d[maxN], p[maxN];
struct TPQItem
{
    int u, dlab;
    inline bool Valid() const
    {
        return d[u] == dlab;
    }
    inline operator < (const TPQItem& other) const
    {
        return dlab > other.dlab;
    }
};

void ReadInput()
{
    cin >> n >> m;
    fill(deg + 1, deg + n + 1, 0);
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        deg[v]++;
        deg[u]--;
        e[i * 2] = {u, v, m, 0, w};
        e[i * 2 + 1] = {v, u, 0, 0, -w};
    }
    for (int i = 0; i < 2 * m; ++i)
        adj[e[i].x].push_back(i);
}

void Init()
{
    for (int i = 1; i <= n; ++i)
        if (deg[i] > 0) x.push_back(i);
    fill(p + 1, p + n + 1, 0);
}

inline int cf(const TEdge& e)
{
    return e.c - e.f;
}

inline int wp(const TEdge& e)
{
    return e.w + p[e.x] - p[e.y];
}

inline bool Minimize(int& Target, int Value)
{
    if (Value < Target)
    {
        Target = Value;
        return true;
    }
    return false;
}

int Dijkstra()
{
    int res = -1;
    priority_queue<TPQItem> PQ;
    fill(d + 1, d + n + 1, infty);
    for (int u: x)
    {
        d[u] = 0;
        PQ.push({u, 0});
    }
    while (!PQ.empty())
    {
        TPQItem item = PQ.top(); PQ.pop();
        if (!item.Valid()) continue;
        int u = item.u;
        if (deg[u] < 0 && res == -1) res = u;
        for (int i: adj[u])
        {
            int v = e[i].y;
            if (cf(e[i]) == 0) continue;
            if (Minimize(d[v], d[u] + wp(e[i])))
            {
                trace[v] = i;
                PQ.push({v, d[v]});
            }
        }
    }
    return res;
}

void AugmentFlow(int t)
{
    int s = t;
    while (deg[s] <= 0)
    {
        int i = trace[s];
        s = e[i].x;
    }
    int fvalue = min(deg[s], -deg[t]);
    int u = t;
    while (u != s)
    {
        int i = trace[u];
        e[i].f += fvalue;
        e[i ^ 1].f -= fvalue;
        u = e[i].x;
    }
    deg[s] -= fvalue;
    deg[t] += fvalue;
    if (deg[s] == 0)
    {
        for (int& u: x)
            if (u == s)
            {
                u = x.back();
                x.pop_back();
                break;
            }
    }
}

void Solve()
{
    while (true)
    {
        if (x.empty()) break;
        int t = Dijkstra();
        AugmentFlow(t);
        for (int i = 1; i <= n; ++i)
            p[i] += d[i];
    }
    long long Result = 0;
    for (int i = 0; i < 2 * m; ++i)
    {
        if (e[i].w > 0) Result += e[i].w;
        if (e[i].f > 0)
            Result += (long long) e[i].f * e[i].w;
    }
    cout << Result;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("DCPP.INP", "r", stdin);
    freopen("DCPP.OUT", "w", stdout);
    ReadInput();
    Init();
    Solve();
}

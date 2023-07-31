#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
using lli = long long;
const lli maxN = 1e3 + 1;
const lli maxM = 1e4;
const lli maxW = 1e6;
const lli infty = maxN * maxW;

struct TEdge
{
    lli x, y, c, f, w;
};

lli n, m;
TEdge e[2 * maxM];
vector<lli> adj[maxN];
lli deg[maxN]; //bậc vào - bậc ra
vector<lli> x;
lli trace[maxN];

lli d[maxN], p[maxN];
struct TPQItem
{
    lli u, dlab;
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
    for (lli i = 0; i < m; ++i)
    {
        lli u, v, w;
        cin >> u >> v >> w;
        deg[v]++;
        deg[u]--;
        e[i * 2] = {u, v, m, 0, w};
        e[i * 2 + 1] = {v, u, 0, 0, -w};
    }
    for (lli i = 0; i < 2 * m; ++i)
        adj[e[i].x].push_back(i);
}

void Init()
{
    for (lli i = 1; i <= n; ++i)
        if (deg[i] > 0) x.push_back(i);
    fill(p + 1, p + n + 1, 0);
}

inline lli cf(const TEdge& e)
{
    return e.c - e.f;
}

inline lli wp(const TEdge& e)
{
    return e.w + p[e.x] - p[e.y];
}

inline bool Minimize(lli& Target, lli Value)
{
    if (Value < Target)
    {
        Target = Value;
        return true;
    }
    return false;
}

lli Dijkstra()
{
    lli res = -1;
    priority_queue<TPQItem> PQ;
    fill(d + 1, d + n + 1, infty);
    for (lli u: x)
    {
        d[u] = 0;
        PQ.push({u, 0});
    }
    while (!PQ.empty())
    {
        TPQItem item = PQ.top(); PQ.pop();
        if (!item.Valid()) continue;
        lli u = item.u;
        if (deg[u] < 0 && res == -1) res = u;
        for (lli i: adj[u])
        {
            lli v = e[i].y;
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

void AugmentFlow(lli t)
{
    lli s = t;
    while (deg[s] <= 0)
    {
        lli i = trace[s];
        s = e[i].x;
    }
    lli fvalue = min(deg[s], -deg[t]);
    lli u = t;
    while (u != s)
    {
        lli i = trace[u];
        e[i].f += fvalue;
        e[i ^ 1].f -= fvalue;
        u = e[i].x;
    }
    deg[s] -= fvalue;
    deg[t] += fvalue;
    if (deg[s] == 0)
    {
        for (lli& u: x)
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
        lli t = Dijkstra();
        AugmentFlow(t);
        for (lli i = 1; i <= n; ++i)
            p[i] += d[i];
    }
    long long Result = 0;
    for (lli i = 0; i < 2 * m; ++i)
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

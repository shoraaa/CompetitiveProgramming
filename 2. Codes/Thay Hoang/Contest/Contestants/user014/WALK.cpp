#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
using lli = long long;
const lli Infty = 2e14;
const int maxN = 1e5 + 1;
const int maxM = 4e5 + 1;

struct TEdge
{
    int x, y, c, f;
    int w;
};

int n, m;
TEdge e[maxM];
vector<int> adj[maxN];
lli p[maxN], d[maxN];
int trace[maxN];

struct TPQItem
{
    int v;
    lli dlab;
    inline bool Valid() const
    {
        return d[v] == dlab;
    }
    inline operator < (const TPQItem& other) const
    {
        return dlab > other.dlab;
    }
};

void ReadInput()
{
    cin >> n >> m;
    int j = 0;
    for (; m > 0; m--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        e[j++] = {u, v, 1, 0, w};
        e[j++] = {v, u, 0, 0, -w};
        e[j++] = {v, u, 1, 0, w};
        e[j++] = {u, v, 0, 0, -w};
    }
    m = j;
    for (int i = 0; i < m; ++i)
        adj[e[i].x].push_back(i);
    fill(p + 1, p + n + 1, 0);
}

inline int cf(const TEdge& e)
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

void Dijkstra()
{
    fill(d + 1, d + n + 1, Infty);
    d[1] = 0;
    priority_queue<TPQItem> PQ;
    PQ.push({1, 0});
    while (!PQ.empty())
    {
        TPQItem item = PQ.top();
        PQ.pop();
        if (!item.Valid()) continue;
        int u = item.v;
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
    for (int i = 1; i <= n; ++i)
        p[i] += d[i];
}

void AugmentFlow()
{
    int u = n;
    while (u != 1)
    {
        int i = trace[u];
        e[i].f++;
        e[i ^ 1].f--;
        u = e[i].x;
    }
}

void FindPath(vector<int>&x, lli& weight)
{
    x.clear();
    weight = 0;
    int u = 1;
    x.push_back(1);
    while (true)
    {
        for (int i : adj[u])
            if (e[i].f == 1)
            {
                u = e[i].y;
                e[i].f = 0;
                weight += e[i].w;
                break;
            }
        x.push_back(u);
        if (u == n) break;
    }
}

void Solve()
{
    for (int step = 0; step < 2; ++step)
    {
        Dijkstra();
        if (d[n] == Infty)
        {
            cout << -1;
            return;
        }
        AugmentFlow();
    }
    vector<int> Path1, Path2;
    lli w1, w2;
    FindPath(Path1, w1);
    FindPath(Path2, w2);
    Path1.pop_back();
    reverse(Path2.begin(), Path2.end());
    cout << w1 + w2 << '\n';
    for (int u: Path1) cout << u << ' ';
    for (int u: Path2) cout << u << ' ';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("WALK.INP", "r", stdin);
    freopen("WALK.OUT", "w", stdout);
    ReadInput();
    Solve();
}
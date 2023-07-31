#define taskname "WALK"
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
const int maxN = 1e5 + 1;
const int maxM = 1e5 + 1;
const int maxW = 2e9;
typedef long long lli;
const lli maxD = lli(maxW) * maxN;
struct TEdge
{
    int u, v, w;
    bool selected;
};
typedef pair<int, lli> TPQRec;
struct Cmp
{
    inline bool operator()(const TPQRec& a, const TPQRec& b) const
    {
        return a.second > b.second;
    }
};
TEdge e[2 * maxM];
vector<int> adj[maxN];
lli p[maxN], d[maxN];
int trace[maxN];
int n, m;
priority_queue<TPQRec, vector<TPQRec>, Cmp> pq;

void Enter()
{
    int ne;
    cin >> n >> ne;
    m = 0;
    for (; ne > 0; --ne)
    {
        int u, v, w;
        cin >> u >> v >> w;
        e[m++] = {u, v, w, false};
        e[m++] = {v, u, w, false};
    }
}

void Init()
{
    for (int i = 0; i < m; ++i)
        adj[e[i].u].push_back(i);
    fill(begin(p), end(p), 0);
}

inline lli wp(const TEdge& e)
{
    return e.w + p[e.u] - p[e.v];
}

int Extract()
{
    while (true)
    {
        if (pq.empty()) return - 1;
        TPQRec urec = pq.top();
        pq.pop();
        if (d[urec.first] == urec.second) return urec.first;
    }
}

bool Update(int v, lli newd)
{
    if (d[v] <= newd) return false;
    d[v] = newd;
    pq.emplace(v, newd);
    return true;
}

void Dijkstra()
{
    fill_n(d + 1, n, maxD);
    d[1] = 0;
    pq.emplace(1, 0);
    while (true)
    {
        int u = Extract();
        if (u == -1) break;
        for (int i: adj[u])
            if (!e[i].selected && Update(e[i].v, d[u] + wp(e[i])))
                trace[e[i].v] = i;
    }
}

void AdjustPotentials()
{
    int u = n;
    do
    {
        int i = trace[u];
        e[i].selected = true;
        e[i ^ 1].w *= -1;
        u = e[i].u;
    }
    while (u != 1);
    for (int u = 1; u <= n; ++u)
        if (d[u] < maxD) p[u] += d[u];
}

lli Solve()
{
    //Phase 1
    Dijkstra();
    if (d[n] == maxD) return -1;
    AdjustPotentials();
    lli d1 = p[n] - p[1];
    //Phase 2
    Dijkstra();
    if (d[n] == maxD) return -1;
    AdjustPotentials();
    lli d2 = p[n] - p[1];
    //Refine Edges;
    for (int i = 0; i < m; ++i)
        if (e[i].selected && e[i ^ 1].selected)
            e[i].selected = e[i ^ 1].selected = false;
    for (int i = 0; i < m; ++i)
        if (e[i].selected || e[i ^ 1].selected)
            e[i].selected = e[i ^ 1].selected = true;
    return d1 + d2;
}

void Visit(int u)
{
    while (true)
    {
        while (!adj[u].empty() && !e[adj[u].back()].selected)
            adj[u].pop_back();
        if (adj[u].empty()) break;
        int i = adj[u].back();
        adj[u].pop_back();
        e[i].selected = e[i ^ 1].selected = false;
        Visit(e[i].v);
    }
    cout << u << ' ';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen(taskname".inp", "r", stdin);
    freopen(taskname".out", "w", stdout);
    Enter();
    Init();
    lli res = Solve();
    cout << res << '\n';
    if (res != -1)
        Visit(1);
}

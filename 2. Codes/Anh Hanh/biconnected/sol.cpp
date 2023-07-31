#include<bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; i--)
#define REP(i, n) for (int i = 0, _n = (n); i < _n; i++)
#define FORE(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); i++)
#define ALL(v) (v).begin(), (v).end()
#define IS_INF(x)   (std::isinf(x))
#define IS_NAN(x)   (std::isnan(x))
#define fi   first
#define se   second
#define MASK(i) (1LL << (i))
#define BIT(x, i) (((x) >> (i)) & 1)
#define div   ___div
#define next   ___next
#define prev   ___prev
#define left   ___left
#define right   ___right
#define __builtin_popcount __builtin_popcountll
using namespace std;
template<class X, class Y>
    bool minimize(X &x, const Y &y) {
        X eps = 1e-9;
        if (x > y + eps) {
            x = y;
            return true;
        } else return false;
    }
template<class X, class Y>
    bool maximize(X &x, const Y &y) {
        X eps = 1e-9;
        if (x + eps < y) {
            x = y;
            return true;
        } else return false;
    }
template<class T>
    T Abs(const T &x) {
        return (x < 0 ? -x : x);
    }
 
/* Author: Van Hanh Pham */
 
class DisjointSet {
private:
    vector<int> lab;
 
public:
    DisjointSet(int n = 0) {
        lab.assign(n + 7, -1);
    }
 
    int find(int x) {
        return lab[x] < 0 ? x : lab[x] = find(lab[x]);
    }
 
    bool join(int u, int v) {
        int x = find(u), y = find(v);
        if (x == y) return false;
 
        if (lab[x] > lab[y]) swap(x, y);
        lab[x] += lab[y];
        lab[y] = x;
        return true;
    }
};
 
/** END OF TEMPLATE. DRINK A CUP OF TIGERSUGAR BEFORE READING MY CODE. **/
 
struct Edge {
    int u, v;
    bool used, isBridge;
 
    Edge(int _u = 0, int _v = 0) {
        u = _u; v = _v;
        used = false;
        isBridge = false;
    }
};
 
#define MAX   250250
int numNode, numEdge;
Edge edges[MAX];
vector<int> adj[MAX];
int low[MAX], num[MAX], cnt;
int compID[MAX], compNode[MAX], numComp;
vector<int> treeAdj[MAX], leaves;
 
void loadGraph(void) {
    scanf("%d%d", &numNode, &numEdge);
 
    FOR(i, 1, numNode) adj[i].clear();
    memset(low, 0, (numNode + 1) * sizeof (int));
    memset(num, 0, (numNode + 1) * sizeof (int));
    cnt = 0;
    memset(compID, 0, (numNode + 1) * sizeof (int));
    memset(compNode, 0, (numNode + 1) * sizeof (int));
    numComp = 0;
    FOR(i, 1, numNode) treeAdj[i].clear();
    leaves.clear();
 
    FOR(i, 1, numEdge) {
        int u, v; scanf("%d%d", &u, &v);
        edges[i] = Edge(u, v);
        adj[u].push_back(i);
        adj[v].push_back(i);
    }
}
 
void dfsNode(int u) {
    low[u] = numNode + 1;
    num[u] = ++cnt;
 
    FORE(it, adj[u]) if (!edges[*it].used) {
        edges[*it].used = true;
        int v = edges[*it].u ^ edges[*it].v ^ u;
        if (num[v] == 0) {
            dfsNode(v);
            minimize(low[u], low[v]);
            edges[*it].isBridge = low[v] > num[u];
        } else minimize(low[u], num[v]);
    }
}
 
void buildTree(void) {
    FOR(i, 1, numNode) if (num[i] == 0) dfsNode(i);
 
    DisjointSet dsu(numNode);
    FOR(i, 1, numEdge) if (!edges[i].isBridge) dsu.join(edges[i].u, edges[i].v);
 
    FOR(i, 1, numNode) if (dsu.find(i) == i) {
        compID[i] = ++numComp;
        compNode[numComp] = i;
    }
    FOR(i, 1, numNode) if (dsu.find(i) != i) compID[i] = compID[dsu.find(i)];
 
//    FOR(i, 1, numNode) printf("%d ", compID[i]); printf("\n");
 
    FOR(i, 1, numEdge) if (edges[i].isBridge) {
        int u = compID[edges[i].u];
        int v = compID[edges[i].v];
        treeAdj[u].push_back(v);
        treeAdj[v].push_back(u);
//        printf("Tree edge %d %d\n", u, v);
    }
}
 
void dfsComp(int u, int par) {
    bool isLeaf = true;
    FORE(it, treeAdj[u]) if (*it != par) {
        int v = *it;
        dfsComp(v, u);
        isLeaf = false;
    }
    if (isLeaf) leaves.push_back(u);
}
 
void solve(void) {
    if (numComp == 1) {
        printf("0\n");
        return;
    }
    if (numComp == 2) {
        printf("1\n");
        printf("%d %d\n", compNode[1], compNode[2]);
        return;
    }
 
    int root = 1;
    while (treeAdj[root].size() < 2) root++;
    dfsComp(root, -1);
 
    printf("%d\n", ((int)leaves.size() + 1) / 2);
    REP(i, leaves.size() / 2) {
        int u = leaves[i];
        int v = leaves[i + leaves.size() / 2];
        printf("%d %d\n", compNode[u], compNode[v]);
    }
    if (leaves.size() % 2 != 0) {
        int u = leaves.front();
        int v = leaves.back();
        printf("%d %d\n", compNode[u], compNode[v]);
    }
}
 
int main(void) {
    int numTest; scanf("%d", &numTest);
    REP(love, numTest) {
        loadGraph();
        buildTree();
        solve();
    }
    return 0;
}
 
/*** BUBBLE TEA IS GREAT. MY CODE IS AMAZING :D ***/

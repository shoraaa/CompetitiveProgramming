#include "testlib.h"
 
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
 
/** END OF TEMPLATE. DRINK A CUP OF TIGERSUGAR BEFORE READING MY CODE. **/
 
const int MAX_EXTRA = (int)3e6;
const double TEST_POINT = 0.3;
const double EXP = acos(-1.0);
 
struct Edge {
    int u, v;
    bool used, isBridge;
 
    Edge(int _u = 0, int _v = 0) {
        u = _u; v = _v;
        used = false;
        isBridge = false;
    }
};
 
#define MAX   3500350
int numNode, numEdge;
Edge edges[MAX];
vector<int> adj[MAX];
int low[MAX], num[MAX], cnt;
 
void loadGraph(void) {
    numNode = inf.readInt();
    numEdge = inf.readInt();
    FOR(i, 1, numEdge) {
        int u = inf.readInt();
        int v = inf.readInt();
        edges[i] = Edge(u, v);
    }
}
 
void dfs(int u) {
    low[u] = numNode + 1;
    num[u] = ++cnt;
 
    FORE(it, adj[u]) if (!edges[*it].used) {
        edges[*it].used = true;
        int v = edges[*it].u ^ edges[*it].v ^ u;
        if (num[v] == 0) {
            dfs(v);
            minimize(low[u], low[v]);
            edges[*it].isBridge = low[v] > num[u];
        } else minimize(low[u], num[v]);
    }
}
 
int checkAnswer(InStream &stream) {
    int numExtra = stream.readInt(0, MAX_EXTRA, "number of extra edges");
    FOR(i, 1, numExtra) {
        int u = stream.readInt(1, numNode, format("extra[%d].u", i));
        int v = stream.readInt(1, numNode, format("extra[%d].v", i));
        edges[numEdge + i] = Edge(u, v);
    }
 
    FOR(i, 1, numNode) adj[i].clear();
    memset(low, 0, (numNode + 1) * sizeof (int));
    memset(num, 0, (numNode + 1) * sizeof (int));
    cnt = 0;
 
    FOR(i, 1, numEdge + numExtra) {
        adj[edges[i].u].push_back(i);
        adj[edges[i].v].push_back(i);
        edges[i].used = false;
        edges[i].isBridge = false;
    }
 
    FOR(i, 1, numNode) if (num[i] == 0) dfs(i);
 
    FOR(i, 1, numEdge + numExtra) if (edges[i].isBridge) return -1;
    return numExtra;
}
 
int numCorrect, numTest;
void process(int testID) {
    setTestCase(testID);
    int jury = checkAnswer(ans);
    int cont = checkAnswer(ouf);
 
    quitif(jury < 0, _fail, "Jury's answer is invalid.");
    quitif(cont >= 0 && jury > cont, _fail, "Jury has worse answer: jury = %d, contestant = %d", jury, cont);
    if (cont == jury) numCorrect++;
    else {
    	cerr << numNode << ' ' << numEdge << '\n';
	    FOR(i, 1, numEdge) {
	        cerr << edges[i].u << ' ' << edges[i].v << '\n';
	    }
    	cerr << '\n';
		}
}
 
int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
 
    int numTest = inf.readInt();
    FOR(i, 1, numTest) {
        loadGraph();
        process(i);
    }
 
    double rate = 1.0 * numCorrect / numTest;
    string message = format("%d correct answers out of %d (%.2lf%%)", numCorrect, numTest, 100.0 * rate);
    if (numCorrect == numTest) quit(_ok, message);
    else quitp(TEST_POINT * pow(rate, EXP), message);
    return 0;
}
 
/*** BUBBLE TEA IS GREAT. MY CODE IS AMAZING :D ***/
 

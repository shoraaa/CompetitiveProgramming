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
 
vector<string> treeTypes({"random", "long", "focused", "mixed", "line", "binary"});
class TreeGenerator {
private:
    vector<int> lab, par;
    int numNode;
 
public:
    TreeGenerator(int n = 0) {
        numNode = n;
        lab.assign(numNode + 7, 0);
        par.assign(numNode + 7, 0);
    }
 
    vector<int> genTreeAsParent(string type) {
        if (type == "line") {
            FOR(i, 2, numNode) par[i] = i - 1;
            return par;
        }
        if (type == "binary") {
            FOR(i, 2, numNode) par[i] = i / 2;
            return par;
        }
 
        if (numNode < 50) type = rnd.next(2) ? "random" : "long";
        if (type == "random") {
            FOR(i, 2, numNode) par[i] = rnd.next(1, i - 1);
            return par;
        }
 
        if (type == "long") {
            FOR(i, 2, numNode) par[i] = rnd.next(max(1, i - 7), i - 1);
            return par;
        }
 
        if (type == "focused") {
            vector<int> hubs = rnd.perm(numNode, 1);
            hubs.resize(6);
            hubs.push_back(1);
 
            FOR(i, 2, numNode) {
                if (rnd.next(100) < 7) par[i] = rnd.next(1, i - 1);
                else {
                    while (true) {
                        par[i] = rnd.any(hubs);
                        if (par[i] < i) break;
                    }
                }
            }
            return par;
        }
 
        if (type == "mixed") {
            int x1 = 0.47 * numNode;
            int x2 = 0.94 * numNode;
            FOR(i, 2, x1) par[i] = i - 1;
 
            vector<int> hubs = rnd.perm(x1, 1);
            hubs.resize(7);
            FOR(i, x1 + 1, x2) par[i] = rnd.any(hubs);
            FOR(i, x2 + 1, numNode) par[i] = rnd.next(1, i - 1);
            return par;
        }
 
        quitf(_fail, "unknown tree type %s", type.c_str());
    }
 
    vector<pair<int, int>> genTreeAsEdge(string type) {
        genTreeAsParent(type);
        FOR(i, 2, numNode) ensure(1 <= par[i] && par[i] < i);
        FOR(i, 1, numNode) lab[i] = i;
        shuffle(lab.begin() + 1, lab.begin() + numNode + 1);
 
        vector<pair<int, int>> edges;
        FOR(i, 2, numNode) edges.push_back(make_pair(lab[i], lab[par[i]]));
        FORE(it, edges) if (rnd.next(2)) swap(it->fi, it->se);
        shuffle(ALL(edges));
        return edges;
    }
};
 
vector<string> valueTypes({"uniform", "logarit", "uniform", "maximum"});
long long genValue(long long low, long long high, const string &type, int param = 3) {
    if (type == "logarit") ensure(low > 0);
    ensure(low <= high);
    if (type == "uniform") return rnd.next(low, high);
    if (type == "logarit") return low * exp(rnd.next() * log(1.0 * high / low)) + 0.5;
    if (type == "maximum") return rnd.wnext(low, high, param);
    quitf(_fail, "unknown value type %s", type.c_str());
}
 
vector<string> setTypes({"uniform", "logarit", "maximum", "sequence",
                         "uniform", "logarit", "maximum", "sequence",
                         "squared", "major-1", "major-2", "major-3", "major-5", "major-7"});
vector<int> divideSet(int numSet, int totalSize, string type, int minSize) {
    vector<int> result(numSet, 0);
    ensure(minSize * numSet <= totalSize);
    REP(i, numSet) result[i] = minSize;
    totalSize -= minSize * numSet;
 
    if (type == "uniform" || type == "logarit" || type == "maximum") {
        REP(love, totalSize) result[genValue(1, numSet, type, 10) - 1]++;
        return result;
    }
 
    if (type == "sequence") {
        REP(i, numSet) {
            int tmp = rnd.wnext(0, totalSize, -10);
            result[i] += tmp;
            totalSize -= tmp;
        }
        result[0] += totalSize;
        return result;
    }
 
    if (type == "squared") {
        int group = min(numSet, (int)sqrt(totalSize));
        REP(love, totalSize) result[rnd.next(100) ? rnd.next(group) : rnd.next(numSet)]++;
        shuffle(ALL(result));
        return result;
    }
 
    if (type.size() == 7 && type.substr(0, 6) == "major-") {
        int group = min(numSet, type.back() - '0');
        REP(love, totalSize) result[rnd.next(100) ? rnd.next(group) : rnd.next(numSet)]++;
        shuffle(ALL(result));
        return result;
    }
 
    quitf(_fail, "Unknown type %s", type.c_str());
}
 
/** END OF TEMPLATE. DRINK A CUP OF TIGERSUGAR BEFORE READING MY CODE. **/
 
struct Test {
    int numNode;
    vector<pair<int, int>> edges;
 
    Test(int numNode = 0, const vector<pair<int, int>> &edges = vector<pair<int, int>>()) {
        this->numNode = numNode;
        this->edges = edges;
    }
 
    void print(void) const {
        printf("\n%d %d\n", numNode, (int)edges.size());
        FORE(it, edges) printf("%d %d\n", it->fi, it->se);
    }
};
 
Test genGraph(int numNode, int numEdge) {
    ensure(numEdge >= numNode - 1);
    if (numEdge < numNode || rnd.next(5) == 0)
        return Test(numNode, TreeGenerator(numNode).genTreeAsEdge(rnd.any(treeTypes)));
 
    int numCircle = genValue(1, min(numEdge - numNode + 1, numNode / 2), rnd.any(valueTypes), 9);
    int numAlone = genValue(1, numNode - 2 * numCircle + 1, rnd.any(valueTypes), 7) - 1;
    int numComp = numCircle + numAlone;
 
    vector<int> sizes = divideSet(numCircle, numNode - numAlone, rnd.any(setTypes), 2);
    REP(love, numAlone) sizes.push_back(1);
    shuffle(ALL(sizes));
 
    vector<int> nodes = rnd.perm(numNode, 1);
    vector<vector<int>> comps(numComp, vector<int>());
    int j = 0;
    REP(i, numComp) REP(love, sizes[i]) comps[i].push_back(nodes[j++]);
 
    vector<pair<int, int>> edges = TreeGenerator(numComp).genTreeAsEdge(rnd.any(treeTypes));
    FORE(it, edges) {
        it->fi = rnd.any(comps[it->fi - 1]);
        it->se = rnd.any(comps[it->se - 1]);
    }
 
    REP(i, numComp) if (sizes[i] > 1) REP(j, sizes[i]) {
        int u = comps[i][j];
        int v = comps[i][(j + 1) % sizes[i]];
        edges.push_back(make_pair(u, v));
    }
 
    REP(love, rnd.wnext((int)edges.size(), numEdge, -2) - edges.size()) {
        int i = rnd.next(numComp);
        int j = rnd.any(comps[i]);
        int k = rnd.any(comps[i]);
        edges.push_back(make_pair(j, k));
    }
 
    shuffle(ALL(edges));
    FORE(it, edges) if (rnd.next(2)) swap(it->fi, it->se);
    return Test(numNode, edges);
}
 
vector<Test> tests;
void genMultipleTests(int minSize, int maxSize, int sum, int param) {
    while (sum >= minSize) {
        int numEdge = rnd.wnext(minSize, min(maxSize, sum), param);
        int numNode = rnd.next(minSize, numEdge);
        tests.push_back(genGraph(numNode, numEdge));
        sum -= max((int)tests.back().edges.size(), numNode);
    }
}
 
const int LIMIT[] = {-1, 100, 1500, 20000, 250000};
 
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    prepareOpts(argc, argv);
 
    int subtask = opt<int>("subtask");
 
    genMultipleTests(LIMIT[subtask], LIMIT[subtask], LIMIT[subtask] * 4, 0);
 
    if (subtask == 2) genMultipleTests(100, 500, LIMIT[subtask] * 5, -3);
    if (subtask == 3 || subtask == 4) {
        genMultipleTests(LIMIT[subtask] / 5, LIMIT[subtask], LIMIT[subtask] * 3, -5);
        genMultipleTests(100, 500, LIMIT[subtask] * 3, -3);
    }
 
    int sumNode = LIMIT[subtask] * 12, sumEdge = LIMIT[subtask] * 12;
    FORE(it, tests) {
        sumNode -= it->numNode;
        sumEdge -= it->edges.size();
    }
 
    genMultipleTests(10, 100, min(sumNode, sumEdge), -1);
 
    cout << tests.size() << endl;
    FORE(it, tests) it->print();
    return 0;
}
 
/*** BUBBLE TEA IS GREAT. MY CODE IS AMAZING :D ***/

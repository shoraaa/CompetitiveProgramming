#include <bits/stdc++.h>
using namespace std;

struct node {
    int op, cl, le;
    
    node(): op(0), cl(0), le(0) {}
};

const int N = 1e6 + 5;

char s[N]; int lo, hi;
node tr[N * 4];

node operator + (node a, node b) {
    node c;
    int add = min(a.op, b.cl);
    c.le = a.le + b.le + add;
    c.op = a.op + b.op - add;
    c.cl = a.cl + b.cl - add;
    return c;
}

void init(int i, int l, int r) {
    if (l + 1 == r) {
        tr[i].op = s[l] == '(';
        tr[i].cl = s[l] == ')';
        return;
    }
    int m = (l + r) / 2;
    int ls = i * 2, rs = ls + 1;
    init(ls, l, m);
    init(rs, m, r);
    tr[i] = tr[ls] + tr[rs];
}

node query(int i, int l, int r) {
    if (l >= hi || r <= lo)
        return node();
    if (l >= lo && r <= hi)
        return tr[i];
    int m = (l + r) / 2;
    return query(i * 2, l, m)
    + query(i * 2 + 1, m, r);
}

int main() {
    cin >> s;
    int n = strlen(s);
    init(1, 0, n);
    int q; cin >> q;
    while (q--) {
        cin >> lo >> hi; lo--;
        cout << query(1, 0, n).le * 2;
        cout << '\n';
    }
}

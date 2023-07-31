#include <bits/stdc++.h>
using namespace std;

using Tp = long double;

const Tp EPS = 1e-9;

struct point {
    Tp x, y;

    point(Tp x = 0, Tp y = 0): x(x), y(y) {}

    point& operator += (const point &o) {
        x += o.x; y += o.y; return *this;
    }

    point& operator -= (const point &o) {
        x -= o.x; y -= o.y; return *this;
    }

    point& operator *= (const Tp &k) {
        x *= k; y *= k; return *this;
    }

    point& operator /= (const Tp &k) {
        x /= k; y /= k; return *this;
    }

    bool operator != (const point &o) const {
        return x != o.x || y != o.y;
    }

    point operator + (const point &o) const {
        return point(*this) += o;
    }

    point operator - (const point &o) const {
        return point(*this) -= o;
    }

    point operator * (const Tp &k) const {
        return point(*this) *= k;
    }

    point operator / (const Tp &k) const {
        return point(*this) /= k;
    }
};

Tp dot(const point &a, const point &b) {
    return a.x * b.x + a.y * b.y;
}

Tp cross(const point &a, const point &b) {
    return a.x * b.y - a.y * b.x;
}

Tp orient(const point &a,
const point &b, const point &c) {
    return cross(b - a, c - b);
}

Tp norm(const point &p) {
    return dot(p, p);
}

bool ccw(const point &a,
const point &b, const point &c) {
    return orient(a, b, c) > 0;
}

bool cw(const point &a,
const point &b, const point &c) {
    return orient(a, b, c) < 0;
}

bool cmp(const point &a, const point &b) {
    if (a.y < 0 && b.y >= 0) return false;
    if (a.y >= 0 && b.y < 0) return true;
    return cross(a, b) > 0;
}

istream& operator >> (istream &is, point &p) {
    return is >> p.x >> p.y;
}

ostream& operator << (ostream &os, const point &p) {
    return os << '(' << p.x << ", " << p.y << ')';
}

struct line {
    point v; Tp c;

    line() {}

    line(point v, Tp c): v(v), c(c) {}

    line(point p, point q): v(q - p), c(cross(v, p)) {}

    Tp side(const point &p) {
        return cross(v, p) - c;
    }
};

bool intersect(line l1, line l2, point &pt) {
    Tp d = cross(l1.v, l2.v);
    if (abs(d) < EPS) return false;
    pt = (l2.v * l1.c - l1.v * l2.c) / d;
    return true;
}

void solve() {
    int n; cin >> n; Tp tot = 0;
    vector <point> a(n), b;
    for (point &pt : a) cin >> pt;
    a.push_back(a.front());
    for (int i = 0; i < n; i++)
        tot += cross(a[i], a[i + 1]);
    point root = {(a[0].x + a[1].x) / 2,
                (a[0].y + a[1].y) / 2};
    point p1 = a[0] - root, p2 = a[1] - root;
    p1 = point(p1.x + p1.y, -p1.x + p1.y) + root;
    p2 = point(p2.x - p2.y, p2.x + p2.y) + root;
    line l1(root, p1), l2(root, p2);
    for (int i = 0; i < n; i++)
        if (l1.side(a[i]) * l1.side(a[0]) < 0
        && l2.side(a[i]) * l2.side(a[1]) < 0)
            b.push_back(a[i]);
    for (int i = 1; i < n; i++) {
        Tp x = l1.side(a[i]) * l1.side(a[i + 1]);
        if (x <= 0) {
            point pt;
            if (intersect(l1, line(a[i], a[i + 1]), pt))
                b.push_back(pt);
        }
    }
    b.push_back(root);
    for (int i = 1; i < n; i++) {
        Tp x = l2.side(a[i]) * l2.side(a[i + 1]);
        if (x <= 0) {
            point pt;
            if (intersect(l2, line(a[i], a[i + 1]), pt))
                b.push_back(pt);
        }
    }
    int m = b.size();
    b.push_back(b.front()); Tp res = 0;
    for (int i = 0; i < m; i++)
        res += cross(b[i], b[i + 1]);
    cout << abs(res / tot) << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << setprecision(10) << fixed;
    cerr << setprecision(10) << fixed;
    int t; cin >> t;
    while (t--) solve();
}
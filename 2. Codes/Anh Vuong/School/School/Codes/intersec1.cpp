#include <bits/stdc++.h>
using namespace std;

using type = long double;

const type EPS = 1e-9;

struct point {
    type x, y;

    point(type x = 0, type y = 0): x(x), y(y) {}

    point& operator -= (const point &o) {
        x -= o.x; y -= o.y; return *this;
    }

    point& operator += (const point &o) {
        x += o.x; y += o.y; return *this;
    }

    point& operator *= (const type &k) {
        x *= k; y *= k; return *this;
    }

    point& operator /= (const type &k) {
        x /= k; y /= k; return *this;
    }

    point operator - (const point &o) const {
        return point(*this) -= o;
    }

    point operator + (const point &o) const {
        return point(*this) += o;
    }

    point operator * (const type &k) const {
        return point(*this) *= k;
    }

    point operator / (const type &k) const {
        return point(*this) /= k;
    }
};

type cross(const point &a, const point &b) {
    return a.x * b.y - b.x * a.y;
}

type dot(const point &a, const point &b) {
    return a.x * b.x + a.y * b.y;
}

type norm(const point &a) {
    return dot(a, a);
}

type abs(const point &a) {
    return sqrt(norm(a));
}

type dis(const point &a, const point &b) {
    return sqrt(norm(a - b));
}

type orient(const point &a,
const point &b, const point &c) {
    return cross(b - a, c - b);
}

point perp(const point &a) {
    return point(-a.y, a.x);
}

struct line {
    point v; type c;

    line() {}

    line(point v, type c): v(v), c(c) {}

    line(type a, type b, type c): v(b, -a), c(c) {}

    line(point p, point q): v(q - p), c(cross(v, p)) {}

    type side(point p) {
        return cross(v, p) - c;
    }

    line shift(type d) {
        return {v, c + d * abs(v)};
    }
    
    type dis(point a) {
        return abs(side(a)) / abs(v);
    }
};

line bisector(line l1, line l2, bool sign) {
    return {l2.v / abs(l2.v) + l1.v / abs(l1.v) * sign,
            l2.c / abs(l2.v) + l1.c / abs(l1.v) * sign};
}

bool intersect(line l1, line l2, point &p) {
    type d = cross(l1.v, l2.v);
    if (abs(d) < EPS) return 0;
    p = (l2.v * l1.c - l1.v * l2.c) / d;
    return true;
}

int main() {
    freopen("intersec1.in", "r", stdin);
    freopen("intersec1.out", "w", stdout);
    double a, b, c, x, y, z;
    cin >> a >> b >> c >> x >> y >> z;
    point pt;
    cout << setprecision(10) << fixed;
    intersect(line(a, b, -c), line(x, y, -z), pt);
    cout << pt.x << ' ' << pt.y << '\n';
}
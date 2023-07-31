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

int main() {
    freopen("bisector.in", "r", stdin);
    freopen("bisector.out", "w", stdout);
    point a, b, c;
    cout << setprecision(10) << fixed;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    line l = bisector(line(a, b), line(a, c), 1);
    cout << -l.v.y << ' ' << l.v.x << ' ' << -l.c << '\n';
}
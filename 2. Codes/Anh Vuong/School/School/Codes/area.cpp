#include <bits/stdc++.h>
using namespace std;

using type = long double;

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
    return abs(a - b);
}

type orient(const point &a,
const point &b, const point &c) {
    return cross(b - a, c - b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; type res = 0; cin >> n;
    vector <point> a(n);
    for (auto &pt : a) cin >> pt.x >> pt.y;
    a.push_back(a.front());
    for (int i = 0; i < n; i++)
        res += cross(a[i], a[i + 1]);
    cout << setprecision(10) << fixed;
    cout << abs(res) / 2 << '\n';
}
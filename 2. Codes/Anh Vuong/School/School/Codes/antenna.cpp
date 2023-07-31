#include <bits/stdc++.h>

using namespace std;

using Tp = double;

struct point {
    Tp x, y;
    
    point(Tp x = 0, Tp y = 0): x(x), y(y) {}
    
    point& operator -= (const point &o) {
        x -= o.x; y -= o.y; return *this;
    }
    
    point& operator *= (const Tp &k) {
        x *= k; y *= k; return *this;
    }
    
    point operator - (const point &o) const {
        return point(*this) -= o; 
    }
};

Tp dot(const point &a, const point &b) {
    return a.x * b.x + a.y * b.y;
}

Tp cross(const point &a, const point &b) {
    return a.x * b.y - a.y * b.x;
}

Tp norm(const point &p) {
    return dot(p, p);
}

Tp abs(const point &a) {
    return sqrt(norm(a));
}

istream& operator >> (istream &is, point &p) {
    return is >> p.x >> p.y;
}

ostream& operator << (ostream &os, const point &p) {
    return os << '(' << p.x << ", " << p.y << ')';
}

vector<point> pt; int n, req;

bool check(Tp r) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        vector<pair<double, int>> events;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            point v = pt[j] - pt[i];
            if (abs(v) > r * 2) continue;
            Tp a = atan2(v.y, v.x);
            Tp b = acos(abs(v) / (r * 2));
            events.emplace_back(a - b, -1);
            events.emplace_back(a + b, 1);
        }
        sort(events.begin(), events.end());
        int m = events.size(), cur = 1;
        for (int i = 0; i < m; i++)
            events.push_back(events[i]);
        for (int i = 0; i < 2 * m; i++) {
            cur -= events[i].second;
            res = max(res, cur);
        }
    }
    return res >= req;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << setprecision(8) << fixed;
    cin >> n >> req; pt.resize(n);
    for (point &p : pt) cin >> p;
    Tp lo = 0, hi = 1e9;
    for (int i = 0; i < 60; i++) {
        Tp mi = (lo + hi) / 2;
        if (check(mi)) hi = mi;
        else lo = mi;
    }
    cout << hi << '\n';
}

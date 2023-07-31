#include <bits/stdc++.h>
using namespace std;

const int N = 55;
const double inf = 1e14;
const double eps = 1e-6;
const double PI = 3.14159265359;

int n, m, a[N*N], b[N*N];

struct Point {
    double x, y;
    bool operator < (const Point &A) const {
        if (abs (x - A.x) > eps) return x < A.x;
        if (abs (y - A.y) > eps) return y < A.y;
        return false;
    }
    bool operator == (const Point &A) const {
        return (abs (x - A.x) <= eps && abs (y - A.y) <= eps);
    }
} P[N];

void print(Point A) { cout << fixed << setprecision(15) << A.x << ' ' << A.y << ' '; }

int ccw(Point A, Point B, Point C) {
    double t1 = (A.x - B.x) * (A.y + B.y);
    double t2 = (B.x - C.x) * (B.y + C.y);
    double t3 = (C.x - A.x) * (C.y + A.y);
    double t = t1 + t2 + t3;
    if (abs (t - 0) <= eps) return 0;
    return (t > 0 ? 1 : -1);
}

bool onSegLine(Point A, Point B, Point C) {
    if (ccw (A, B, C) != 0) return false;
    return (C.x >= min (A.x, B.x) && C.x <= max (A.x, B.x)
         && C.y >= min (A.y, B.y) && C.y <= max (A.y, B.y));
}

bool SegIntersection(Point A, Point B, Point C, Point D) {
    int o1 = ccw (A, B, C);
    int o2 = ccw (A, B, D);
    int o3 = ccw (C, D, A);
    int o4 = ccw (C, D, B);

    if (o1 != o2 && o3 != o4) return true;
    if (onSegLine (A, B, C)) return true;
    if (onSegLine (A, B, D)) return true;
    if (onSegLine (C, D, A)) return true;
    if (onSegLine (C, D, B)) return true;

    return false;
}

Point LineIntersection(Point A, Point B, Point C, Point D) {
    double a1 = B.y - A.y;
    double b1 = A.x - B.x;
    double c1 = - (a1 * A.x + b1 * A.y);

    double a2 = D.y - C.y;
    double b2 = C.x - D.x;
    double c2 = - (a2 * C.x + b2 * C.y);

    double Div = a1 * b2 - a2 * b1;
    if (Div == 0) return { inf, inf };
    else {
        double x = (c2 * b1 - c1 * b2) / Div;
        double y = (c1 * a2 - c2 * a1) / Div;
        return { x, y };
    }
}

int main() {
    freopen ("cake.inp", "r", stdin);
    freopen ("cake.out", "w", stdout);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a[i] >> b[i];
        a[i]--; b[i]--;
    }

    for (int i = 0; i < n; i++) {
        double X = 100 * cos (2 * PI * i / n);
        double Y = 100 * sin (2 * PI * i / n);
        P[i] = {X, Y};
    }

//    for (int i = 0; i < n; i++) {
//        cout << i << " : "; print (P[i]); cout << '\n';
//    }
//    cout << '\n';

    int res = 1;
    for (int i = 1; i <= m; i++) {
        map <Point, int> vis;
        int numIntersection = 0;
        for (int j = 1; j < i; j++) {
            if (!SegIntersection(P[a[i]], P[b[i]], P[a[j]], P[b[j]])) continue;
            Point M = LineIntersection(P[a[i]], P[b[i]], P[a[j]], P[b[j]]);
            if (M.x == inf || a[i] == a[j] || a[i] == b[j] || b[i] == a[j] || b[i] == b[j]) continue;
            if (!vis[M]) numIntersection++, vis[M] = true;
        }
        res += numIntersection + 1;
    }

    cout << res << '\n';

    return 0;
}

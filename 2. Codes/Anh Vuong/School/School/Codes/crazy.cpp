#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 45;

set <size_t> c[N]; int pw[N];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s; cin >> s;
    int n = s.size();
    if (n & 1) {
        cout << "no\n"; return 0;
    }
    int m = n / 2;
    for (int i = 0; i < (1 << m); i++) {
        int x = 0; string a, b;
        for (int j = 0; j < m; j++)
            if (i >> j & 1) {
                x++; a += s[j];
            }
            else b += s[j];
        if (a.size() > b.size())
            swap(a, b);
        if (a != b.substr(0, a.size()))
            continue;
        c[x].insert(hash <string> {}
        (b.substr(a.size(), -1)));
    }
    for (int i = 0; i < (1 << m); i++) {
        int x = 0; string a, b;
        for (int j = 0; j < m; j++)
            if (i >> j & 1) {
                x++; a += s[j + m];
            }
            else b += s[j + m];
        if (a.size() > b.size())
            swap(a, b);
        if (a != b.substr(b.size()
        - a.size(), a.size())) continue;
        if (c[m - x].count(hash <string>
        {} (b.substr(0,
        b.size() - a.size())))) {
            cout << "yes\n"; return 0;
        }
    }
    cout << "no\n";
}
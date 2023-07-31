#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int a[N], r[N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n; cin >> n;
    vector <int> v;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = n; i > 0; i--) {
        int id = i, mn = a[i];
        while (!v.empty()
        && a[v.back()] < a[i]) {
            mn = min(mn, a[v.back()]);
            id = v.back(); v.pop_back();
        }
        a[id] = mn; r[i] = id;
        v.push_back(id); 
    }
    v.clear();
    for (int i = 1; i <= n; i++) {
        v.push_back(i); i = r[i];
    }
    cout << v.size() << '\n';
    for (int i : v) {
        cout << r[i] - i + 1 << ' ';
        for (int j = i; j <= r[i]; j++)
            cout << j << " \n"[j == r[i]];
    }
}
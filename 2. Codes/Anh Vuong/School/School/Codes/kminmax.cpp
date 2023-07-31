#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k; cin >> n >> k;
    vector <int> a(n);
    deque <int> dq;
    for (int &x : a) cin >> x;
    for (int i = 0; i < n; i++) {
        while (dq.size() && dq.front() <= i - k)
            dq.pop_front();
        while (dq.size() && a[dq.back()] >= a[i])
            dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1)
            cout << a[dq.front()] << ' ';
    }
    cout << '\n'; dq.clear();
    for (int i = 0; i < n; i++) {
        while (dq.size() && dq.front() <= i - k)
            dq.pop_front();
        while (dq.size() && a[dq.back()] <= a[i])
            dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1)
            cout << a[dq.front()] << ' ';
    }
}
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct seg_tree{
    static const int N = 2e5 + 5;

    struct node{
        int l, r; int sum, val;

        node(): sum(0), val(0){}

        bool is_leaf() const {
            return l == r;
        }
    } tree[4 * N];

    void build(int i, int l, int r){
        tree[i].l = l; tree[i].r = r;
        if (l != r){
            int m = (l + r) / 2;
            build(i * 2, l, m); build(i * 2 + 1, m + 1, r);
        }
    }

    void update(int i, int p, int val){
        if (tree[i].l > p || tree[i].r < p) return;
        if (tree[i].is_leaf()){
            tree[i].sum = val; tree[i].val = p * val;
            return;
        }
        update(i * 2, p, val); update(i * 2 + 1, p, val);
        int l_sz = tree[i * 2].r - tree[i * 2].l + 1;
        if (l_sz & 1){
            tree[i].sum = tree[i * 2].sum - tree[i * 2 + 1].sum;
            tree[i].val = tree[i * 2].val - tree[i * 2 + 1].val; 
        }
        else {
            tree[i].sum = tree[i * 2].sum + tree[i * 2 + 1].sum;
            tree[i].val = tree[i * 2].val + tree[i * 2 + 1].val; 
        }
    }

    int get_val(int i, int l, int r){
        if (tree[i].l > r || tree[i].r < l) return 0;
        if (tree[i].l >= l && tree[i].r <= r){
            int l_sz = tree[i].l - l;
            if (l_sz & 1) return -tree[i].val;
            return tree[i].val;
        }
        return get_val(i * 2, l, r) + get_val(i * 2 + 1, l, r);
    }

    int get_sum(int i, int l, int r){
        if (tree[i].l > r || tree[i].r < l) return 0;
        if (tree[i].l >= l && tree[i].r <= r){
            int l_sz = tree[i].l - l;
            if (l_sz & 1) return -tree[i].sum;
            return tree[i].sum;
        }
        return get_sum(i * 2, l, r) + get_sum(i * 2 + 1, l, r);
    }
} st;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q; st.build(1, 1, n);
    for (int i = 1, x; i <= n; i++){
        cin >> x; st.update(1, i, x);
    }
    char cmd; int u, v;
    while (q--){
        cin >> cmd >> u >> v;
        if (cmd == 'U') st.update(1, u, v);
        else cout << st.get_val(1, u, v) -
        (u - 1) * st.get_sum(1, u, v) << '\n';
    }
}
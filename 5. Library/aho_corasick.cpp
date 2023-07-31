#include <bits/stdc++.h>

using namespace std;

struct aho_corasick {
    struct node {
        int nxt[26], len, link, leaf;
        node() {}
        node(int l): len(l), link(0), leaf(0) {
            memset(nxt, 0, sizeof nxt);
        }
    };

    vector <node> tree;

#define nxt(i, c) tree[i].nxt[c - 'a']
//#define link(i) tree[i].link
#define leaf(i) tree[i].leaf
#define len(i) tree[i].len

inline int& link(int i) { return tree[i].link; }

    aho_corasick(): tree(1) {}

    void add(const string &s) {
        int u = 0;
        for (char c : s) {
            if (nxt(u, c)) {
                nxt(u, c) = tree.size();
                tree.emplace_back(len(u) + 1);
            }
            u = nxt(u, c);
        }
        leaf(u)++;
    }

    void build() {
        queue <int> que; que.emplace(0);
        while (que.size()) {
            int u = que.front(); que.pop();
            leaf(u) += leaf(link(u));
            for (char c = 'a'; c <= 'z'; c++) {
                int v = nxt(u, c);
                if (v) {
                    link(v) = u ? nxt(link(u), c) : 0;
                    que.emplace(v);
                } else nxt(u, c) = nxt(link(u), c);
            }
        }
    }

    int count(const string &s) const {
        int u = 0, res = 0;
        for (char c : s)
            res += leaf(u = nxt(u, c));
        return res;
    }
};

int main() {
  return 0;
}
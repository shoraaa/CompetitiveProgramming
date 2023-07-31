#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "fibquery";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int M = 1e9 + 19972207;
inline int sum(int x, int y) {
	x += y; if (x >= M) x -= M; return x;
}
inline int dif(int x, int y) {
	x -= y; if (x < 0) x += M; return x;
}
inline void add(int& x, int y) {
	x += y; if (x >= M) x -= M;
}
inline void sub(int& x, int y) {
	x -= y; if (x < 0) x += M; 
}
inline int mul(ll x, ll y) {
	return x * y % M;
}
#define matrix_2 array<int, 2>
#define matrix array<array<int, 2>, 2>
inline void add(matrix& x, matrix& y) {
	add(x[0][0], y[0][0]), add(x[0][1], y[0][1]),
	add(x[1][0], y[1][0]), add(x[1][1], y[1][1]);
}
inline void sub(matrix& x, matrix& y) {
	sub(x[0][0], y[0][0]), sub(x[0][1], y[0][1]),
	sub(x[1][0], y[1][0]), sub(x[1][1], y[1][1]);
}
inline matrix mul(matrix& x, matrix& y) {
	matrix z;
	z[0][0] = sum(mul(x[0][0], y[0][0]), mul(x[0][1], y[1][0]));
	z[0][1] = sum(mul(x[0][0], y[0][1]), mul(x[0][1], y[1][1]));
	z[1][0] = sum(mul(x[1][0], y[0][0]), mul(x[1][1], y[1][0]));
	z[1][1] = sum(mul(x[1][0], y[0][1]), mul(x[1][1], y[1][1]));
	return z;
}
inline matrix_2 mul(matrix_2& x, matrix& y) {
	matrix_2 z;
	z[0] = sum(mul(x[0], y[0][0]), mul(x[1], y[1][0]));
	z[1] = sum(mul(x[0], y[0][1]), mul(x[1], y[1][1]));
	return z;
}
matrix pw(matrix x, ll k) {
	matrix res; 
	res[0][1] = res[1][0] = 0;
	res[0][0] = res[1][1] = 1;
	for (; k; k >>= 1, x = mul(x, x))
		if (k & 1) res = mul(res, x);
	return res; 
}

const int N = 5e5 + 5;
matrix_2 fib[N], base;
matrix pre_pw[N], trans;

struct segment_tree {
	struct node {
		int len = 1, res = 0;
		matrix val, lz;
	};
	int n, x, y, res; 
	matrix v, lz;
	vector<node> st;
	segment_tree(int n): n(n), st(n * 4) { build(1, 0, n-1); }
	void build(int k, int l, int r) {
		if (l == r) 
			return;
		int m = (l + r) >> 1;
		build(k << 1, l, m);
		build(k << 1 | 1, m+1, r);
		st[k].len = st[k << 1].len + st[k << 1 | 1].len;
	}
	// void push(int k) {
		// add(st[k << 1].val, st[k].lz);
		// add(st[k << 1].lz, st[k].lz);
		// add(st[k << 1].res, 
			// dif(mul(fib[st[k << 1].len + 1], st[k].lz)[0], 
					// mul(fib[1], st[k].lz)[0]));
// 		
		// st[k].lz = mul(st[k].lz, pre_pw[st[k << 1].len]);
// 		
		// add(st[k << 1 | 1].val, st[k].lz);
		// add(st[k << 1 | 1].lz, st[k].lz);
		// add(st[k << 1 | 1].res, 
			// dif(mul(fib[st[k << 1 | 1].len + 1], st[k].lz)[0], 
					// mul(fib[1], st[k].lz)[0]));
// 		
		// st[k].lz[0][0] = st[k].lz[0][1] = 0;
		// st[k].lz[1][0] = st[k].lz[1][1] = 0;
	// }
	void update(int k, int l, int r) {
		if (l > y || r < x)
			return;
		if (l >= x && r <= y) {
			add(st[k].lz, v);
			add(st[k].res, 
				dif(mul(fib[st[k].len + 1], v)[0],
						mul(fib[1], v)[0]));
			v = mul(v, pre_pw[st[k].len]);
			return;
		}
		int m = (l + r) >> 1;
		update(k << 1, l, m);
		update(k << 1 | 1, m+1, r);
		st[k].res = sum(st[k << 1].res, st[k << 1 | 1].res);
		add(st[k].res, 
				dif(mul(fib[st[k].len + 1], st[k].lz)[0],
						mul(fib[1], st[k].lz)[0]));

	}
	void get(int k, int l, int r) {
		if (l > y || r < x)
			return;
		if (l >= x && r <= y) {
			add(res, sum(st[k].res, 
					dif(mul(fib[st[k].len + 1], lz)[0], 
							mul(fib[1], lz)[0])));			
			return;
		}
		int m = (l + r) >> 1;
		auto tmp = lz;
		add(lz, st[k].lz);
		get(k << 1, l, m);
		lz = mul(lz, pre_pw[st[k << 1].len]);
		get(k << 1 | 1, m+1, r);
		lz = tmp;
		
	}
	void insert(int l, int r, ll val) {
		x = l, y = r, v = pw(trans, val), update(1, 0, n-1);
	}
	int get(int l, int r) {
		x = l, y = r, res = 0;
		lz[0][0] = lz[0][1] = lz[1][0] = lz[1][1] = 0;
		get(1, 0, n-1);
		return res;
	}
};

void read(int& x) {
	char c = getchar();
	while (!isdigit(c)) 
		c = getchar();
	x = 0;
	while (isdigit(c))
		x = x * 10 + c - '0', 
		c = getchar();
}

void read(ll& x) {
	char c = getchar();
	while (!isdigit(c)) 
		c = getchar();
	x = 0;
	while (isdigit(c))
		x = x * 10 + c - '0', 
		c = getchar();
}
void write(int x) {
	if (x > 9) write(x / 10);
	putchar(char(x % 10 + '0')); 
}

int n, q;
int main() {
	//file();
	base[0] = 0, base[1] = 1;
	
	trans[0][0] = 0, trans[0][1] = 1;
	trans[1][0] = 1, trans[1][1] = 1;

	read(n), read(q);

	pre_pw[1] = trans;
	fib[1] = mul(base, trans);
	for (int i = 2; i <= n + 1; ++i)
		pre_pw[i] = mul(pre_pw[i-1], trans),
		fib[i] = mul(fib[i-1], trans);
	
	segment_tree st(n); 
	ll k;
	for (int i = 0, t, l, r; i < q; ++i) {
		read(t), read(l), read(r), l--, r--;
		if (t == 1) {
			read(k);
			st.insert(l, r, k);
		} else {
			write(st.get(l, r));
			putchar('\n');
		} 
	}
	return 0;
}



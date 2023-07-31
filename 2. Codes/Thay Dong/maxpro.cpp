#include<bits/stdc++.h>
using namespace std;
using ll = long long;

 

/*
  ######################################################################
  #######################   THE   BIG   INT   ##########################
*/
const signed base = 1000000000;
const signed base_digits = 9; 
struct BigInteger {
	vector<signed> a;
	signed sign;
	BigInteger() :
		sign(1) {
	}
 
	BigInteger(long long v) {
		*this = v;
	}
 
	void operator=(const BigInteger &v) {
		sign = v.sign;
		a = v.a;
	}
 
	void operator=(long long v) {
		sign = 1;
		a.clear();
		if (v < 0)
			sign = -1, v = -v;
		for (; v > 0; v = v / base)
			a.push_back(v % base);
	}
 
	BigInteger operator+(const BigInteger &v) const {
		if (sign == v.sign) {
			BigInteger res = v;
 
			for (signed i = 0, carry = 0; i < (signed) max(a.size(), v.a.size()) || carry; ++i) {
				if (i == (signed) res.a.size())
					res.a.push_back(0);
				res.a[i] += carry + (i < (signed) a.size() ? a[i] : 0);
				carry = res.a[i] >= base;
				if (carry)
					res.a[i] -= base;
			}
			return res;
		}
		return *this - (-v);
	}
 
	BigInteger operator-(const BigInteger &v) const {
		if (sign == v.sign) {
			if (abs() >= v.abs()) {
				BigInteger res = *this;
				for (signed i = 0, carry = 0; i < (signed) v.a.size() || carry; ++i) {
					res.a[i] -= carry + (i < (signed) v.a.size() ? v.a[i] : 0);
					carry = res.a[i] < 0;
					if (carry)
						res.a[i] += base;
				}
				res.trim();
				return res;
			}
			return -(v - *this);
		}
		return *this + (-v);
	}
 
	void operator*=(signed v) {
		if (v < 0)
			sign = -sign, v = -v;
		for (signed i = 0, carry = 0; i < (signed) a.size() || carry; ++i) {
			if (i == (signed) a.size())
				a.push_back(0);
			long long cur = a[i] * (long long) v + carry;
			carry = (signed) (cur / base);
			a[i] = (signed) (cur % base);
			//asm("divl %%ecx" : "=a"(carry), "=d"(a[i]) : "A"(cur), "c"(base));
		}
		trim();
	}
 
	BigInteger operator*(signed v) const {
		BigInteger res = *this;
		res *= v;
		return res;
	}
 
	void operator*=(long long v) {
		if (v < 0)
			sign = -sign, v = -v;
		if(v > base){
			*this = *this * (v / base) * base + *this * (v % base);
			return ;
		}
		for (signed i = 0, carry = 0; i < (signed) a.size() || carry; ++i) {
			if (i == (signed) a.size())
				a.push_back(0);
			long long cur = a[i] * (long long) v + carry;
			carry = (signed) (cur / base);
			a[i] = (signed) (cur % base);
			//asm("divl %%ecx" : "=a"(carry), "=d"(a[i]) : "A"(cur), "c"(base));
		}
		trim();
	}
 
	BigInteger operator*(long long v) const {
		BigInteger res = *this;
		res *= v;
		return res;
	}
 
	void operator+=(const BigInteger &v) {
		*this = *this + v;
	}
	void operator-=(const BigInteger &v) {
		*this = *this - v;
	}
 
	bool operator<(const BigInteger &v) const {
		if (sign != v.sign)
			return sign < v.sign;
		if (a.size() != v.a.size())
			return a.size() * sign < v.a.size() * v.sign;
		for (signed i = a.size() - 1; i >= 0; i--)
			if (a[i] != v.a[i])
				return a[i] * sign < v.a[i] * sign;
		return false;
	}
 
	bool operator>(const BigInteger &v) const {
		return v < *this;
	}
	bool operator<=(const BigInteger &v) const {
		return !(v < *this);
	}
	bool operator>=(const BigInteger &v) const {
		return !(*this < v);
	}
	bool operator==(const BigInteger &v) const {
		return !(*this < v) && !(v < *this);
	}
	bool operator!=(const BigInteger &v) const {
		return *this < v || v < *this;
	}
 
	void trim() {
		while (!a.empty() && !a.back())
			a.pop_back();
		if (a.empty())
			sign = 1;
	}
 
	bool isZero() const {
		return a.empty() || (a.size() == 1 && !a[0]);
	}
 
	BigInteger operator-() const {
		BigInteger res = *this;
		res.sign = -sign;
		return res;
	}
 
	BigInteger abs() const {
		BigInteger res = *this;
		res.sign *= res.sign;
		return res;
	}
 
 
	friend ostream& operator<<(ostream &stream, const BigInteger &v) {
		if (v.sign == -1)
			stream << '-';
		stream << (v.a.empty() ? 0 : v.a.back());
		for (signed i = (signed) v.a.size() - 2; i >= 0; --i)
			stream << setw(base_digits) << setfill('0') << v.a[i];
		return stream;
	}
 
};
/*
  #######################   THE   BIG   INT   ##########################
  ######################################################################
*/
#define ll BigInteger
int n;
ll get(int start) {
  int sum = 0; ll cur = 1;
  for (int i = start;; ++i) {
    sum += i; cur *= i;
    if (sum == n) return cur;
    if (sum > n) break;
  }
  sum = 0, cur = 1;
  for (int divi = start;; ++divi) {
    sum += divi; cur *= divi;
    if (sum > n) return 0;
    int csum = sum; ll ccur = cur;
    for (int i = divi + 2;; ++i) {
      csum += i; ccur *= i;
      if (csum == n) return ccur;
      if (csum > n) break;
    }
  }
  return 0;
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  if (n == 1)
    return cout << 1, 0;
  if (n == 4)
    return cout << 4, 0;
  cout << max(get(2), get(3));
	return 0;
}


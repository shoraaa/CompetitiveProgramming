#include <bits/stdc++.h>
using namespace std;
 
template <class T = int>
class big_integer : private basic_string <T> {
private:
    static const int base = 1000; bool sign;

    void fix(){
        this->push_back(0);
        for (int i = 0; i < int(this->size()) - 1; i++){
            this->at(i + 1) += this->at(i) / base;
            this->at(i) %= base;
            if (this->at(i) < 0){
                this->at(i) += base; this->at(i + 1)--;
            }
        }
        while (!this->empty() && this->back() == 0) this->pop_back();
    }

public:
    big_integer(): sign(true){}

    big_integer(int x){
        sign = x < 0 ? x = -x, false : true;
        while (x > 0){
            this->push_back(x % base); x /= base;
        }
        this->fix();
    }

    big_integer(long long x){
        sign = x < 0 ? x = -x, false : true;
        while (x > 0){
            this->push_back(x % base); x /= base;
        }
        this->fix();
    }

    big_integer(const string &s){
        sign = s[0] == '-' ? false : true;
        this->resize(s.size() / 3 + 1);
        for (int i = sign ? 0 : 1, pos; s[i]; i++){
            pos = (s.size() - i - 1) / 3;
            this->at(pos) = this->at(pos) * 10 + s[i] - '0';
        }
        this->fix();
    }
    friend big_integer operator - (const big_integer &a){
        big_integer res = a; res.sign ^= 1; return res;
    }

    friend int comp(const big_integer &a, const big_integer &b){
        if (a.sign != b.sign) return a.sign < b.sign ? -1 : 1;
        if (a.size() != b.size())
            return (a.size() - b.size()) * (a.sign ? 1 : -1);
        for (int i = a.size() - 1; ~i; i--)
            if (a[i] != b[i]) return (a[i] - b[i]) * (a.sign ? 1 : -1);
        return 0;
    }

    friend ostream& operator << (ostream &os, const big_integer &a){
        if (a.empty()) return os << "0";
        if (!a.sign) os << '-'; os << a.back();
        for (int i = a.size() - 2; ~i; i--)
            os << setw(3) << setfill('0') << a[i];
        return os;
    }

    friend istream& operator >> (istream &is, big_integer &a){
        string s; is >> s; a = big_integer(s); return is;
    }

    friend string to_string(const big_integer &a){
        if (a.empty()) return "0"; stringstream ss;
        if (!a.sign) ss << '-'; ss << a.back();
        for (int i = a.size() - 2; ~i; i--)
            ss << setw(3) << setfill('0') << a[i];
        return ss.str();
    }

    friend bool operator < (const big_integer &a, const big_integer &b){
        return comp(a, b) < 0;
    }

    friend bool operator <= (const big_integer &a, const big_integer &b){
        return comp(a, b) <= 0;
    }

    friend bool operator > (const big_integer &a, const big_integer &b){
        return comp(a, b) > 0;
    }
    friend bool operator >= (const big_integer &a, const big_integer &b){
        return comp(a, b) >= 0;
    }

    friend big_integer operator + (const big_integer &a, const big_integer &b){
        if (a.sign && !b.sign) return a - -b;
        if (!a.sign && b.sign) return b - -a;
        big_integer res = a; res.resize(max(a.size(), b.size()));
        for (int i = 0; i < int(b.size()); i++) res[i] += b[i];
        res.fix(); return res;
    }

    friend big_integer operator - (const big_integer &a, const big_integer &b){
        if (a.sign && !b.sign) return a + -b;
        if (!a.sign && b.sign) return -(b + -a);
        if (!a.sign && !b.sign) return -(-a - -b);
        if (a > b){
            big_integer res = a;
            for (int i = 0; i < int(b.size()); i++) res[i] -= b[i];
            res.fix(); return res;
        }
        else {
            big_integer res = b;
            for (int i = 0; i < int(a.size()); i++) res[i] -= a[i];
            res.fix(); res.sign = 0; return res;
        }
    }

    friend big_integer operator * (const big_integer &a, const big_integer &b){
        big_integer res; res.resize(a.size() + b.size());
        for (int i = 0; i < int(a.size()); i++)
            for (int j = 0; j < int(b.size()); j++)
                res[i + j] += a[i] * b[j];
        res.sign = a.sign == b.sign; res.fix(); return res;
    }

    friend void operator += (big_integer &a, const big_integer &b){
        a = a + b;
    }

    friend void operator -= (big_integer &a, const big_integer &b){
        a = a - b;
    }

    friend void operator *= (big_integer &a, const big_integer &b){
        a = a * b;
    }
};
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    big_integer <int> a, b; cin >> a >> b;
    cout << a + b << '\n' << a - b << '\n' << a * b << '\n';
}
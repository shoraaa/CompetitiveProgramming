#include<bits/stdc++.h>
using namespace std;
using ll = long long;

void ABC(int n);
void ACB(int n);
void BCA(int n);
void BAC(int n);
void CAB(int n);
void CBA(int n);

string s;

void CBA(int n) {
  if (n == 0) return;
  CAB(n - 1);
  ABC(n - 1);
  s += 'C';
  BCA(n - 1);
  s += 'A';
  CBA(n - 1);
}

void CAB(int n) {
  if (n == 0) return;
  CBA(n - 1);
  s += 'C';
  BAC(n - 1);
}

void BAC(int n) {
  if (n == 0) return;
  BCA(n - 1);
  CAB(n - 1);
  s += 'B';
  ABC(n - 1);
  s += 'C';
  BAC(n - 1);
}

void BCA(int n) {
  if (n == 0) return;
  BAC(n - 1);
  s += 'B';
  ACB(n - 1);
}

void ABC(int n) {
  if (n == 0) return;
  ACB(n - 1);
  s += 'A';
  CBA(n - 1);
}

void ACB(int n) {
  if (n == 0) return;
  ABC(n - 1);
  BCA(n - 1);
  s += 'A';
  CAB(n - 1);
  s += 'B';
  ACB(n - 1);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int n; cin >> n;
  ACB(n);
  cout << s;
	return 0;
}


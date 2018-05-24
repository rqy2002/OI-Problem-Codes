/**************************************************************
 * Problem: JCYZOJ 1001
 * Author: Rqy
 * Date: 2018 Feb 13
 * Algorithm: Miller-Rabin, Pollard-Rho
**************************************************************/
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <map>
typedef long long LL;
inline LL readInt() {
  LL ans = 0;
  int x;
  while (!isdigit(x = getchar()));
  do ans = ans * 10 + x - '0';
  while (isdigit(x = getchar()));
  return ans;
}
inline LL abs(LL a) { return a >= 0 ? a : -a; }
inline LL gcd(LL a, LL b) {
  while (b) std::swap(a %= b, b);
  return a;
}
inline LL mul(LL a, LL b, LL p) {
  LL ans = 0;
  for (; b; b >>= 1, a = (a + a) % p)
    if (b & 1) ans = (ans + a) % p;
  return ans;
}
inline LL pow(LL a, LL b, LL p) {
  LL ans = 1;
  for (; b; b >>= 1, a = mul(a, a, p))
    if (b & 1) ans = mul(ans, a, p);
  return ans;
}
bool check(LL n, LL a) {
  LL t = n - 1, p = 0;
  while (~t & 1) {
    t >>= 1;
    ++p;
  }
  a = pow(a, t, n);
  while (p--) {
    LL a1 = mul(a, a, n);
    if (a1 == 1) return a == 1 || a == n - 1;
    a = a1;
  }
  return false;
}
bool Miller_Rabin(LL n) {
  if (n == 1) return false;
  const int a[6] = { 2, 3, 5, 7, 11, 167 };
  for (int i = 0; i < 6; ++i) {
    if (!(n % a[i])) return n == a[i];
    if (!check(n, a[i])) return false;
  }
  return true;
}
std::map<LL, int> S;
LL get(LL n, LL a) {
  LL x = 0, y = a;
  while (x != y) {
    LL d = gcd(abs(x - y), n);
    if (d != 1 && d != n) return d;
    x = (mul(x, x, n) + a) % n;
    if ((y = (mul(y, y, n) + a) % n) == x) return n;
    y = (mul(y, y, n) + a) % n;
  }
  return n;
}
void Pollard_Rho(LL n) {
  if (Miller_Rabin(n)) {
    if (!S.count(n)) S[n] = 0;
    ++S[n];
    return;
  }
  if (~n & 1) {
    if (!S.count(2)) S[2] = 0;
    ++S[2];
    Pollard_Rho(n / 2);
    return;
  }
  for (LL a = 2;; ++a) {
    LL d = get(n, a);
    if (d != n) {
      Pollard_Rho(d);
      Pollard_Rho(n / d);
      return;
    }
  }
}
inline LL getP(LL n, LL p) {
  LL ans = 0;
  while (n) ans += (n /= p);
  return ans;
}
int main() {
  S.clear();
  LL n = readInt();
  Pollard_Rho(readInt());
  LL ans = n;
  for (std::map<LL, int>::iterator it = S.begin(); it != S.end(); ++it)
    ans = std::min(ans, getP(n, it->first) / it->second);
  printf("%lld\n", ans);
  return 0;
}

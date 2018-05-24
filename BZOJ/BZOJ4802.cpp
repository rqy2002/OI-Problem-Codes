/**************************************************************
 * Problem: BZOJ4802
 * Author: Rqy
 * Date: 2018 Feb 23
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <set>
typedef long long LL;
LL mul_mod(LL a, LL b, LL n) {
  LL ans = 0;
  for (; b; b >>= 1, a = a * 2 % n)
    if (b & 1) ans = (ans + a) % n;
  return ans;
}
LL pow_mod(LL a, LL b, LL n) {
  LL ans = 1;
  for (; b; b >>= 1, a = mul_mod(a, a, n))
    if (b & 1) ans = mul_mod(ans, a, n);
  return ans;
}
bool check(LL n, LL a) {
  LL t = n - 1, k = 0;
  while (~t & 1) { ++k; t >>= 1; }
  a = pow_mod(a, t, n);
  if (a == 1) return true;
  while (k--) {
    LL b = mul_mod(a, a, n);
    if (b == 1) return a == n - 1;
    a = b;
  }
  return false;
}
bool MillerRabin(LL n) {
  if (n == 1) return false;
  const int p[10] = {2, 3, 5, 7, 11, 13, 17, 19, 21, 167};
  for (int i = 0; i < 10; ++i)
    if (!(n % p[i])) return n == p[i];
    else if (!check(n, p[i])) return false;
  return true;
}
LL gcd(LL a, LL b) {
  while (b) std::swap(a %= b, b);
  return a;
}
std::set<LL> S;
LL get(LL n, LL c) {
  LL x = 0, y = c;
  while (true) {
    x = (mul_mod(x, x, n) + c) % n;
    y = (mul_mod(y, y, n) + c) % n;
    LL d = gcd(std::abs(y - x), n);
    if (d != 1) return d;
    y = (mul_mod(y, y, n) + c) % n;
    d = gcd(std::abs(y - x), n);
    if (d != 1) return d;
  }
}
void PollardRho(LL n) {
  while (~n & 1) {
    n >>= 1;
    S.insert(2);
  }
  if (n == 1) return;
  if (MillerRabin(n)) {
    S.insert(n);
    return;
  }
  LL d = n, c = 2;
  while (d >= n) d = get(n, c++);
  PollardRho(d);
  PollardRho(n / d);
}
int main() {
  LL n;
  scanf("%lld", &n);
  S.clear();
  PollardRho(n);
  for (std::set<LL>::iterator it = S.begin(); it != S.end(); ++it)
    n = n / *it * (*it - 1);
  printf("%lld\n", n);
  return 0;
}

/**************************************************************
 * Problem: BZOJ5118.cpp
 * Author: Rqy
 * Date: 2018 Feb 27
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
typedef long long LL;
const LL mod = 1125899839733759LL;
LL mul(LL a, LL n, LL p) {
  LL ans = 0;
  for (; n; n >>= 1, a = a * 2 % p)
    if (n & 1) ans = (ans + a) % p;
  return ans;
}
LL pow_mod(LL a, LL n, LL p) {
  LL ans = 1;
  for (; n; n >>= 1, a = mul(a, a, p))
    if (n & 1) ans = mul(ans, a, p);
  return ans;
}
struct M{
  LL a, b, c, d;
  M(LL a, LL b, LL c, LL d) : a(a % mod), b(b % mod), c(c % mod), d(d % mod) {}
  friend M operator*(const M &a, const M &b) {
    return M(
        mul(a.a, b.a, mod) + mul(a.b, b.c, mod),
        mul(a.a, b.b, mod) + mul(a.b, b.d, mod),
        mul(a.c, b.a, mod) + mul(a.d, b.c, mod),
        mul(a.c, b.b, mod) + mul(a.d, b.d, mod));
  }
};
int main() {
  int T;
  LL n;
  scanf("%d", &T);
  while (T--) {
    scanf("%lld", &n);
    M x(1, 1, 1, 0), ans(1, 0, 0, 1);
    n = pow_mod(2, n, mod - 1);
    for (; n; n >>= 1, x = x * x)
      if (n & 1) ans = ans * x;
    printf("%lld\n", ans.b);
  }
  return 0;
}

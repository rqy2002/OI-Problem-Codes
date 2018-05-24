/**************************************************************
 * Problem: BZOJ2875
 * Author: Rqy
 * Date: 2018 Feb 25
 * Algorithm: 
**************************************************************/
#include <cstdio>
typedef long long LL;
LL m, a, c, g;
LL mult(LL a, LL b) {
  LL ans = 0;
  for (; b; b >>= 1, a = a * 2 % m)
    if (b & 1) ans = (ans + a) % m;
  return ans;
}
struct P{
  LL a, b;
  P(LL a, LL b) : a(a), b(b) {}
  friend P operator*(const P &x, const P &y) {
    return P(mult(x.a, y.a), (mult(x.a, y.b) + x.b) % m);
  }
};
int main() {
  LL x0, n;
  scanf("%lld%lld%lld%lld%lld%lld", &m, &a, &c, &x0, &n, &g);
  P x(a, 1), ans(1, 0);
  for (; n; n >>= 1, x = x * x)
    if (n & 1) ans = ans * x;
  printf("%lld\n", (mult(ans.a, x0) + mult(ans.b, c)) % m % g);
  return 0;
}

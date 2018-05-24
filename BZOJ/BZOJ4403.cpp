/**************************************************************
 * Problem: BZOJ4403
 * Author: Rqy
 * Date: 2018 Feb 27
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int mod = 1000003;
typedef long long LL;
LL fac[mod], invfac[mod];
LL C(LL a, LL b) {
  if (a < b) return 0;
  return fac[a] * invfac[b] % mod * invfac[a - b] % mod;
}
LL Lucas(LL a, LL b) {
  if (!b) return 1;
  return C(a % mod, b % mod) * Lucas(a / mod, b / mod) % mod;
}
int main() {
  fac[0] = 1;
  for (int i = 1; i < mod; ++i) fac[i] = fac[i - 1] * i % mod;
  invfac[mod - 1] = mod - 1;
  for (int i = mod - 1; i; --i) invfac[i - 1] = invfac[i] * i % mod;
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, l, r;
    scanf("%d%d%d", &n, &l, &r);
    printf("%lld\n", (Lucas(n + r - l + 1, n) - 1 + mod) % mod);
  }
}

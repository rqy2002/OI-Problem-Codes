/**************************************************************
 * Problem: BZOJ3207
 * Author: Rqy
 * Date: 2018 Feb 27
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int mod = 10000007;
typedef long long LL;
const int N = 60;
LL f[N][N][2];
LL pow_mod(LL a, LL b) {
  LL ans = 1;
  for (; b; b >>= 1, a = a * a % mod)
    if (b & 1) ans = ans * a % mod;
  return ans;
}
int main() {
  LL n;
  scanf("%lld", &n);
  ++n;
  int k = 0;
  while ((1LL << k) <= n) ++k;
  f[k][0][0] = 1;
  for (int i = k; i; --i)
    for (int a = 0; a < k; ++a)
      for (int b = 0; b < 2; ++b)
        for (int c = 0; c < 2; ++c)
          if (!(c == 1 && b == 0 && ((~n >> (i - 1))) & 1))
            f[i - 1][a + c][b || (c < ((n >> (i - 1)) & 1))] += f[i][a][b];
  LL ans = 1;
  for (int i = 1; i < k; ++i)
    ans = ans * pow_mod(i, f[0][i][1]) % mod;
  printf("%lld\n", ans);
  return 0;
}

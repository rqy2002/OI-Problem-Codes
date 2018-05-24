/**************************************************************
 * Problem: BZOJ4475
 * Author: Rqy
 * Date: 2018 Feb 22
 * Algorithm: 
**************************************************************/
#include <cstdio>
typedef long long LL;
const int mod = 1000000007;
int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  int ans = 1, x = 2;
  for (n = (LL)n * k % (mod - 1); n; n >>= 1, x = (LL)x * x % mod)
    if (n & 1) ans = (LL)ans * x % mod;
  return printf("%d\n", ans) & 0;
}


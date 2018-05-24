/**************************************************************
 * Problem: BZOJ2431
 * Author: Rqy
 * Date: 2018 Feb 22
 * Algorithm: 
**************************************************************/
#include <cstdio>
const int N = 1050;
const int mod = 10000;
int f[N][N];
int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  f[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    f[i][0] = 1;
    for (int j = 1; j <= k; ++j) {
      f[i][j] = f[i][j - 1] + f[i - 1][j];
      if (j >= i) f[i][j] -= f[i - 1][j - i];
      f[i][j] %= mod;
    }
  }
  printf("%d\n", (f[n][k] + mod) % mod);
  return 0;
}

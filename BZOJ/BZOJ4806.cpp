/**************************************************************
 * Problem: BZOJ4806
 * Author: Rqy
 * Date: 2018 Feb 24
 * Algorithm: 
**************************************************************/
#include <cstdio>
#include <cstring>
const int N = 105;
const int mod = 999983;
typedef long long LL;
#define add(x, y) ((x) = ((x) + (y)) % mod)
#define C2(x) ((LL)(x) * ((x) - 1) / 2 % mod)
int n, m, f[N][N][N];
int main() {
  scanf("%d%d", &n, &m);
  memset(f, 0, sizeof f);
  f[0][0][0] = 1;
  for (int i = 0; i < n; ++i)
    for (int b = 0; b <= 2 * i && b <= m; ++b)
      for (int c = 0; b + 2 * c <= 2 * i && b + c <= m; ++c) {
        LL t = f[i][b][c];
        int a = m - b - c;
        // 0
        add(f[i + 1][b][c], t);
        // 1
        if (a) add(f[i + 1][b + 1][c], t * a % mod);
        if (b) add(f[i + 1][b - 1][c + 1], t * b % mod);
        // 2
        if (a > 1) add(f[i + 1][b + 2][c], t * C2(a) % mod);
        if (a && b) add(f[i + 1][b][c + 1], t * a % mod * b % mod);
        if (b > 1) add(f[i + 1][b - 2][c + 2], t * C2(b) % mod);
      }
  int ans = 0;
  for (int b = 0; b <= 2 * n && b <= m; ++b)
    for (int c = 0; b + 2 * c <= 2 * n && b + c <= m; ++c)
      add(ans, f[n][b][c]);
  printf("%d\n", ans);
  return 0;
}

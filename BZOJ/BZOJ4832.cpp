/**************************************************************
 * Problem: BZOJ4832
 * Author: Rqy
 * Date: 2018 Feb 26
 * Algorithm: 
**************************************************************/
#include <cstdio>
const int N = 55;
const int T = 8;
double f[N][T][T][T];
int main() {
  for (int i = 1; i <= 50; ++i)
    for (int a = 0; a <= 7; ++a)
      for (int b = 0; a + b <= 7; ++b)
        for (int c = 0; a + b + c <= 7; ++c) {
          int s = a + b + c + 1;
          double &ans = f[i][a][b][c];
          ans = 1.0 / s * (1.0 + f[i - 1][a][b][c]);
          if (a) ans += ((double)a / s) * f[i - 1][a - 1][b][c];
          if (b) ans += ((double)b / s) * f[i - 1][a + 1][b - 1][c + (s < 8)];
          if (c) ans += ((double)c / s) * f[i - 1][a][b + 1][c - 1 + (s < 8)];
        }
  int T, k, a, b, c;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &k, &a, &b, &c);
    printf("%.2lf\n", f[k][a][b][c]);
  }
  return 0;
}

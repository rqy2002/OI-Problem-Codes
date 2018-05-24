/**************************************************************
 * Problem: Luogu P3396
 * Author: Rqy
 * Date: 2017 Dec 23
 * Algorithm: 分块
**************************************************************/
#include <cstdio>
const int N = 150050;
const int sN = 400;
int f[sN][sN], A[N];
char ss[5];
int main() {
  int n, m, s = 0;
  scanf("%d%d", &n, &m);
  while (s * s < n) ++s;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &A[i]);
    for (int j = 1; j <= s; ++j)
      f[j][i % j] += A[i];
  }
  int x, y;
  while (m--) {
    scanf("%s%d%d", ss, &x, &y);
    if (*ss == 'A') {
      if (x <= s) printf("%d\n", f[x][y]);
      else {
        int ans = 0;
        for (int i = y; i <= n; i += x)
          ans += A[i];
        printf("%d\n", ans);
      }
    } else {
      for (int j = 1; j <= s; ++j)
        f[j][x % j] += y - A[x];
      A[x] = y;
    }
  }
  return 0;
}

/**************************************************************
 * Problem: BZOJ3997
 * Author: Rqy
 * Date: 2018 Feb 22
 * Algorithm: DP
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 1050;
int A[N][N], f[N][N];
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    memset(f, 0, sizeof f);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        scanf("%d", &A[i][j]);
    for (int i = 0; i < n; ++i)
      for (int j = m - 1; ~j; --j) {
        f[i][j] = std::max(A[i][j], f[i][j + 1]);
        if (i) {
          f[i][j] = std::max(f[i][j], f[i - 1][j + 1] + A[i][j]);
          f[i][j] = std::max(f[i][j], f[i - 1][j]);
        }
      }
    printf("%d\n", f[n - 1][0]);
  }
  return 0;
}

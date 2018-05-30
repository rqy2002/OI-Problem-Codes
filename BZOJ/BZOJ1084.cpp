#include <algorithm>
#include <cstdio>
using std::max;
int f[105][15][5];
inline int max(int a, int b, int c) {
  return max(max(a, b), c);
}
inline int max(int a, int b, int c, int d) {
  return max(max(a, b), max(c, d));
}
inline int max(int a, int b, int c, int d, int e) {
  return max(e, max(max(a, b), max(c, d)));
}
int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  if (m == 1) {
    int x;
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &x);
      for (int j = 0; j <= k; ++j) {
        f[i][j][0] = max(f[i - 1][j][0], f[i - 1][j][1]);
        if (j) f[i][j][1] = max(f[i - 1][j - 1][0], f[i - 1][j][1]) + x;
      }
    }
    printf("%d\n", max(f[n][k][0], f[n][k][1]));
  } else {
    int x, y;
    for (int i = 1; i <= n; ++i) {
      scanf("%d%d", &x, &y);
      for (int j = 0; j <= k; ++j) {
        int *now = f[i][j], *las = f[i - 1][j], *las1 = f[i - 1][j - 1], *las2 = f[i - 1][j - 2];
        now[0] = max(las[0], las[1], las[2], las[3], las[4]);
        if (j) {
          now[1] = max(las1[0], las[1], las1[2], las1[3], las[4]) + x;
          now[2] = max(las1[0], las1[1], las[2], las1[3], las[4]) + y;
          now[3] = max(las1[0], las1[1], las1[2], las[3], las1[4]) + x + y;
          if (j > 1)
            now[4] = max(las2[0], las1[1], las1[2], las2[3], las[4]) + x + y;
        }
      }
    }
    int *ans = f[n][k];
    printf("%d\n", max(ans[0], ans[1], ans[2], ans[3], ans[4]));
  }
  return 0;
}

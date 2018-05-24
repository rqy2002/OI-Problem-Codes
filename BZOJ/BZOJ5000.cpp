/**************************************************************
 * Problem: BZOJ5000
 * Author: Rqy
 * Date: 2018 Feb 28
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cctype>
#include <cstdio>
const int N = 10050;
int a[32][N][30], b[32][N][30];
char s[200000];
int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j < k; ++j)
      scanf("%d%d", &a[0][i][j], &b[0][i][j]);
  int p;
  scanf("%s%d", s, &p);
  for (int t = 1; t < 32; ++t)
    for (int i = 1; i <= n; ++i)
      for (int j = 0; j < k; ++j) {
        a[t][i][j] = a[t - 1][a[t - 1][i][j]][j];
        b[t][i][j] = b[t - 1][i][j] + b[t - 1][a[t - 1][i][j]][j];
        if (b[t][i][j] >= p) b[t][i][j] -= p;
      }
  int o = 1, ans = 0;
  char *c = s;
  while (*c) {
    int cnt, cc;
    if (*c == '[') {
      int t;
      sscanf(++c, "%d%n", &cnt, &t);
      c += t;
      cc = *(c++) - 'A';
      c++;
    } else {
      cnt = 1;
      cc = *(c++) - 'A';
    }
    for (int i = 0; i < 32; ++i)
      if ((cnt >> i) & 1) {
        if ((ans += b[i][o][cc]) >= p) ans -= p;
        o = a[i][o][cc];
      }
  }
  printf("%d\n", ans);
  return 0;
}

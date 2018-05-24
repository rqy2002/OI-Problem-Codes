/**************************************************************
 * Problem: BZOJ1260
 * Author: Rqy
 * Date: 2018 Feb 25
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 55;
char s[N];
int f[N][N];
int main() {
  scanf("%s", s);
  int n = strlen(s);
  for (int i = 0; i < n; ++i) f[i][i] = 1;
  for (int l = 2; l <= n; ++l)
    for (int i = 0; i + l <= n; ++i) {
      int j = i + l - 1;
      f[i][j] = l;
      for (int k = i; k < j; ++k)
        f[i][j] = std::min(f[i][j], f[i][k] + f[k + 1][j]);
      if (s[i] == s[j])
        f[i][j] = std::min(f[i][j], std::min(f[i + 1][j - 1] + 1, std::min(f[i + 1][j], f[i][j - 1])));
    }
  printf("%d\n", f[0][n - 1]);
  return 0;
}

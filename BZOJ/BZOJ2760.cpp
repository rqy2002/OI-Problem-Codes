/**************************************************************
 * Problem: BZOJ2760
 * Author: Rqy
 * Date: 2018 Feb 26
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 105;
char T[N][N][N];
int m[N], len[N][N], width[N];
inline int getLen(char *s) {
  int ans = 1;
  while (*s) ans += (*(s++) == ',');
  return ans;
}
int main() {
  int n;
  scanf("%d", &n);
  int h = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &m[i]);
    ++m[i];
    h = std::max(h, m[i]);
    width[i] = 0;
    for (int j = 0; j < m[i]; ++j) {
      scanf("%s", T[i][j]);
      len[i][j] = getLen(T[i][j]);
      width[i] = std::max(width[i], len[i][j]);
    }
    width[i] += (i != n - 1);
  }
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < n; ++j) {
      printf("%s", i >= m[j] ? "" : T[j][i]);
      int x = i >= m[j] ? 1 : len[j][i];
      while (x < width[j]) {
        putchar(',');
        ++x;
      }
    }
    putchar('\n');
  }
  return 0;
}

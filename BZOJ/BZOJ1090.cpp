#include <algorithm>
#include <cstdio>
#include <cstring>
using std::min;
char s[105];
inline bool eq(int b1, int b2, int len) {
  return !strncmp(s + b1, s + b2, len);
}
inline int wei(int x) {
  int t = 1;
  while (x /= 10) ++t;
  return t;
}
int f[105][105];
int main() {
  scanf("%s", s);
  int n = strlen(s);
  for (int len = 1; len <= n; ++len)
    for (int i = 0; i + len <= n; ++i) {
      int j = i + len;
      f[i][j] = len;
      for (int k = i + 1; k < j; ++k) {
        f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
        if (!(len % (k - i)) && eq(i, k, j - k))
          f[i][j] = min(f[i][j], f[i][k] + 2 + wei(len / (k - i)));
      }
    }
  printf("%d\n", f[0][n]);
  return 0;
}

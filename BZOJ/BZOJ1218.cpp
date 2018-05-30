#include <cstdio>
const int N = 5005;
int s[N][N];
int main() {
  int n, r, mx, my, x, y, v;
  scanf("%d%d", &n, &r);
  mx = r; my = r;
  for (int i = 0; i < n; ++i) {
    scanf("%d%d%d", &x, &y, &v);
    s[++y][++x] += v;
    if (x > mx) mx = x;
    if (y > my) my = y;
  }
  int ans = 0;
  for (int i = 1; i <= my; ++i)
    for (int j = 1; j <= mx; ++j) {
      s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
      if (i >= r && j >= r) {
        int a = s[i][j] - s[i - r][j] - s[i][j - r] + s[i - r][j - r];
        if (a > ans) ans = a;
      }
    }
  printf("%d\n", ans);
  return 0;
}

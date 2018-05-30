#include <cstdio>
int n, m;
int num[500], tmp[500];
bool judge() {
  for (int d = 1; d <= n; ++d)
    if (num[d] >= 2) {
      int i;
      for (i = 1; i <= n + 2; ++i) tmp[i] = num[i];
      tmp[d] -= 2;
      for (i = 1; i <= n + 2; ++i) {
        if (tmp[i] < 0) break;
        tmp[i] %= 3;
        tmp[i + 1] -= tmp[i];
        tmp[i + 2] -= tmp[i];
      }
      if (i == n + 3) return true;
    }
  return false;
}
int main() {
  scanf("%d%d", &n, &m);
  int x;
  for (int i = 0; i < 3 * m + 1; ++i) {
    scanf("%d", &x);
    ++num[x];
  }
  bool f = 1;
  for (int i = 1; i <= n; ++i) {
    ++num[i];
    if (judge()) {
      if (!f) putchar(' ');
      else f = 0;
      printf("%d", i);
    }
    --num[i];
  }
  if (f) puts("NO");
  return 0;
}

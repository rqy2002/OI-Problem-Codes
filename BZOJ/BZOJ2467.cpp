#include <cstdio>
int main() {
  int T, n;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    int ans = 4 * n;
    while (--n) ans = ans * 5 % 2007;
    printf("%d\n", ans);
  }
  return 0;
}

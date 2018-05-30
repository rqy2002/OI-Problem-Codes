#include<cstdio>
#include<algorithm>
int a[10005], n;
int main() {
  int i, j;
  scanf("%d", &n);
  for (i = 0; i < n; ++i) scanf("%d", &a[i]);
  int ans = 0;
  for (i = std::max(a[0] - 1, 0); i <= a[0] && i <= 1; ++i) {
    int t1 = i, t2 = a[0] - t1;
    bool ok = true;
    for (j = 1; j < n; ++j) {
      int t3 = a[j] - t2 - t1;
      if (t3 < 0 || t3 > 1) {
        ok = false;
        break;
      }
      t1 = t2;
      t2 = t3;
    }
    if (ok && !t2) ++ans;
  }
  printf("%d", ans);
  return 0;
}

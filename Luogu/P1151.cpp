#include <cstdio>
int main() {
  int k;
  scanf("%d", &k);
  bool ok = false;
  for (int i = 10000; i <= 30000; ++i) {
    int a = i / 100, b = i / 10 % 1000, c = i % 1000;
    if (a % k == 0 && b % k == 0 && c % k == 0) {
      printf("%d\n", i);
      ok = true;
    }
  }
  if (!ok) puts("No");
  return 0;
}

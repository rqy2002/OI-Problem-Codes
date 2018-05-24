#include <cstdio>
int main() {
  int n = 0;
  scanf("%d", &n);
  for (int i = 0, j = 0, t; j < n * n; ++i, t ^= 1) {
    scanf("%d", &t);
    while (t--) {
      printf("%d", i % 2);
      if (!((++j) % n)) puts("");
    }
  }
  return 0;
}

#include <cstdio>
int main() {
  int T, n, x, y, t;
  for (scanf("%d", &T); T; --T) {
    for (scanf("%d", &n), y = t = 0; n; --n) {
      scanf("%d", &x);
      y ^= x;
      t |= x > 1;
    }
    puts((!!y ^ t) ? "Brother" : "John");
  }
  return 0;
}

#include <cstdio>
int main() {
  int x, t = 1;
  scanf("%d", &x);
  while (x /= 2) ++t;
  return printf("%d\n", t), 0;
}

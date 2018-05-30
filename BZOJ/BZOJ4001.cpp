#include <algorithm>
#include <cstdio>
int main() {
  double n;
  scanf("%lf", &n);
  printf("%.9lf", n * (n + 1) / 2 / (2 * n - 1));
  return 0;
}

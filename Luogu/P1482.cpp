#include <algorithm>
#include <cstdio>
int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }
int main() {
  int a, b, c, d;
  scanf("%d/%d%d/%d", &a, &b, &c, &d);
  a *= c;
  b *= d;
  printf("%d %d", b / gcd(a, b), a / gcd(a, b));
  return 0;
}

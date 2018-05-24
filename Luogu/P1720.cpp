#include <algorithm>
#include <cstdio>
int main() {
  int n;
  scanf("%d", &n);
  long long a = 0, b = 1;
  while (n--)
    std::swap(a += b, b);
  printf("%lld.00\n", a);
  return 0;
}

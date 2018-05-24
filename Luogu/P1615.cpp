#include <algorithm>
#include <cstdio>
int main() {
  int a, b, c, d, e, f, k;
  scanf("%d:%d:%d", &a, &b, &c);
  scanf("%d:%d:%d", &d, &e, &f);
  scanf("%d", &k);
  printf("%lld\n", (long long)(((d - a) * 60 + (e - b)) * 60 + (f - c)) * k);
  return 0;
}

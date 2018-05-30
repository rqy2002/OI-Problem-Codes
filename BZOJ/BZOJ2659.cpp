#include <cstdio>
typedef long long LL;
int main() {
  LL p, q;
  scanf("%lld%lld", &p, &q);
  if (p == q) printf("%lld\n", (p * p - 1) / 4);
  else printf("%lld\n", (p - 1) * (q - 1) / 4);
  return 0;
}

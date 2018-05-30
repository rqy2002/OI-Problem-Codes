#include <cmath>
#include <cstdio>
typedef long long LL;
LL gcd(LL a, LL b) {
  while (b) {
    LL t = b;
    b = a % b;
    a = t;
  }
  return a;
}
LL r;
inline bool check(LL d, LL A) {
  LL B = (LL)sqrt(2 * r / d - A * A);
  return A * A + B * B == 2 * r / d && gcd(A, B) == 1 && A != B;
}
int main() {
  scanf("%lld", &r);
  LL ans = 0;
  for (LL d = 1; d * d <= 2 * r; ++d)
    if (!(2 * r % d)) {
      for (LL A = 1; A * A <= r / d; ++A)
        ans += check(d, A);
      if (d * d != 2 * r)
        for (LL A = 1; A * A <= d / 2; ++A)
          ans += check(2 * r / d, A);
    }
  printf("%lld\n", (ans + 1) * 4);
  return 0;
}

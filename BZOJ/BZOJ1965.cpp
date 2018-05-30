#include <cstdio>
typedef long long LL;
LL l, m, n, t2;
const LL t = 100000;
LL mul(LL a, LL b) {
  LL a1 = a % t, b1 = b % t, a2 = a / t, b2 = b / t;
  return (a1 * b1 % n + (a1 * b2 + b1 * a2) % n * t % n + a2 * b2 % n * t2 % n) % n;
}
int main() {
  scanf("%lld%lld%lld", &n, &m, &l);
  ++n;
  t2 = t * t % n;
  LL x = n / 2 + 1;
  for (; m; m >>= 1, x = mul(x, x))
    if (m & 1) l = mul(l, x);
  printf("%lld\n", l);
  return 0;
}

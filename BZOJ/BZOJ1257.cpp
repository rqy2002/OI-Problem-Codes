#include <cstdio>
typedef long long LL;
inline LL get(LL t) {
  return t * (t + 1) / 2;
}
int main() {
  LL n, k;
  scanf("%lld%lld", &n, &k);
  LL ans = k * n;
  if (n > k) n = k;
  for (LL i = 1, end; i <= n; i = end + 1) {
    end = k / (k / i);
    if (end > n) end = n;
    ans -= k / i * (get(end) - get(i - 1));
  }
  printf("%lld\n", ans);
  return 0;
}

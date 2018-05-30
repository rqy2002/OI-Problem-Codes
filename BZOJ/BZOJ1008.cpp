#include <cstdio>
const int mod = 100003;
typedef long long LL;
LL pow_mod(LL a, LL b) {
  LL ans = 1;
  a %= mod;
  for (; b; b >>= 1, a = a * a % mod)
    if (b & 1) ans = ans * a % mod;
  return ans;
}
int main() {
  LL n, m;
  scanf("%lld%lld", &m, &n);
  printf("%lld\n",
         (pow_mod(m, n) - pow_mod(m - 1, n - 1) * m % mod + mod) % mod);
  return 0;
}

/**************************************************************
 * Problem: Luogu P2606
 * Author: Rqy
 * Date: 2017 Dec 28
 * Algorithm: DP,Lucas
**************************************************************/
#include <cstdio>
typedef long long LL;
const int N = 2000050;
int fac[N], inv[N];
int p;
LL C(int n, int m) {
  return (LL)fac[n] * inv[m] % p * inv[n - m] % p;
}
int Lucas(int n, int m) {
  if (n % p < m % p) return 0;
  if (!n) return 1;
  return C(n % p, m % p) * Lucas(n / p, m / p) % p;
}
int siz[N];
int main() {
  int n;
  scanf("%d%d", &n, &p);
  fac[0] = fac[1] = 1;
  inv[0] = inv[1] = 1;
  for (int i = 2; i <= n && i < p; ++i) {
    fac[i] = (LL)fac[i - 1] * i % p;
    inv[i] = p - (LL)(p / i) * inv[p % i] % p;
  }
  for (int i = 2; i <= n && i < p; ++i) inv[i] = (LL)inv[i] * inv[i - 1] % p;
  for (int i = n; i; --i) siz[i / 2] += (++siz[i]);
  int ans = 1;
  for (int i = 1; i <= n; ++i)
    ans = (LL)ans * Lucas(siz[i] - 1, siz[i << 1]) % p;
  printf("%d\n", ans);
  return 0;
}

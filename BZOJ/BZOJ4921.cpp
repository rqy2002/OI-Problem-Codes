/**************************************************************
 * Problem: BZOJ4921
 * Author: Rqy
 * Date: 2018 Feb 26
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
typedef long long LL;
const LL N = 100050;
const LL mod = 998244353;
LL A[N];
LL a[100], b[100], c[100], d[100];
inline LL gcd(LL a, LL b) { while (b) std::swap(a %= b, b); return a; }
int main() {
  LL n;
  scanf("%lld", &n);
  for (LL i = 0; i < n; ++i)
    scanf("%lld", &A[i]);
  LL m = 0, k = 0;
  a[m] = A[0]; b[m] = 1;
  for (LL i = 1; i < n; ++i) {
    if (A[i] % a[m]) a[m + 1] = gcd(A[i], a[m]), ++m;
    ++b[m];
  }
  c[k] = A[n - 1]; d[k] = 1;
  for (LL i = n - 2; ~i; --i) {
    if (A[i] % c[k]) c[k + 1] = gcd(A[i], c[k]), ++k;
    ++d[k];
  }
  LL ans = 0;
  for (LL i = 0; i <= m; ++i)
    for (LL j = 0; j <= k; ++j)
      ans = (ans + (LL)b[i] * d[j] % mod * gcd(a[i], c[j])) % mod;
  ans = (ans - (n * n + 3 * n - 2) / 2 % mod * a[m]) % mod;
  for (LL i = 0; i <= m; ++i)
    ans = (ans + (b[i] - !i - (i == m)) * a[i]) % mod;
  for (LL i = 0; i <= k; ++i)
    ans = (ans + (d[i] - !i - (i == k)) * c[i]) % mod;
  printf("%lld\n", (ans + mod) % mod);
  return 0;
}

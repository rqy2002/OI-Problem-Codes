/**************************************************************
 * Problem: BZOJ5015
 * Author: Rqy
 * Date: 2018 Feb 27
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int mod = 1000000007;
typedef long long LL;
const int N = 15;
LL pow_mod(LL a, LL b) {
  LL ans = 1;
  for (a %= mod; b; b >>= 1, a = a * a % mod)
    if (b & 1) ans = ans * a % mod;
  return ans;
}
LL g[N];
LL A[N][N];
void solve(int n) {
  for (int i = 0; i < n; ++i) {
    int j = i;
    while (!A[j][i]) ++j;
    LL inv = pow_mod(A[j][i], mod - 2);
    for (int k = i; k <= n; ++k) std::swap((A[j][k] *= inv) %= mod, A[i][k]);
    for (int j = i + 1; j < n; ++j)
      for (int k = n; k >= i; --k)
        A[j][k] = (A[j][k] - A[i][k] * A[j][i]) % mod;
  }
  for (int i = n - 1; i; --i)
    for (int j = i - 1; ~j; --j)
      A[j][n] = (A[j][n] - A[i][n] * A[j][i]) % mod;
}
int main() {
  LL n;
  int k;
  scanf("%lld%d", &n, &k);
  g[0] = 0;
  for (int i = 1; i <= k; ++i) {
    g[i] = (2 * g[i - 1] - pow_mod(i - 1, k) + pow_mod(i, k)) % mod;
    A[i - 1][k] = g[i];
    A[i - 1][0] = (1 << i) - 1;
    LL pi = i;
    for (int j = 1; j < k; ++j, pi = pi * i % mod)
      A[i - 1][j] = pi;
  }
  solve(k);
  LL ans = A[0][k] * (pow_mod(2, n) - 1);
  LL pn = n %= mod;
  for (int i = 1; i < k; ++i, pn = pn * n % mod)
    ans = (ans + pn * A[i][k]) % mod;
  printf("%lld\n", (ans + mod) % mod);
  return 0;
}

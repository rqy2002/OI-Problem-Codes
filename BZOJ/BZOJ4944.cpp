/**************************************************************
 * Problem: NOI2017 Pool
 * Author: Rqy
 * Date: 2018 Feb 26
 * Algorithm: DP + 矩阵 + 特征多项式优化
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int mod = 998244353;
typedef long long LL;
void exgcd(int a, int b, int &x, int &y) {
  if (!b) { x = 1; y = 0; return; }
  exgcd(b, a % b, y, x);
  y -= (a / b) * x;
}
inline int inv(int x) {
  int v;
  exgcd(x, mod, v, x);
  return v;
}
const int K = 1050;
LL _f[2][K], pq[K], g[K];
LL ans[K], tmp[K * 2], x[K];
LL dp[K];
void mul(LL *a, LL *b, int k) {
  memset(tmp, 0, sizeof tmp);
  for (int i = 0; i < k; ++i) if (a[i])
    for (int j = 0; j < k; ++j)
      tmp[i + j] = (tmp[i + j] + a[i] * b[j]) % mod;
  for (int i = k * 2; i >= k; --i)
    for (int j = 0; j < k; ++j)
      tmp[i - j - 1] = (tmp[i - j - 1] + tmp[i] * dp[j]) % mod;
  for (int i = 0; i < k; ++i) a[i] = tmp[i];
}
LL solve(int n, int k, int q) {
  pq[0] = 1;
  for (int i = 1; i <= k; ++i) pq[i] = q * pq[i - 1] % mod;
  LL *f = _f[0], *f2 = _f[1];
  std::fill(f2, f2 + k + 1, 0);
  f2[0] = 1;
  for (int j = k; j; --j, std::swap(f, f2)) {
    std::fill(f, f + k + 1, 0);
    for (int i = 0; i * j < k; ++i) {
      f[i] = pq[i] * f2[i] % mod;
      for (int t = 0; t < i; ++t)
        f[i] = (pq[t] * (1 - q) % mod * f2[t] % mod
                * f[i - t - 1] % mod + f[i]) % mod;
    }
  }
  g[0] = 1;
  for (int i = 1; i < k; ++i) {
    g[i] = (1 - q) * g[i - 1] % mod;
    for (int j = 1; j < k && j <= i; ++j) {
      LL t = (LL)pq[j] * f2[j] % mod;
      if (j == i)
        g[i] = (g[i] + t) % mod;
      else
        g[i] = (g[i] + t * (1 - q) % mod * g[i - j - 1] % mod) % mod;
    }
  }
  memset(ans, 0, sizeof ans);
  memset(x, 0, sizeof x);
  ans[0] = 1;
  x[1] = 1;
  if (k == 1) x[0] = 1 - q;
  dp[0] = 1 - q;
  for (int i = 1; i < k; ++i)
    dp[i] = (LL)pq[i] * f2[i] % mod * (1 - q) % mod;
  for (; n; n >>= 1, mul(x, x, k))
    if (n & 1) mul(ans, x, k);
  LL ansv = 0;
  for (int i = 0; i < k; ++i)
    ansv = (ansv + ans[i] * g[i]) % mod;
  return (ansv + mod) % mod;
}
int main() {
  int n, k, x, y;
  scanf("%d%d%d%d", &n, &k, &x, &y);
  x = (LL)x * inv(y) % mod;
  printf("%lld\n", (solve(n, k + 1, x) - solve(n, k, x) + mod) % mod);
  return 0;
}


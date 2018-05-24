/**************************************************************
 * Problem: BZOJ3601
 * Author: Rqy
 * Date: 2018 Feb 23
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int D = 105;
const int mod = 1000000007;
typedef long long LL;
inline LL pow_mod(LL a, LL b) {
  LL ans = 1;
  for (a %= mod, (b += mod - 1) %= mod - 1; b; b >>= 1, a = a * a % mod)
    if (b & 1) ans = ans * a % mod;
  return ans;
}
inline LL inv(LL a) { return pow_mod(a, -1); }
int d;
LL a[D];
void solve() {
  static LL A[D][D];
  LL t = 0;
  for (int i = 0; i <= d; ++i) {
    LL j = 1;
    for (int k = 0; k <= d; ++k) A[i][k] = j = j * (i + 1) % mod;
    A[i][d + 1] = ((t += d ? A[i][d - 1] : 1) %= mod);
  }
  for (int i = 0; i <= d; ++i) {
    int j = i;
    while (!A[j][i]) ++j;
    for (int k = i; k <= d + 1; ++k) std::swap(A[i][k], A[j][k]);
    LL inv1 = inv(A[i][i]);
    for (int j = i; j <= d + 1; ++j)
      A[i][j] = A[i][j] * inv1 % mod;
    for (int j = i + 1; j <= d; ++j)
      for (int k = d + 1; k >= i; --k)
        A[j][k] = (A[j][k] - A[j][i] * A[i][k] % mod) % mod;
  }
  for (int i = d; ~i; --i) {
    a[i + 1] = A[i][d + 1];
    for (int j = i - 1; ~j; --j)
      A[j][d + 1] = (A[j][d + 1] - A[j][i] * A[i][d + 1] % mod) % mod;
  }
}
const int N = 1050;
int p[N], q[N];
int main() {
  int w;
  scanf("%d%d", &d, &w);
  solve();
  LL ans = 0, n = 1;
  for (int i = 0; i < w; ++i) {
    scanf("%d%d", &p[i], &q[i]);
    n = n * pow_mod(p[i], q[i]) % mod;
  }
  LL y = 1;
  for (int i = 1; i <= d + 1; ++i) {
    y = y * n % mod;
    LL t = a[i] * y % mod;
    for (int j = 0; j < w; ++j)
      t = t * (1 - pow_mod(p[j], d - i)) % mod;
    ans = (ans + t) % mod;
  }
  printf("%d\n", (int)((ans + mod) % mod));
  return 0;
}

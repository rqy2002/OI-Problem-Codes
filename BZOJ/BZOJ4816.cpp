/**************************************************************
 * Problem: BZOJ4816
 * Author: Rqy
 * Date: 2018 Feb 24
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
typedef long long LL;
const int N = 1000050;
const int mod = 1000000007;
int f[N], s[N], pr[N], cnt;
bool vis[N];
int pow_mod(int a, int b) {
  int ans = 1;
  for (; b; b >>= 1, a = (LL)a * a % mod)
    if (b & 1) ans = (LL)ans * a % mod;
  return ans;
}
inline int inv(int x) { return pow_mod(x, mod - 2); }
void sieve() {
  s[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (!vis[i]) s[pr[cnt++] = i] = -1;
    for (int j = 0; j < cnt && (LL)i * pr[j] < N; ++j) {
      s[i * pr[j]] = i % pr[j] ? -s[i] : 0;
      vis[i * pr[j]] = 1;
      if (!(i % pr[j])) break;
    }
  }
  f[0] = 0; f[1] = 1;
  for (int i = 2; i < N; ++i) f[i] = (f[i - 1] + f[i - 2]) % mod;
  for (int i = N - 1; i; --i)
    for (int j = i * 2, g = inv(f[i]); j < N; j += i) {
      if (s[j / i] == 1) f[j] = (LL)f[j] * f[i] % mod;
      else if (s[j / i] == -1) f[j] = (LL)f[j] * g % mod;
    }
  f[0] = 1;
  for (int i = 2; i < N; ++i) {
    s[i] += s[i - 1];
    f[i] = (LL)f[i] * f[i - 1] % mod;
  }
}
int main() {
  sieve();
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m;
    scanf("%d%d", &n, &m);
    if (n > m) std::swap(n, m);
    int ans = 1;
    for (int i = 1, last; i <= n; i = last + 1) {
      last = std::min(n / (n / i), m / (m / i));
      ans = (LL)ans * pow_mod((LL)f[last] * inv(f[i - 1]) % mod, (LL)(n / i) * (m / i) % (mod - 1)) % mod;
    }
    printf("%d\n", (ans + mod) % mod);
  }
  return 0;
}


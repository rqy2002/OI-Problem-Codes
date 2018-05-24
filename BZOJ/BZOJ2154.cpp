/**************************************************************
 * Problem: BZOJ2154
 * Author: Rqy
 * Date: 2018 Feb 28
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 10000050;
const int mod = 20101009;
typedef long long LL;
int f[N], pr[N / 10], cnt;
inline int calc(int n) { return (LL)n * (n + 1) / 2 % mod; }
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  if (n > m) std::swap(n, m);
  f[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!f[i])
      f[pr[cnt++] = i] = 1 - i;
    for (int j = 0; j < cnt && pr[j] <= n / i; ++j)
      if (i % pr[j])
        f[i * pr[j]] = f[i] * f[pr[j]];
      else {
        f[i * pr[j]] = f[i];
        break;
      }
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    ans = (ans + (LL)calc(n / i) * calc(m / i) % mod * i % mod * f[i] % mod) % mod;
  printf("%d\n", (ans + mod) % mod);
  return 0;
}

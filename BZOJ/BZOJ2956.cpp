/**************************************************************
 * Problem: BZOJ2956
 * Author: Rqy
 * Date: 2018 Feb 23
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int mod = 19940417;
const int inv6 = 3323403;
typedef long long LL;
inline LL calc(int n) { n %= mod; return (LL)n * (n + 1) / 2 % mod; }
inline LL calc2(int n) {
  n %= mod;
  return (LL)n * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod;
}
int solve(int n) {
  int ans = (LL)n * n % mod;
  for (int i = 1, last; i <= n; i = last + 1) {
    last = n / (n / i);
    ans = (ans - (LL)(calc(last) - calc(i - 1)) * (n / i) % mod) % mod;
  }
  return ans;
}
int solve2(int n, int m) {
  if (n > m) std::swap(n, m);
  int ans = (LL)n * n % mod * m % mod;
  for (int i = 1, last; i <= n; i = last + 1) {
    last = std::min(n / (n / i), m / (m / i));
    ans = (ans
        - (LL)(calc(last) - calc(i - 1)) * ((LL)(n / i) * m % mod + (LL)(m / i) * n % mod) % mod
        + (LL)(calc2(last) - calc2(i - 1)) * (n / i) % mod * (m / i) % mod) % mod;
  }
  return ans;
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  printf("%d\n", (int)((((LL)solve(n) * solve(m) - solve2(n, m))% mod + mod) % mod));
  return 0;
}

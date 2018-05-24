/**************************************************************
 * Problem: BZOJ1408
 * Author: Rqy
 * Date: 2018 Feb 24
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 1050;
const int mod = 10000;
inline int sqr(int a) { return a * a % mod; }
int pow(int a, int b) {
  return b ? (b & 1 ? a : 1) * sqr(pow(a, b >> 1)) % mod : 1;
}
int main() {
  int k, m = 1, ans1 = 0, ans2 = 0, p, e;
  scanf("%d", &k);
  while (k--) {
    scanf("%d%d", &p, &e);
    (m *= pow(p, e)) %= mod;
    if (p > 2) {
      int t1 = ans1, t2 = ans2;
      ans1 = (t1 + (p - 1) * t2) % mod;
      ans2 = ((p - 1) * (1 + t1) + t2) % mod;
    }
  }
  printf("%d\n%d\n%d\n", ans1, ans2, (m - 1 - ans1 - ans2 + 3 * mod) % mod);
  return 0;
}

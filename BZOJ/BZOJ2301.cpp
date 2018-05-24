/**************************************************************
 * Problem: BZOJ2301
 * Author: Rqy
 * Date: 2018 Feb 25
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 50050;
typedef long long LL;
int s[N];
bool mark[N];
LL solve(int a, int b) {
  LL ans = 0;
  for (int i = 1, last; i <= a && i <= b; i = last + 1) {
    last = std::min(a / (a / i), b / (b / i));
    ans += (LL)(s[last] - s[i - 1]) * (a / i) * (b / i);
  }
  return ans;
}
int main() {
  for (int i = 1; i < N; ++i) s[i] = 1;
  for (int i = 2; i < N; ++i) if (!mark[i])
    for (int j = i; j < N; j += i) {
      mark[j] = 1;
      s[j] *= (j / i % i) ? -1 : 0;
    }
  for (int i = 1; i < N; ++i) s[i] += s[i - 1];
  int n, a, b, c, d, k;
  scanf("%d", &n);
  while (n--) {
    scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
    (--a /= k); b /= k; (--c /= k); d /= k;
    printf("%lld\n", solve(b, d) - solve(a, d) - solve(b, c) + solve(a, c));
  }
  return 0;
}

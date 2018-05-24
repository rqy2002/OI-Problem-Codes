/**************************************************************
 * Problem: BZOJ2190
 * Author: Rqy
 * Date: 2018 Feb 26
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
typedef long long LL;
const int N = 40050;
int phi[N];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) phi[i] = i;
  for (int i = 2; i < n; ++i) if (phi[i] == i)
    for (int j = i; j < n; j += i)
      phi[j] = phi[j] / i * (i - 1);
  LL ans = 0;
  for (int i = 1; i < n; ++i) ans += phi[i];
  printf("%lld\n", ans * 2 + 1);
  return 0;
}

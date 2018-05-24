/**************************************************************
 * Problem: BZOJ4590
 * Author: Rqy
 * Date: 2018 Feb 23
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
typedef long long LL;
const int N = 100050;
int x[N], n, k;
int calc(LL m) {
  int ans = 0;
  for (LL i = 0, t = 0; i < n; ++i)
    if ((t = std::max(t + x[i], 0LL)) >= m)
      ++ans, t = 0;
  return ans;
}
int main() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) scanf("%d", &x[i]);
  if (calc(1) < k) return puts("-1") & 0;
  LL l = 1, r = 1e15;
  while (l < r) {
    LL mid = (l + r) / 2;
    if (calc(mid) > k) l = mid + 1;
    else r = mid;
  }
  if (calc(l) != k) return puts("-1") & 0;
  printf("%lld ", l);
  l = 1, r = 1e15;
  while (l < r) {
    LL mid = r + (l - r) / 2;
    if (calc(mid) < k) r = mid - 1;
    else l = mid;
  }
  printf("%lld\n", l);
  return 0;
}

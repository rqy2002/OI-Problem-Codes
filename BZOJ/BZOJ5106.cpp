/**************************************************************
 * Problem: BZOJ5106
 * Author: Rqy
 * Date: 2018 Feb 27
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
typedef long long LL;
const int N = 200050;
LL S, L, H[N], A[N];
int n;
int main() {
  scanf("%d%lld%lld", &n, &S, &L);
  LL l = 0, r = 0;
  for (int i = 0; i < n; ++i) scanf("%lld", &H[i]);
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &A[i]);
    r = std::max(r, 1 + std::max(S, L) / A[i]);
  }
  while (l < r) {
    LL mid = (l + r) / 2;
    LL ans = 0;
    for (int i = 0; i < n && ans < S; ++i)
      if (H[i] + A[i] * mid >= L) ans += H[i] + A[i] * mid;
    if (ans >= S) r = mid;
    else l = mid + 1;
  }
  printf("%lld\n", l);
  return 0;
}

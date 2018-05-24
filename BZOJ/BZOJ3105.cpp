/**************************************************************
 * Problem: BZOJ3105
 * Author: Rqy
 * Date: 2018 Feb 23
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int K = 105;
int J[32], A[K];
bool mark[K];
bool cmp(int a, int b) { return b < a; }
int main() {
  int k;
  scanf("%d", &k);
  for (int i = 0; i < k; ++i) scanf("%d", &A[i]);
  std::sort(A, A + k, cmp);
  long long ans = 0;
  for (int i = 0, j, l; i < k; ++i) {
    for (l = 31, j = A[i]; ~l; --l)
      if ((j >> l) & 1) {
        if (!J[l]) { J[l] = j; break; }
        else j ^= J[l];
      }
    if (l == -1) ans += A[i];
  }
  printf("%lld\n", ans);
  return 0;
}

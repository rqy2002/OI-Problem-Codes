/**************************************************************
 * Problem: Luogu P3143
 * Author: Rqy
 * Date: 2017 Dec 27
 * Algorithm: 尺取
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 50050;
int A[N], l[N], r[N];
int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) scanf("%d", &A[i]);
  std::sort(A, A + n);
  for (int i = 0, j = 0; i < n; ++i) {
    while (A[i] - A[j] > k) ++j;
    r[i] = i - j + 1;
  }
  for (int i = n - 1, j = n - 1; ~i; --i) {
    while (A[j] - A[i] > k) --j;
    l[i] = j - i + 1;
  }
  for (int i = 1; i < n; ++i) r[i] = std::max(r[i], r[i - 1]);
  for (int i = n - 2; ~i; --i) l[i] = std::max(l[i], l[i + 1]);
  int ans = 0;
  for (int i = 1; i < n; ++i)
    ans = std::max(ans, l[i] + r[i - 1]);
  printf("%d\n", ans);
  return 0;
}

/**************************************************************
 * Problem: BZOJ2257
 * Author: Rqy
 * Date: 2018 Feb 28
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
int A[2000000];
int main() {
  int n, k, m = 0;
  scanf("%d%d", &n, &k);
  while (n--) {
    int x;
    scanf("%d", &x);
    for (int i = 1; i * i <= x; ++i) if (!(x % i)) {
      A[m++] = i;
      if (i * i != x) A[m++] = x / i;
    }
  }
  std::sort(A, A + m);
  for (int i = m - 1, t = 0; i; --i)
    if ((t = (A[i] == A[i + 1]) * t + 1) >= k)
      return printf("%d\n", A[i]) & 0;
}

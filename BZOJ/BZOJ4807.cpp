/**************************************************************
 * Problem: BZOJ4807
 * Author: Rqy
 * Date: 2018 Feb 24
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 1000050;
bool mark[N];
const int K = 50;
int A[K], len;
int get(int n, int p) { return n ? n / p + get(n / p, p) : 0; }
void mul(int x) {
  for (int i = 0, t = 0; i < len || t; ++i) {
    if (i >= 50) break;
    if (i >= len) len = i + 1;
    t = (A[i] = A[i] * x + t) / 10;
    A[i] %= 10;
  }
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  if (n < m) std::swap(n, m);
  len = A[0] = 1;
  for (int i = 2; i <= n; ++i) if (!mark[i]) {
    int k = get(n, i) - get(m, i) - get(n - m, i);
    while (k--) mul(i);
    for (int j = i; j <= n; j += i)
      mark[j] = 1;
  }
  while (!A[len - 1]) --len;
  for (int i = len - 1; ~i; --i) printf("%d", A[i]);
  return 0;
}

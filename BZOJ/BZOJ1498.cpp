/**************************************************************
 * Problem: BZOJ1498
 * Author: Rqy
 * Date: 2018 Feb 24
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 1050;
const int M = 20050;
int a[N];
int p[M];
void add(int n, int x) {
  for (int i = 2; i <= n; ++i) while (!(n % i)) { p[i] += x; n /= i; }
}
int A[M], len;
void mul(int x) {
  for (int i = 0, t = 0; i < len || t; ++i) {
    if (i >= len) len = i + 1;
    t = (A[i] = A[i] * x + t) / 10;
    A[i] %= 10;
  }
}
int main() {
  int t, n, d, S = 0;
  scanf("%d%d%d", &t, &n, &d);
  for (int i = 1; i <= t; ++i) {
    scanf("%d", &a[i]);
    S += a[i];
  }
  while (n--) {
    int y;
    scanf("%*d%d", &y);
    add(S, -1); add(a[y], 1);
    a[y] += d; S += d;
  }
  A[0] = len = 1;
  for (int i = 2; i < M; ++i)
    while (p[i] > 0) --p[i], mul(i);
  while (len--) printf("%d", A[len]);
  memset(A, 0, sizeof A);
  A[0] = len = 1;
  for (int i = 2; i < M; ++i)
    while (p[i] < 0) ++p[i], mul(i);
  putchar('/');
  while (len--) printf("%d", A[len]);
  return 0;
}

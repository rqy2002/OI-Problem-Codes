/**************************************************************
 * Problem: Luogu P2219
 * Author: Rqy
 * Date: 2017 Dec 23
 * Algorithm: 单调队列
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 1050;
const int INF = 1000000000;
int A[N][N], B[N][N], m1[N][N], m2[N][N];
int que[N], head, tail;
int main() {
  int n, m, a, b, c, d;
  scanf("%d%d%d%d%d%d", &m, &n, &a, &b, &c, &d);
  for (int i = 1; i <= m; ++i)
    for (int j = 1; j <= n; ++j) {
      scanf("%d", &A[i][j]);
      B[i][j] = A[i][j] += A[i][j - 1] + A[i - 1][j] - A[i - 1][j - 1];
    }
  for (int i = m; i >= a; --i)
    for (int j = n; j >= b; --j)
      A[i][j] -= A[i - a][j] + A[i][j - b] - A[i - a][j - b];
  for (int i = m; i >= c; --i)
    for (int j = n; j >= d; --j)
      B[i][j] -= B[i - c][j] + B[i][j - d] - B[i - c][j - d];
  for (int i = 1; i < m; ++i) {
    head = tail = 0;
    for (int j = 1; j < n; ++j) {
      while (head < tail && B[i][que[tail - 1]] > B[i][j]) --tail;
      que[tail++] = j;
      m1[i][j] = B[i][que[head]];
      if (que[head] == j - b + d + 2) ++head;
    }
  }
  int ans = A[m][n] - B[m - 1][n - 1];
  for (int j = 1; j <= n; ++j) {
    head = tail = 0;
    for (int i = 1; i <= m; ++i) {
      while (head < tail && m1[que[tail - 1]][j] > m1[i][j]) --tail;
      que[tail++] = i;
      m2[i][j] = m1[que[head]][j];
      if (que[head] == i - a + c + 2) ++head;
    }
  }
  for (int i = a; i <= m; ++i)
    for (int j = b; j <= n; ++j)
      ans = std::max(ans, A[i][j] - m2[i - 1][j - 1]);
  printf("%d\n", ans);
  return 0;
}


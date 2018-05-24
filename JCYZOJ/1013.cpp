/**************************************************************
 * Problem: JCYZOJ 1013
 * Author: Rqy
 * Date: 2018 Feb 13
 * Algorithm: 2demision-BIT
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
typedef long long LL;
const int N = 805;
LL A[N][N], Ax[N][N], Ay[N][N], Axy[N][N];
LL S[N][N];
int n, m;
void add(LL A[N][N], int x, int y, LL v) {
  for (int i = x; i <= n; i += i & -i)
    for (int j = y; j <= m; j += j & -j)
      A[i][j] += v;
}
void add(int x, int y, LL v) {
  add(Axy, x, y, v);
  add(Ax, x, y, -v * (y - 1));
  add(Ay, x, y, -v * (x - 1));
  add(A, x, y, v * (x - 1) * (y - 1));
}
void add(int x1, int y1, int x2, int y2, LL v) {
  add(x1, y1, v);
  add(x1, y2 + 1, -v);
  add(x2 + 1, y1, -v);
  add(x2 + 1, y2 + 1, v);
}
LL query(LL A[N][N], int x, int y) {
  LL ans = 0;
  for (int i = x; i; i &= (i - 1))
    for (int j = y; j; j &= (j - 1))
      ans += A[i][j];
  return ans;
}
LL query(int x, int y) {
  LL ans = 0;
  ans += query(Axy, x, y) * x * y;
  ans += query(Ax, x, y) * x;
  ans += query(Ay, x, y) * y;
  ans += query(A, x, y);
  return ans;
}
LL query(int x1, int y1, int x2, int y2) {
  LL ans = 0;
  ans += query(x2, y2);
  ans -= query(x2, y1 - 1);
  ans -= query(x1 - 1, y2);
  ans += query(x1 - 1, y1 - 1);
  return ans;
}
int main() {
  int q;
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      scanf("%lld", &S[i][j]);
      S[i][j] += S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1];
      int i1 = i & (i - 1), j1 = j & (j - 1);
      A[i][j] = S[i][j] - S[i1][j] - S[i][j1] + S[i1][j1];
    }
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) Ax[i][j] = 0;
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) Ay[i][j] = 0;
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) Axy[i][j] = 0;
  while (q--) {
    int opt, x1, y1, x2, y2;
    LL v;
    scanf("%d%d%d%d%d", &opt, &x1, &y1, &x2, &y2);
    if (opt == 1) {
      scanf("%lld", &v);
      add(x1, y1, x2, y2, v);
    } else
      printf("%lld\n", query(x1, y1, x2, y2));
  }
  return 0;
}

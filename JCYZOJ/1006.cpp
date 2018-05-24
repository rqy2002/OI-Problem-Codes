/**************************************************************
 * Problem: JCYZOJ 1006
 * Author: Rqy
 * Date: 2018 Feb 13
 * Algorithm: RMQ
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 500050;
int n, A[N], L[N], R[N], gcdv[20][N];
bool t[N];
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
inline int gcdr(int l, int r) {
  int k = 0;
  while ((r - l + 1) >> (k + 1)) ++k;
  return gcd(gcdv[k][l], gcdv[k][r - (1 << k) + 1]);
}
int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &A[i]);
    gcdv[0][i] = A[i];
  }
  for (int i = 0; i < 19; ++i)
    for (int j = 0; j + (2 << i) <= n; ++j)
      gcdv[i + 1][j] = gcd(gcdv[i][j], gcdv[i][j + (1 << i)]);
  int ans = 0, ans2 = 0;
  for (int i = 0; i < n; ++i) {
    int l = 0, r = i;
    while (l < r) {
      int mid = (l + r) / 2;
      if (gcdr(mid, i) == A[i]) r = mid;
      else l = mid + 1;
    }
    L[i] = l;
    l = i, r = n - 1;
    while (l < r) {
      int mid = r + (l - r) / 2;
      if (gcdr(i, mid) == A[i]) l = mid;
      else r = mid - 1;
    }
    R[i] = l;
    ans = std::max(ans, R[i] - L[i]);
  }
  for (int i = 0; i < n; ++i) if (R[i] - L[i] == ans) t[L[i]] = true;
  for (int i = 0; i < n; ++i) if (t[i]) ++ans2;
  printf("%d %d\n", ans2, ans);
  for (int i = 0; i < n; ++i) if (t[i]) printf("%d ", i + 1);
  return 0;
}

/**************************************************************
 * Problem: BZOJ2006
 * Author: Rqy
 * Date: 2018 Feb 25
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <queue>
const int N = 500050;
typedef long long LL;
LL A[N];
int maxn[30][N];
int query(int l, int r) {
  int k = 0;
  while ((1 << (k + 1)) <= (r - l + 1)) ++k;
  int t1 = maxn[k][l], t2 = maxn[k][r - (1 << k) + 1];
  return A[t1] > A[t2] ? t1 : t2;
}
struct HeapNode{
  int x, l, r, y;
  HeapNode(int x, int l, int r) : x(x), l(l), r(r) { y = query(l, r); }
  LL getV() const { return A[y] - A[x - 1]; }
  bool operator<(const HeapNode &t) const { return getV() < t.getV(); }
};
std::priority_queue<HeapNode> PQ;
int main() {
  int n, k, L, R;
  scanf("%d%d%d%d", &n, &k, &L, &R);
  for (int i = 1; i <= n; ++i) scanf("%lld", &A[i]);
  for (int i = 1; i <= n; ++i) A[maxn[0][i] = i] += A[i - 1];
  for (int i = 0; i + 1 < 30; ++i)
    for (int j = 1; (1 << i) + j <= n + 1; ++j) {
      int t1 = maxn[i][j], t2 = maxn[i][j + (1 << i)];
      maxn[i + 1][j] = A[t1] > A[t2] ? t1 : t2;
    }
  while (!PQ.empty()) PQ.pop();
  for (int i = 1; i + L - 1 <= n; ++i)
    PQ.push(HeapNode(i, i + L - 1, std::min(i + R - 1, n)));
  LL ans = 0;
  while (k--) {
    HeapNode x = PQ.top(); PQ.pop();
    ans += x.getV();
    if (x.y != x.l) PQ.push(HeapNode(x.x, x.l, x.y - 1));
    if (x.y != x.r) PQ.push(HeapNode(x.x, x.y + 1, x.r));
  }
  printf("%lld\n", ans);
  return 0;
}

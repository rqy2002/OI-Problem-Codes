/**************************************************************
 * Problem: Luogu P2709
 * Author: Rqy
 * Date: 2017 Dec 26
 * Algorithm: 莫队
**************************************************************/
#include <algorithm>
#include <cstdio>
typedef long long LL;
const int N = 50050;
int A[N], cnt[N], B;
struct Query{
  int i, l, r;
  bool operator<(const Query &t)const {
    if (l / B != t.l / B) return l / B < t.l / B;
    return r < t.r;
  }
}q[N];
LL ans[N];
int main() {
  int n, m;
  scanf("%d%d%*d", &n, &m);
  while (B * B < n) ++B;
  for (int i = 0; i < n; ++i)
    scanf("%d", &A[i]);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &q[i].l, &q[i].r);
    --q[i].l, --q[i].r;
    q[i].i = i;
  }
  std::sort(q, q + m);
  int l = 0, r = -1;
  LL anst = 0;
  for (int i = 0; i < m; ++i) {
    while (l > q[i].l) anst += 2 * (cnt[A[--l]]++) + 1;
    while (r < q[i].r) anst += 2 * (cnt[A[++r]]++) + 1;
    while (l < q[i].l) anst -= 2 * (--cnt[A[l++]]) + 1;
    while (r > q[i].r) anst -= 2 * (--cnt[A[r--]]) + 1;
    ans[q[i].i] = anst;
  }
  for (int i = 0; i < m; ++i)
    printf("%lld\n", ans[i]);
  return 0;
}

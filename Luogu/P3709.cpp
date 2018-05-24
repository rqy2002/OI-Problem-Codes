/**************************************************************
 * Problem: Luogu P3709
 * Author: Rqy
 * Date: 2017 Dec 26
 * Algorithm: 莫队
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <map>
const int N = 200050;
int bs, A[N], cnt[N], ccnt[N], maxt, ans[N];
struct Query{
  int l, r, i;
  bool operator<(const Query &t)const{
    if (l / bs != t.l / bs) return l / bs < t.l / bs;
    return r < t.r;
  }
}q[N];
int get(int x) {
  static int p = 0;
  static std::map<int, int> M;
  if (!M.count(x)) M[x] = p++;
  return M[x];
}
void add(int x) {
  --ccnt[cnt[x]];
  ++ccnt[++cnt[x]];
  maxt = std::max(maxt, cnt[x]);
}
void remove(int x) {
  --ccnt[cnt[x]];
  if (maxt == cnt[x] && !ccnt[cnt[x]])
    --maxt;
  ++ccnt[--cnt[x]];
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  while (bs * bs < n) ++bs;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &A[i]);
    A[i] = get(A[i]);
  }
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &q[i].l, &q[i].r);
    --q[i].l; --q[i].r;
    q[i].i = i;
  }
  std::sort(q, q + m);
  int l = 0, r = -1;
  ccnt[0] = n;
  for (int i = 0; i < m; ++i) {
    while (l > q[i].l) add(A[--l]);
    while (r < q[i].r) add(A[++r]);
    while (l < q[i].l) remove(A[l++]);
    while (r > q[i].r) remove(A[r--]);
    ans[q[i].i] = maxt;
  }
  for (int i = 0; i < n; ++i)
    printf("%d\n", -ans[i]);
  return 0;
}

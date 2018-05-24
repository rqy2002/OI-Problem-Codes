/**************************************************************
 * Problem: Luogu P2698
 * Author: Rqy
 * Date: 2017 Dec 22
 * Algorithm: 单调队列
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 100050;
struct Water{
  int x, h, ord;
  bool operator<(const Water &s) const {
    return x < s.x;
  }
}ws[N];
int q1[N], q2[N], h1, h2, t1, t2;
int main() {
  int n, d;
  scanf("%d%d", &n, &d);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &ws[i].x, &ws[i].h);
    ws[i].ord = i;
  }
  std::sort(ws, ws + n);
  h1 = h2 = t1 = t2 = 0;
  int ans = 10000000;
  for (int i = 0, j = 0; i < n; ++i) {
    while (j < n && (i == j || ws[q1[h1]].h - ws[q2[h2]].h < d)) {
      while (t1 > h1 && ws[q1[t1 - 1]].h < ws[j].h) --t1;
      while (t2 > h2 && ws[q2[t2 - 1]].h > ws[j].h) --t2;
      q1[t1++] = q2[t2++] = j++;
    }
    if (ws[q1[h1]].h - ws[q2[h2]].h < d) break;
    ans = std::min(ans, ws[j - 1].x - ws[i].x);
    if (q1[h1] == i) ++h1;
    if (q2[h2] == i) ++h2;
  }
  if (ans >= 10000000) printf("-1\n");
  else printf("%d\n", ans);
  return 0;
}

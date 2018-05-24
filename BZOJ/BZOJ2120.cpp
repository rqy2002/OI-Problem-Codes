/**************************************************************
 * Problem: BZOJ2120
 * Author: Rqy
 * Date: 2018 Feb 25
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 10050;
const int M = 1050;
const int S = 300;
int c[N];
int p[M], ca[M], cb[M];
int cnt[1000050];
struct Query{
  int l, r, t, id;
  bool operator<(const Query &x) const {
    if (l / S != x.l / S) return l / S < x.l / S;
    if (r / S != x.r / S) return r / S < x.r / S;
    return t < x.t;
  }
}qs[N];
int ans[N];
int main() {
  int n, m = 0, q;
  scanf("%d%d", &n, &q);
  char s[10];
  for (int i = 1; i <= n; ++i) scanf("%d", &c[i]);
  for (int i = 0, x, y; i < q; ++i) {
    scanf("%s%d%d", s, &x, &y);
    if (*s == 'Q') {
      qs[i].l = x;
      qs[i].r = y;
      qs[i].t = m;
      qs[i].id = i;
    } else {
      p[m] = x;
      ca[m] = c[x];
      c[x] = cb[m++] = y;
      --i; --q;
    }
  }
  std::sort(qs, qs + q);
  int l = 1, r = 0, t = m, res = 0;
  for (int i = 0; i < q; ++i) {
    while (r < qs[i].r) res += !(cnt[c[++r]]++);
    while (l > qs[i].l) res += !(cnt[c[--l]]++);
    while (r > qs[i].r) res -= !(--cnt[c[r--]]);
    while (l < qs[i].l) res -= !(--cnt[c[l++]]);
    while (t < qs[i].t) {
      res -= !(--cnt[c[p[t]]]);
      res += !(cnt[c[p[t]] = cb[t]]++);
      ++t;
    }
    while (t > qs[i].t) {
      --t;
      res -= !(--cnt[c[p[t]]]);
      res += !(cnt[c[p[t]] = ca[t]]++);
    }
    ans[qs[i].id] = res;
  }
  for (int i = 0; i < q; ++i)
    printf("%d\n", ans[i]);
  return 0;
}

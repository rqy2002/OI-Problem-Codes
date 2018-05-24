/**************************************************************
 * Problem: Luogu P3168
 * Author: Rqy
 * Date: 2017 Dec 29
 * Algorithm: 主席树
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 100050;
const int NN = N * 50;
typedef long long LL;
struct Event{
  int x, p, t, ti;
  bool operator<(const Event &y)const{
    return ti < y.ti;
  }
}e[N * 2];
int siz[NN], son[NN][2], root[NN], cnt;
int ti[NN];
LL sum[NN];
inline void maintain(int o) {
  sum[o] = sum[son[o][0]] + sum[son[o][1]];
  siz[o] = siz[son[o][0]] + siz[son[o][1]];
}
inline int newNode(int x, int time) {
  sum[cnt] = sum[x]; siz[cnt] = siz[x];
  son[cnt][0] = son[x][0];
  son[cnt][1] = son[x][1];
  ti[cnt] = time;
  return cnt++;
}
void modify(int &o, int l, int r, const Event &e) {
  if (ti[o] != e.ti) o = newNode(o, e.ti);
  if (l == r) {
    siz[o] += e.t;
    sum[o] += e.p * e.t;
  } else {
    int mid = (l + r) / 2;
    if (mid >= e.x) modify(son[o][0], l, mid, e);
    else modify(son[o][1], mid + 1, r, e);
    maintain(o);
  }
}
LL query(int o, int k) {
  if (siz[o] <= k) return sum[o];
  if (siz[son[o][0]] >= k) return query(son[o][0], k);
  else return sum[son[o][0]] + query(son[o][1], k - siz[son[o][0]]);
}
int s[N], t[N], p[N], x[N], tmp[N];
bool cmp(int a, int b) {
  return p[a] < p[b];
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d%d", &s[i], &t[i], &p[i]);
    tmp[i] = i;
  }
  std::sort(tmp, tmp + n, cmp);
  for (int i = 0; i < n; ++i) x[tmp[i]] = i + 1;
  for (int i = 0; i < n; ++i) {
    e[i << 1] = (Event){x[i], p[i], 1, s[i]};
    e[i << 1 | 1] = (Event){x[i], p[i], -1, t[i] + 1};
  }
  std::sort(e, e + 2 * n);
  int now = 0;
  cnt = 1;
  for (int i = 0, j = 0; i <= n; ++i) {
    while (e[j].ti == i)
      modify(now, 1, n, e[j++]);
    root[i] = now;
  }
  LL pre = 1;
  int X, A, B, C;
  while (m--) {
    scanf("%d%d%d%d", &X, &A, &B, &C);
    int K = 1 + (pre % C * A + B) % C;
    printf("%lld\n", pre = query(root[X], K));
  }
  return 0;
}

#include <algorithm>
#include <cstdio>
const int N = 100050;
int cnt[N * 4], set[N * 4];
int A[N];
inline void upd(int o, int l, int r) {
  if (~set[o]) cnt[o] = set[o] * (r - l + 1);
  else cnt[o] = cnt[o << 1] + cnt[o << 1 | 1];
}
inline void pushd(int o, int l, int r) {
  if (l != r && ~set[o]) {
    set[o << 1] = set[o << 1 | 1] = set[o];
    set[o] = -1;
  }
}
int p;
void build(int o, int l, int r) {
  if (l == r) set[o] = A[l] > p;
  else {
    set[o] = -1;
    int mid = (l + r) >> 1;
    build(o << 1, l, mid);
    build(o << 1 | 1, mid + 1, r);
  }
  upd(o, l, r);
}
int L, R, x;
void modify(int o, int l, int r) {
  upd(o, l, r);
  if (l > R || L > r) return;
  if (l >= L && r <= R)
    set[o] = x;
  else {
    pushd(o, l, r);
    int mid = (l + r) >> 1;
    modify(o << 1, l, mid);
    modify(o << 1 | 1, mid + 1, r);
  }
  upd(o, l, r);
}
int query(int o, int l, int r) {
  if (l > R || L > r) return 0;
  if (~set[o]) return set[o] * (std::min(r, R) - std::max(l, L) + 1);
  if (l >= L && r <= R) return cnt[o];
  int mid = (l + r) >> 1;
  return query(o << 1, l, mid) + query(o << 1 | 1, mid + 1, r);
}
int n;
void work(int l, int r, int t) {
  L = l; R = r;
  int c = query(1, 1, n);
  if (t) {
    L = l; R = l + c - 1; x = 1;
    modify(1, 1, n);
    L = l + c; R = r; x = 0;
    modify(1, 1, n);
  } else {
    L = l; R = r - c; x = 0;
    modify(1, 1, n);
    L = r - c + 1; R = r; x = 1;
    modify(1, 1, n);
  }
}
int m, l[N], r[N], t[N], q;
bool check(int mid) {
  p = mid;
  build(1, 1, n);
  for (int i = 0; i < m; ++i)
    work(l[i], r[i], t[i]);
  L = R = q;
  return query(1, 1, n);
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &A[i]);
  for (int i = 0; i < m; ++i)
    scanf("%d%d%d", &t[i], &l[i], &r[i]);
  scanf("%d", &q);
  int ll = 1, rr = n;
  while (ll < rr) {
    int mid = (ll + rr) >> 1;
    if (check(mid)) ll = mid + 1;
    else rr = mid;
  }
  printf("%d\n", ll);
  return 0;
}

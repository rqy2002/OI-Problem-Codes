/**************************************************************
 * Problem: BZOJ3211
 * Author: Rqy
 * Date: 2018 Feb 24
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cmath>
typedef long long LL;
const int N = 100050;
int A[N], n;
LL S[N * 4];
bool flag[N * 4];
inline int readInt() {
  int ans = 0, c;
  while (!isdigit(c = getchar()));
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getchar()));
  return ans;
}
inline void upd(int o, int l, int r) {
  if (l == r) flag[o] = (S[o] = A[l]) <= 1;
  else {
    flag[o] = flag[o << 1] && flag[o << 1 | 1];
    S[o] = S[o << 1] + S[o << 1 | 1];
  }
}
void build(int o, int l, int r) {
  if (l != r) {
    int mid = (l + r) / 2;
    build(o << 1, l, mid);
    build(o << 1 | 1, mid + 1, r);
  }
  upd(o, l, r);
}
void modify(int o, int l, int r, int L, int R) {
  if (flag[o]) return;
  if (l > R || L > r) return;
  if (l == r) A[l] = (int)sqrt(A[l]);
  else {
    int mid = (l + r) / 2;
    modify(o << 1, l, mid, L, R);
    modify(o << 1 | 1, mid + 1, r, L, R);
  }
  upd(o, l, r);
}
LL query(int o, int l, int r, int L, int R) {
  if (l > R || L > r) return 0;
  if (L <= l && r <= R) return S[o];
  int mid = (l + r) / 2;
  return query(o << 1, l, mid, L, R) + query(o << 1 | 1, mid + 1, r, L, R);
}
int main() {
  n = readInt();
  for (int i = 1; i <= n; ++i) scanf("%d", &A[i]);
  build(1, 1, n);
  for (int m = readInt(), x, l, r; m; --m) {
    x = readInt(); l = readInt(); r = readInt();
    if (x == 2)
      modify(1, 1, n, l, r);
    else
      printf("%lld\n", query(1, 1, n, l, r));
  }
  return 0;
}

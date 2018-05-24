/**************************************************************
 * Problem: BZOJ2161
 * Author: Rqy
 * Date: 2018 Feb 28
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 100050;
const int NN = 40 * N;
const int mod = 19921228;
int P[N], C[N], L[N], R[N];
int ch[NN][2], cnt = 1, siz[NN];
int ans = 0;
void insert(int x) {
  int o = 0;
  ++siz[o];
  for (int i = 31; ~i; --i) {
    int t = (x >> i) & 1;
    if (!ch[o][t]) ch[o][t] = cnt++;
    ++siz[o = ch[o][t]];
  }
}
void remove(int x) {
  int o = 0;
  --siz[o];
  for (int i = 31; ~i; --i) {
    int t = (x >> i) & 1;
    --siz[o = ch[o][t]];
  }
}
void query(int x) {
  if (siz[0] < x) return;
  int o = 0, ans = 0;
  for (int i = 31; ~i; --i) {
    int t = (ch[o][1] ? siz[ch[o][1]] : 0);
    if (t >= x) { o = ch[o][1]; ans |= (1 << i); }
    else { x -= t; o = ch[o][0]; }
  }
  (::ans += ans) %= mod;
}
void get(int *A, int n) {
  typedef long long LL;
  int add, fst, mod, prd;
  scanf("%d%d%d%d", &add, &fst, &mod, &prd);
  A[0] = fst % mod;
  for (int i = 1; i < n; ++i)
    A[i] = ((LL)A[i - 1] * prd + add + i + 1) % mod;
}
struct Event{
  int tim, tp, v;
  // v=0 -> insert; v=1 -> query; v=2 -> remove.
  bool operator<(const Event &e) const {
    if (tim != e.tim) return tim < e.tim;
    else return tp < e.tp;
  }
}e[N * 3];
int main() {
  int n;
  scanf("%d", &n);
  get(P, n); get(C, n); get(L, n); get(R, n);
  for (int i = 0; i < n; ++i) {
    if (R[i] < L[i]) std::swap(L[i], R[i]);
    e[i * 3 + 0] = (Event){L[i], 0, C[i]};
    e[i * 3 + 1] = (Event){P[i], 1, i + 1};
    e[i * 3 + 2] = (Event){R[i], 2, C[i]};
  }
  std::sort(e, e + 3 * n);
  for (int i = 0; i < 3 * n; ++i) {
    if (e[i].tp == 0) insert(e[i].v);
    if (e[i].tp == 1) query(e[i].v);
    if (e[i].tp == 2) remove(e[i].v);
  }
  printf("%d\n", ans);
  return 0;
}


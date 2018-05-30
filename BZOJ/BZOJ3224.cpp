#include <algorithm>
#include <cstdio>
#include <cstdlib>
const int N = 100050;
int v[N], w[N], ch[N][2], root;
int siz[N], cnt = 0;
void upd(int x) { siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1; }
int merge(int x, int y) {
  if (!x || !y) return x | y;
  //if (w[x] < w[y]) std::swap(x, y);
  if (v[x] > v[y]) ch[x][0] = merge(ch[x][0], y);
  else ch[x][1] = merge(ch[x][1], y);
  upd(x);
  return x;
}
int ta, tb;
void split(int o, int y, int k) {
  if (!o) { ta = tb = 0; return; }
  if (v[o] > y || (v[o] == y && !k)) {
    split(ch[o][0], y, k);
    ch[o][0] = tb;
    tb = o;
  } else {
    split(ch[o][1], y, k);
    ch[o][1] = ta;
    ta = o;
  }
  upd(o);
}
int _rank(int o, int y, int k) {
  if (!o) return 0;
  if (v[o] > y || (v[o] == y && !k))
    return _rank(ch[o][0], y, k);
  else
    return _rank(ch[o][1], y, k) + siz[ch[o][0]] + 1;
}
int rank(int x, int k) {
  return _rank(root, x, k) + !k;
}
void del(int x) {
  split(root, x, 0);
  int a = ta, b = tb;
  split(b, x, 1);
  b = ta;
  b = merge(ch[b][0], ch[b][1]);
  root = merge(merge(a, b), tb);
}
void ins(int x) {
  v[++cnt] = x;
  w[cnt] = cnt & (cnt >> 1);
  siz[cnt] = 1;
  ch[cnt][0] = ch[cnt][1] = 0;
  split(root, x, 0);
  root = merge(merge(cnt, tb), ta);
}
int kth(int k) {
  int l = -10000000, r = 10000000;
  while (l <= r) {
    int mid = (l + r) / 2;
    int ll = rank(mid, 0), rr = rank(mid, 1);
    if (ll <= k && k <= rr) return mid;
    else if (ll > k) r = mid - 1;
    else l = mid + 1;
  }
}
int main() {
  int n, opt, x;
  scanf("%d", &n);
  while (n--) {
    scanf("%d%d", &opt, &x);
    if (opt == 1) ins(x);
    else if (opt == 2) del(x);
    else if (opt == 3) printf("%d\n", rank(x, 0));
    else if (opt == 4) printf("%d\n", kth(x));
    else if (opt == 5) printf("%d\n", kth(rank(x, 0) - 1));
    else printf("%d\n", kth(rank(x, 1) + 1));
  }
  return 0;
}

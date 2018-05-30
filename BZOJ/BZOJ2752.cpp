#include <algorithm>
#include <cstdio>
typedef long long LL;
const int N = 100050 * 4;
LL sc[N], sci[N], scii[N], add[N];
inline LL si(LL l, LL r) {
  return (l + r) * (r - l + 1) / 2;
}
inline LL sii(LL l, LL r) {
  return (r * (r + 1) * (2 * r + 1) - l * (l - 1) * (2 * l - 1)) / 6;
}
#define lch (o << 1)
#define rch (o << 1 | 1)
inline void maintain(int o, int l, int r) {
  if (l == r) {
    sc[o] = add[o];
    sci[o] = l * sc[o];
    scii[o] = l * sci[o];
  } else {
    sc[o] = sc[lch] + sc[rch] + (r - l + 1) * add[o];
    sci[o] = sci[lch] + sci[rch] + si(l, r) * add[o];
    scii[o] = scii[lch] + scii[rch] + sii(l, r) * add[o];
  }
}
inline void pushdown(int o, int l, int r) {
  if (l != r) {
    add[lch] += add[o];
    add[rch] += add[o];
  }
  add[o] = 0;
}
int L, R, x;
void modify(int o, int l, int r) {
  if (l > R || L > r) return;
  if (l >= L && r <= R) {
    add[o] += x;
  } else {
    int mid = (l + r) / 2;
    modify(lch, l, mid);
    modify(rch, mid + 1, r);
  }
  maintain(o, l, r);
  return;
}
LL query(int o, int l, int r) {
  maintain(o, l, r);
  if (l > R || L > r) return 0LL;
  if (l >= L && r <= R)
    return -scii[o] + (L + R) * sci[o] - (LL)(R + 1) * (L - 1) * sc[o];
  pushdown(o, l, r);
  int mid = (l + r) / 2;
  return query(lch, l, mid) + query(rch, mid + 1, r);
}
char s[10];
inline LL gcd(LL a, LL b) {
  while (b) std::swap(b, a %= b);
  return a;
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  while (m--) {
    scanf("%s%d%d", s, &L, &R);
    if (*s == 'C') {
      scanf("%d", &x);
      --R;
      modify(1, 1, n);
    } else {
     LL ansd = (LL)(R - L) * (R - L + 1) / 2;
     --R;
      LL ans = query(1, 1, n);
      LL g = gcd(ans, ansd);
      printf("%lld/%lld\n", ans / g, ansd / g);
    }
  }
  return 0;
}

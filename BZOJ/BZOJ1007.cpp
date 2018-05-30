#include <algorithm>
#include <cstdio>
typedef long long LL;
const int N = 50050;
const double eps = 1e-6;
struct Line{
  int k, b, i;
  friend inline bool operator<(const Line &x, const Line &y) {
    if (x.k == y.k) return x.b > y.b;
    return x.k < y.k;
  }
};
double crossing(const Line &x, const Line &y) {
  return (double)(x.b - y.b) / (y.k - x.k);
}
Line l[N], t[N];
bool ans[N];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &l[i].k, &l[i].b);
    l[i].i = i;
  }
  std::sort(l, l + n);
  int top = 0;
  for (int i = 0; i < n; ++i) if (!i || l[i].k != l[i - 1].k) {
    while (top > 1 && crossing(t[top - 2], t[top - 1]) - crossing(l[i], t[top - 1]) > -eps)
      --top;
    t[top++] = l[i];
  }
  for (int i = 0; i < top; ++i) ans[t[i].i] = true;
  for (int i = 0; i < n; ++i) if (ans[i])
    printf("%d ", i + 1);
  return 0;
}

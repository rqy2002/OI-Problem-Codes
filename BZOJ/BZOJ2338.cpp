#include <algorithm> 
#include <cstdio>
typedef long long LL;
const int N = 1600;
int X[N], Y[N];
inline LL sqr(LL a) {
  return a * a;
}
inline LL S(LL x1, LL y1, LL x2, LL y2) {
  return std::abs(x1 * y2 - x2 * y1);
}
inline LL S(int p1, int p2, int p3) {
  return S(X[p1] - X[p2], Y[p1] - Y[p2], X[p3] - X[p2], Y[p3] - Y[p2]);
}
struct Line{
  LL len2;
  int mx, my;
  int p1, p2;
  Line(int p1 = 0, int p2 = 0)
    : p1(p1), p2(p2) {
      mx = X[p1] + X[p2];
      my = Y[p1] + Y[p2];
      len2 = sqr(X[p1] - X[p2]) + sqr(Y[p1] - Y[p2]);
    }
  bool operator < (const Line &x) const {
    if (len2 != x.len2) return len2 < x.len2;
    if (mx != x.mx) return mx < x.mx;
    return my < x.my;
  }
  bool operator == (const Line &x) const {
    return !(*this < x || x < *this);
  }
};
Line lines[N * N];
int main() {
  int n;
  scanf("%d", &n);
  int c = 0;
  for (int i = 0; i < n; ++i) scanf("%d%d", &X[i], &Y[i]);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) if (i != j)
      lines[c++] = Line(i, j);
  std::sort(lines, lines + c);
  LL ans = 0;
  for (int i = 0; i < c; ++i)
    for (int j = i - 1; j && lines[j] == lines[i]; --j)
      ans = std::max(ans, S(lines[i].p1, lines[j].p1, lines[i].p2));
  return !printf("%lld", ans);
}

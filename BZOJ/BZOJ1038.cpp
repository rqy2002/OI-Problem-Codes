#include <algorithm>
#include <cstdio>
using std::min;
using std::max;
const double eps = 1e-6;
int cmp(double l) {
  if (l > eps) return 1;
  if (l < eps) return -1;
  return 0;
}
struct Point{
  double x, y;
};
struct Line{
  double k, b;
  Line() : k(.0), b(.0) {}
  Line(const Point &a, const Point &b) {
    k = (a.y - b.y) / (a.x - b.x);
    this->b = a.y - a.x * k;
  }
  friend inline bool operator<(const Line &a, const Line &b) {
    if (cmp(a.k - b.k)) return a.k < b.k;
    return a.b > b.b;
  }
  double operator()(double x) const {
    return k * x + b;
  }
};
double crossing(const Line &a, const Line &b) {
  return (a.b - b.b) / (b. k - a.k);
}
const int N = 305;
Point p[N];
Line l[N], s[N];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%lf", &p[i].x);
  for (int i = 0; i < n; ++i) scanf("%lf", &p[i].y);
  for (int i = 1; i < n; ++i) l[i - 1] = Line(p[i - 1], p[i]);
  std::sort(l, l + n - 1);
  int m = 0;
  for (int i = 0; i < n - 1; ++i) {
    while (m > 1 && crossing(s[m - 1], l[i]) <= crossing(s[m - 1], s[m - 2])) --m;
    s[m++] = l[i];
  }
  double ans = 1e10;
  int j = 0;
  for (int i = 0; i < n; ++i) {
    while (j < m - 1 && p[i].x > crossing(s[j], s[j + 1])) ++j;
    ans = min(ans, s[j](p[i].x) - p[i].y);
  }
  j = 1;
  for (int i = 0; i < m - 1; ++i) {
    double x = crossing(s[i], s[i + 1]);
    if (x > p[n - 1].x) break;
    while (p[j].x < x) ++j;
    ans = min(ans, s[i](x) - Line(p[j - 1], p[j])(x));
  }
  printf("%.3lf\n", ans);
  return 0;
}

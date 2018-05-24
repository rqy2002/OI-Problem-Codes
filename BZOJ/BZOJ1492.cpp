#include <algorithm>
#include <cctype>
#include <cstdio>

const int N = 1000050;
const double eps = 1e-6;

int n;
double f[N];
struct Point{
  double Rate, A, B;
  double x, y, k;
  int id;
  inline friend bool operator<(const Point &a, const Point &b) {
    return a.k > b.k;
  }
}P[N];

inline double abs(double x) { return x < 0 ? -x : x; }

inline double CP(const Point &a, const Point &b, const Point &c) {
  // (b - a) x (c - a)
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

inline double calc(const Point &a, const Point &b) {
  return a.x * b.A + a.y * b.B;
}

inline bool cmp(const Point &a, const Point &b) {
  if (abs(a.x - b.x) <= eps) return a.y < b.y;
  return a.x < b.x;
}

void Solve(int l, int r) { // [l, r)
  if (r - l <= 1) {
    if (l != 0) f[l] = std::max(f[l], f[l - 1]);
    P[l].y = f[l] / (P[l].Rate * P[l].A + P[l].B);
    P[l].x = P[l].y * P[l].Rate;
    return;
  }

  int mid = (l + r) >> 1;
  static Point _tmp[N], CV[N];
  Point *tl = _tmp, *tr = _tmp + (mid - l);
  for (int i = l; i < r; ++i) *((P[i].id < mid ? tl : tr)++) = P[i];
  tl = _tmp;
  for (int i = l; i < r; ++i) P[i] = *(tl++);

  Solve(l, mid);

  int m = 0;
  for (int i = l; i < mid; ++i)
    if (i == l || abs(P[i].x - P[i - 1].x) > eps) {
      while (m > 1 && CP(CV[m - 2], CV[m - 1], P[i]) > 0) --m;
      CV[m++] = P[i];
    }
  for (int i = mid, j = 0; i < r; ++i) {
    while (j < m - 1 && calc(CV[j + 1], P[i]) > calc(CV[j], P[i])) ++j;
    f[P[i].id] = std::max(f[P[i].id], calc(CV[j], P[i]));
  }

  Solve(mid, r);

  tl = P + l, tr = P + mid;
  Point *res = _tmp;
  while (tl < P + mid || tr < P + r)
    if (tr == P + r || (tl != P + mid && cmp(*tl, *tr)))
      *(res++) = *(tl++);
    else
      *(res++) = *(tr++);
  for (tl = P + l, res = _tmp; tl != P + r; ++tl)
    *tl = *(res++);
}

int main() {
  scanf("%d%lf", &n, &f[0]);
  for (int i = 0; i < n; ++i) {
    scanf("%lf%lf%lf", &P[i].A, &P[i].B, &P[i].Rate);
    P[i].k = -P[i].A / P[i].B;
    P[i].id = i;
  }

  std::sort(P, P + n);
  Solve(0, n);
  printf("%.3lf\n", f[n - 1]);

  return 0;
}

/**************************************************************
 * Problem: BZOJ3680
 * Author: Rqy
 * Date: 2018 Feb 27
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstdio>
const double eps = 1e-5;
inline double abs(double x) { return x < 0 ? -x : x; }
inline int sgn(double x) { return x < -eps ? -1 : x > eps; }
const int N = 10050;
int n;
double x[N], y[N], w[N];
double E(double x0, double y0) {
  double ans = .0;
  for (int i = 0; i < n; ++i) {
    double xx = x[i] - x0, yy = y[i] - y0;
    ans += sqrt(xx * xx + yy * yy) * w[i];
  }
  return ans;
}
double randf() { return (double)rand() / RAND_MAX; }
int main() {
  srand((unsigned)(new char));
  double Sx = .0, Sy = .0, Sw = .0;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%lf%lf%lf", &x[i], &y[i], &w[i]);
    Sx += x[i] * w[i]; Sy += y[i] * w[i]; Sw += w[i];
  }
  double x0 = Sx / Sw, y0 = Sy / Sw;
  for (int i = 0; i < n; ++i) w[i] /= Sw;
  double ll = 1e5, ans = E(x0, y0);
  while (sgn(ll)) {
    for (int _ = 0; _ < 10; ++_) {
      double x1 = x0 + (randf()-0.5) * ll, y1 = y0 + (randf()-0.5) * ll;
      double anst = E(x1, y1);
      if (anst < ans) x0 = x1, y0 = y1, ans = anst;
    }
    ll *= 0.9;
  }
  printf("%.3lf %.3lf\n", x0, y0);
  return 0;
}


#include <algorithm>
#include <cstdio>
#include <cmath>
int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
int P, Q, R;
inline double get(double a, double b, double t) {
  return a * t + b * (1 - t);
}
inline double sqr(double x) { return x * x; }
inline double dis(double x1, double y1, double x2, double y2) {
  return sqrt(sqr(x1 - x2) + sqr(y1 - y2));
}
inline double calc(double t1, double t2) {
  double x1 = get(Ax, Bx, t1), y1 = get(Ay, By, t1);
  double x2 = get(Cx, Dx, t2), y2 = get(Cy, Dy, t2);
  return dis(Ax, Ay, x1, y1) / P +
         dis(Dx, Dy, x2, y2) / Q +
         dis(x1, y1, x2, y2) / R;
}
inline double work2(double t1) {
  double l = 0.0, r = 1.0;
  for (int _ = 0; _ < 100; ++_) {
    double m1 = l / 3 + r * 2 / 3;
    double m2 = l * 2 / 3 + r / 3;
    if (calc(t1, m1) > calc(t1, m2)) r = m1;
    else l = m2;
  }
  return calc(t1, l);
}
double work1() {
  double l = 0.0, r = 1.0;
  for (int _ = 0; _ < 100; ++_) {
    double m1 = l / 3 + r * 2 / 3;
    double m2 = l * 2 / 3 + r / 3;
    if (work2(m1) > work2(m2)) r = m1;
    else l = m2;
  }
  return work2(l);
}
int main() {
  scanf("%d%d%d%d%d%d%d%d%d%d%d",
      &Ax, &Ay, &Bx, &By, &Cx, &Cy, &Dx, &Dy, &P, &Q, &R);
  printf("%.2lf\n", work1());
}

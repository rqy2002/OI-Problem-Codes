#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <set>

namespace _rqy{
typedef long double R;

const int N = 10050;
const R eps = 1e-8;

inline int readInt() {
  int ans = 0, c, f = 1;
  while (!isdigit(c = getchar()))
    if (c == '-') f *= -1;
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getchar()));
  return ans * f;
}

int n;
R x1[N], y1[N], x2[N], y2[N];
R sx1, sy1, sx2, sy2, L;

inline R absR(R a) { return a < 0 ? -a : a; }

inline void Change(R a, R b, R c, R d, R l, R &x, R &y) {
  x = (a * c + b * d) / l;
  y = (a * d - b * c) / l;
}

inline R sqr(R b) { return b * b; }

struct Seg{
  R l, ly, r, ry;
  int i;
  Seg() {}
  Seg(R l, R ly, R r, R ry, int i) : l(l), ly(ly), r(r), ry(ry), i(i) {}
  R Get(R b) const {
    return ((b - l) * ry + (r - b) * ly) / (r - l);
  }
  friend bool operator<(const Seg &a, const Seg &b) {
    R cx = std::max(a.l, b.l) + 1e-5;
    return absR(a.Get(cx)) < absR(b.Get(cx));
  }
  inline bool getType() const {
    R t = absR(ly) > absR(ry) ? ly : ry;
    return t > 0;
  }
  inline R getA() const {
    return std::sqrt(1 + sqr((ry - ly) / (r - l)));
  }
} A[N];

struct Event{
  R t;
  int op, i;
  Event() {}
  Event(R t, int op, int i) : t(t), op(op), i(i) {}
  inline bool operator<(const Event &a) const {
    return t < a.t - eps;
  }
} e[N * 2];

std::set<Seg> Q1, Q2;

R x[N * 2], a[N * 2];

void main() {
  int T = readInt();
  while (T--) {
    n = readInt();
    for (int i = 0; i < n; ++i) {
      x1[i] = readInt();
      y1[i] = readInt();
      x2[i] = readInt();
      y2[i] = readInt();
    }
    sx1 = readInt();
    sy1 = readInt();
    sx2 = readInt() - sx1;
    sy2 = readInt() - sy1;
    R l = std::sqrt(sqr(sx2) + sqr(sy2));
    L = readInt();
    int m = 0;
    for (int i = 0; i < n; ++i) {
      x1[i] -= sx1;
      y1[i] -= sy1;
      x2[i] -= sx1;
      y2[i] -= sy1;
      Change(sx2, sy2, x1[i], y1[i], l, x1[i], y1[i]);
      Change(sx2, sy2, x2[i], y2[i], l, x2[i], y2[i]);
      if (x1[i] > x2[i]) {
        std::swap(x1[i], x2[i]);
        std::swap(y1[i], y2[i]);
      }
      A[i] = Seg(x1[i], y1[i], x2[i], y2[i], i);
      e[m++] = Event(x1[i], 1, i);
      e[m++] = Event(x2[i], -1, i);
    }
    std::sort(e, e + m);
    Q1.clear();
    Q2.clear();
    int t = 0;
    for (int i = 0; i < m; ++i) {
      if (i == 0 || absR(e[i].t - x[t - 1]) > eps) {
        x[t] = e[i].t;
        if (t > 0) {
          a[t - 1] = .0;
          if (!Q1.empty()) a[t - 1] += Q1.begin()->getA();
          if (!Q2.empty()) a[t - 1] += Q2.begin()->getA();
          /*
#ifdef DEBUG
          printf("%Lf %Lf ", x[t - 1], x[t]);
          if (!Q1.empty()) printf("%d ", Q1.top().i); else printf("N/A ");
          if (!Q2.empty()) printf("%d ", Q2.top().i); else printf("N/A ");
          printf("%Lf\n", a[t - 1]);
#endif
          */
        }
        ++t;
      }
      int j = e[i].i;
      std::set<Seg> &Q = A[j].getType() ? Q1 : Q2;
      if (e[i].op == 1) Q.insert(A[j]);
      else Q.erase(A[j]);
    }
    R ans = .0, s = .0;
    for (int i = 0, j = 0; i < t; ++i) {
      while (j + 1 < t && x[j + 1] < x[i] + L) {
        s += a[j] * (x[j + 1] - x[j]);
        ++j;
      }
      ans = std::max(ans, s + (j == t - 1 ? .0 : a[j]) * (L - x[j] + x[i]));
      s -= a[i] * (x[i + 1] - x[i]);
    }
    s = .0;
    for (int i = t - 1, j = t - 1; i >= 0; --i) {
      while (j - 1 >= 0 && x[j - 1] > x[i] - L) {
        s += a[j - 1] * (x[j] - x[j - 1]);
        --j;
      }
      ans = std::max(ans, s + (j == 0 ? .0 : a[j - 1]) * (L + x[j] - x[i]));
      if (i > 0) s -= a[i - 1] * (x[i] - x[i - 1]);
    }
    printf("%.20lf\n", (double)ans);
  }
}
};

int main() {
  //freopen("laser.in", "r", stdin);
  //freopen("laser.out", "w", stdout);
  _rqy::main();
  return 0;
}

/**************************************************************
 * Problem: BZOJ4922.cpp
 * Author: Rqy
 * Date: 2018 Feb 26
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 305;
const int M = N * N * 10;
struct P{
  char s[N];
  int a, b, len;
  void input() {
    scanf("%s", s);
    len = a = b = 0;
    while (s[len]) {
      if (s[len] == '(') ++b;
      else if (b) --b;
      else ++a;
      ++len;
    }
  }
  bool operator<(const P &p) const {
    if ((a < b) != (p.a < p.b)) return a < b;
    if (a < b) return a < p.a;
    else return b > p.b;
  }
}p[N];
int _f[2][M];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) p[i].input();
  std::sort(p, p + n);
  int *f = _f[0], *g = _f[1];
  int m = 0;
  f[0] = 0;
  for (int i = 0; i < n; ++i, std::swap(f, g)) {
    for (int j = 0; j <= m; ++j) g[j] = f[j];
    int m1 = m;
    if (p[i].a < p[i].b) {
      m += p[i].b - p[i].a;
      for (int j = m1 + 1; j <= m; ++j) g[j] = -10000000;
    }
    for (int j = p[i].b, k = p[i].a; j <= m && k <= m1; ++j, ++k)
      g[j] = std::max(g[j], f[k] + p[i].len);
  }
  printf("%d\n", f[0]);
  return 0;
}

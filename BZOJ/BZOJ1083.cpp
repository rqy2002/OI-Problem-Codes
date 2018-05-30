#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 300005;
struct Edge{
  int x, y, w;
  bool operator<(const Edge &e)const{ return w < e.w; }
}e[N];
int n, m, f[N], a;
int F(int &x) { return x = (~f[x] ? F(f[x]) : x); }
int U(int x, int y) { return F(x) == F(y) ? 0 : (f[x] = y, 1); }
int main() {
  scanf("%d%d", &n, &m);
  for (int i = (std::fill(f, f + n, -1), 0); i < m; ++i)
    scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].w);
  std::sort(e, e + m);
  for (int i = a = 0; i < m; ++i) a = std::max(a, U(e[i].x, e[i].y)* e[i].w);
  return printf("%d %d\n", n - 1, a) & 0;
}

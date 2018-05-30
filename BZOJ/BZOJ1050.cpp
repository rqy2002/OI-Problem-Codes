#include <algorithm>
#include <cstdio>
typedef long long LL;
const int N = 505, M = 5050;
struct Edge{
  int u, v, w;
  bool operator<(const Edge &x)const{
    return w < x.w;
  }
};
Edge e[M];
int fa[N];
int find(int x) {
  if (fa[x]) return fa[x] = find(fa[x]);
  return x;
}
inline void Union(int x, int y) {
  if ((x = find(x)) != (y = find(y)))
    fa[x] = y;
}
int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}
int main() {
  int n, m, s, t;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i)
    scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
  std::sort(e, e + m);
  scanf("%d%d", &s, &t);
  int ansn = 10000000, ansd = 1;
  for (int l = 0; l + 1 < m; ++l) {
    for (int i = 1; i <= n; ++i) fa[i] = 0;
    Union(e[l].u, e[l].v);
    int r;
    for (r = l + 1; r < m && find(s) != find(t); ++r)
      Union(e[r].u, e[r].v);
    if (find(s) == find(t)) {
      int an = e[r - 1].w, ad = e[l].w;
      if ((LL)an * ansd < (LL)ansn * ad)
        ansn = an, ansd = ad;
    }
  }
  if (ansn == 10000000) return printf("IMPOSSIBLE"), 0;
  int g = gcd(ansn, ansd);
  ansn /= g, ansd /= g;
  printf("%d", ansn);
  if (ansd > 1) printf("/%d", ansd);
  return 0;
}

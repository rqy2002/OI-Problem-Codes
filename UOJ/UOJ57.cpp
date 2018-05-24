/**************************************************************
 * Problem: UOJ57
 * Author: Rqy
 * Date: 2017 Dec 13
 * Algorithm: 扫描线，Splay，并查集，LCA
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 100000;
typedef long long LL;
int n, m, q, s, disable, maxx;
int to[N * 2], nxt[N * 2], pre[N], v[N * 2], ahead[N * 2], left[N * 2], cnt = 0;
int x[N], y[N], px[N], py[N];
inline void addEdge(int i, int j, int vv) {
  v[cnt] = vv;
  nxt[cnt] = pre[i];
  to[pre[i] = cnt++] = j;
}
int tmp[N];
bool cmpArg(int xf, int yf, int xt1, int yt1, int xt2, int yt2) {
  int y1 = yt1 - yf, x1 = xt1 - xf;
  int y2 = yt2 - yf, x2 = xt2 - xf;
  while (1) {
    bool i1 = y1 > 0 && x1 > 0, i2 = x2 > 0 && y2 > 0;
    if (i1 != i2) return i1;
    else if (i1) return (LL)y1 * x2 < (LL)y2 * x1;
    std::swap(x1 *= -1, y1); std::swap(x2 *= -1, y2);
  }
}
bool cmpArg2(int a, int b) { //from[a] == from[b]
  return cmpArg(x[to[a ^ 1]], y[to[a ^ 1]],
      x[to[a]], y[to[a]], x[to[b]], y[to[b]]);
}
void init() {
  memset(pre, -1, sizeof pre);
  memset(left, -1, sizeof left);
  maxx = 0;
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &x[i], &y[i]); x[i] <<= 1, y[i] <<= 1;
    maxx = std::max(maxx, x[i]);
  }
  int xx, yy, vv;
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", &xx, &yy, &vv);
    addEdge(--xx, --yy, vv);
    addEdge(yy, xx, vv);
  }
  double xxx, yyy;
  for (int i = 0; i < q; ++i) {
    scanf("%lf%lf", &xxx, &yyy);
    px[i] = (int)(xxx * 2 + 1.1), py[i] = (int)(yyy * 2 + 1.1);
  }
}
void getQ() {
  for (int i = 0; i < n; ++i) {
    int nu = 0;
    for (int j = pre[i]; ~j; j = nxt[j]) tmp[nu++] = j;
    std::sort(tmp, tmp + nu, cmpArg2);
    for (int j = 1; j < nu; ++j)
      ahead[tmp[j] ^ 1] = tmp[j - 1];
    ahead[tmp[0] ^ 1] = tmp[nu - 1];
  }
  for (int i = 0; i < m * 2; ++i) if (!left[i]) {
    left[i] = s;
    for (int j = ahead[i]; j != i; j = ahead[j]) {
      if (x[to[j]] == maxx && cmpArg2(j ^ 1, ahead[j]))
        disable = s;
      left[j] = s;
    }
    ++s;
  }
}
bool onleftP(int po, int e) {
  return cmpArg(x[to[e]], y[to[e]], px[po], py[po], x[to[e ^ 1]], y[to[e ^ 1]]);
}
namespace Splay{
  int e[N], gghh;
};

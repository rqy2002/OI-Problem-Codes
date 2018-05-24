/**************************************************************
 * Problem: BZOJ2286
 * Author: Rqy
 * Date: 2018 Feb 28
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
typedef long long LL;
const int N = 250050;
int pre[N], to[N * 2], c[N * 2], nxt[N * 2], cnt;
void addEdge(int x, int y, int z) {
  nxt[cnt] = pre[x];
  c[cnt] = z;
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  c[cnt] = z;
  to[pre[y] = cnt++] = x;
}
int dep[N], fa[N][20], minv[N][20], pos[N], cnt2;
void dfs(int x, int f) {
  dep[x] = dep[fa[x][0] = f] + 1;
  pos[x] = ++cnt2;
  for (int i = 0; fa[x][i]; ++i) {
    fa[x][i + 1] = fa[fa[x][i]][i];
    minv[x][i + 1] = std::min(minv[x][i], minv[fa[x][i]][i]);
  }
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != f) { minv[to[i]][0] = c[i]; dfs(to[i], x); }
}
int LCA(int x, int y) {
  if (dep[x] < dep[y]) std::swap(x, y);
  for (int i = 19; ~i; --i) if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
  for (int i = 19; ~i; --i) if (fa[x][i] != fa[y][i]) {
    x = fa[x][i];
    y = fa[y][i];
  }
  return x == y ? x : fa[x][0];
}
int minp(int x, int y) {
  int ans = 1000000000;
  if (dep[x] < dep[y]) std::swap(x, y);
  for (int i = 19; ~i; --i) if (dep[fa[x][i]] >= dep[y]) {
    ans = std::min(ans, minv[x][i]);
    x = fa[x][i];
  }
  if (x == y) return ans;
  for (int i = 19; ~i; --i) if (fa[x][i] != fa[y][i]) {
    ans = std::min(ans, std::min(minv[x][i], minv[y][i]));
    x = fa[x][i];
    y = fa[y][i];
  }
  return std::min(ans, std::min(minv[x][0], minv[y][0]));
}
int pres[N], nxts[N];
inline void addS(int x, int y) { nxts[y] = pres[x]; pres[x] = y; }
LL f(int x) {
  LL ans = 0;
  for (int y = pres[x]; y; y = nxts[y])
    ans += std::min(f(y), (LL)minp(x, y));
  if (!ans) ans = 10000000000000000LL;
  pres[x] = 0;
  return ans;
}
bool cmp(int a, int b) { return pos[a] < pos[b]; }
int p[N], stack[N];
int main() {
  memset(pre, -1, sizeof pre);
  int n;
  scanf("%d", &n);
  for (int i = 1, x, y, z; i < n; ++i) {
    scanf("%d%d%d", &x, &y, &z);
    addEdge(x, y, z);
  }
  dfs(1, 0);
  int m;
  scanf("%d", &m);
  while (m--) {
    int k;
    scanf("%d", &k);
    for (int i = 0; i < k; ++i) scanf("%d", &p[i]);
    std::sort(p, p + k, cmp);
    int tot = 1;
    for (int i = 1; i < k; ++i)
      if (LCA(p[i], p[tot - 1]) != p[tot - 1]) p[tot++] = p[i];
    int top = 0;
    stack[top++] = 1;
    for (int i = 0; i < tot; ++i) {
      int x = p[i], y = LCA(stack[top - 1], x);
      while (true) {
        if (top <= 1 || dep[y] >= dep[stack[top - 2]]) {
          if (y != stack[--top]) addS(y, stack[top]);
          if (stack[top - 1] != y) stack[top++] = y;
          break;
        }
        addS(stack[top - 2], stack[top - 1]); --top;
      }
      if (stack[top - 1] != x) stack[top++] = x;
    }
    while (--top) addS(stack[top - 1], stack[top]);
    printf("%lld\n", f(1));
  }
  return 0;
}

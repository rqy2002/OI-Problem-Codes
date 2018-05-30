#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 100050;
const int M = 1000050;

int pre[N], to[M], nxt[M], cnt;
int n, m, f[N], fa[N][20], dep[N], ind[N];
int que[N], siz[N];

inline void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
}

int LCA(int x, int y) {
  if (dep[x] < dep[y]) std::swap(x, y);
  for (int i = 19; i >= 0; --i)
    if (dep[fa[x][i]] >= dep[y])
      x = fa[x][i];
  for (int i = 19; i >= 0; --i)
    if (fa[x][i] != fa[y][i]) {
      x = fa[x][i];
      y = fa[y][i];
    }
  return x == y ? x : f[x];
}

void Build(int x) {
  dep[x] = 1 + dep[fa[x][0] = f[x]];
  for (int i = 0; fa[x][i] != 0; ++i)
    fa[x][i + 1] = fa[fa[x][i]][i];
}

int main() {
  //freopen("math.in", "r", stdin);
  //freopen("math.out", "w", stdout);
  scanf("%d", &n);
  memset(pre, -1, sizeof pre);

  for (int x = 1; x <= n; ++x)
    for (int y; ; ) {
      scanf("%d", &y);
      if (y == 0) break;
      addEdge(y, x);
      ++ind[x];
    }

  int hd = 0, tl = 0;
  memset(f, -1, sizeof f);
  for (int i = 1; i <= n; ++i)
    if (ind[i] == 0) {
      dep[i] = 1;
      f[i] = 0;
      que[tl++] = i;
    }

  while (hd < tl) {
    int x = que[hd++];
    for (int i = pre[x]; i != -1; i = nxt[i]) {
      int y = to[i];
      if (f[y] == -1)
        f[y] = x;
      else if (f[y] != 0)
        f[y] = LCA(f[y], x);
      if ((--ind[y]) == 0)
        Build(que[tl++] = y);
    }
  }

  for (int i = n - 1; i >= 0; --i)
    siz[f[que[i]]] += ++siz[que[i]];
  for (int i = 1; i <= n; ++i)
    printf("%d\n", siz[i] - 1);
  return 0;
}

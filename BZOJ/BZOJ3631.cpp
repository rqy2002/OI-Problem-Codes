#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>

const int N = 300050;

int pre[N], to[N * 2], nxt[N * 2], cnt;
int pre2[N], to2[N * 2], nxt2[N * 2], cnt2;
int n, fa[N], sum[N], count[N];
int ff[N], rk[N], anc[N];
bool vis[N];

inline int readInt() {
  int ans = 0, c;
  while (!isdigit(c = getchar()));
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getchar()));
  return ans;
}

inline void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  to[pre[y] = cnt++] = x;
}

inline void addEdge2(int x, int y) {
  nxt2[cnt2] = pre2[x];
  to2[pre2[x] = cnt2++] = y;
  nxt2[cnt2] = pre2[y];
  to2[pre2[y] = cnt2++] = x;
}

int Find(int x) { return ff[x] == 0 ? x : ff[x] = Find(ff[x]); }
inline void Union(int x, int y) {
  if ((x = Find(x)) != (y = Find(y))) {
    if (rk[x] < rk[y]) anc[ff[x] = y] = anc[x];
    else rk[ff[y] = x] = std::max(rk[x], rk[y] + 1);
  }
}

void dfs(int x) {
  anc[x] = x;
  rk[x] = ff[x] = 0;
  for (int i = pre[x]; i != -1; i = nxt[i])
    if (to[i] != fa[x]) {
      fa[to[i]] = x;
      dfs(to[i]);
      Union(x, to[i]);
    }
  for (int i = pre2[x]; i != -1; i = nxt2[i])
    if (vis[to2[i]]) {
      int l = anc[Find(to2[i])];
      --sum[l];
      --sum[fa[l]];
      ++sum[x];
      ++sum[to2[i]];
    }
  vis[x] = true;
}

int dfs2(int x) {
  for (int i = pre[x]; i != -1; i = nxt[i])
    if (to[i] != fa[x])
      sum[x] += dfs2(to[i]);
  return sum[x];
}

int main() {
  memset(pre, -1, sizeof pre);
  memset(pre2, -1, sizeof pre2);
  int n = readInt();
  for (int i = 1, x = readInt(), y; i < n; ++i, x = y) {
    addEdge2(x, y = readInt());
    ++count[y];
  }
  for (int i = 1; i < n; ++i)
    addEdge(readInt(), readInt());
  dfs(1);
  dfs2(1);
  for (int i = 1; i <= n; ++i)
    printf("%d\n", sum[i] - count[i]);
  return 0;
}

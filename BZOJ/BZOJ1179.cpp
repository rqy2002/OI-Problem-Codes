#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
inline int readInt() {
  int ans = 0, c;
  while (!isdigit(c = getchar()));
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getchar()));
  return ans;
}
const int N = 500050;
int pre[N], nxt[N], to[N], cnt = 0;
inline void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
}
int dfn[N], scc[N], scnt = 0, cnt3 = 0;
int stack[N], top = 0;
int tarjan(int x) {
  int low = dfn[x] = ++cnt3;
  stack[top++] = x;
  for (int i = pre[x]; ~i; i = nxt[i])
    if (!dfn[to[i]])
      low = std::min(low, tarjan(to[i]));
    else if (!scc[to[i]])
      low = std::min(low, dfn[to[i]]);
  if (low == dfn[x]) {
    ++scnt;
    while (stack[--top] != x)
      scc[stack[top]] = scnt;
    scc[stack[top]] = scnt;
  }
  return low;
}
int pre2[N], nxt2[N], to2[N], cnt2 = 0;
inline void addEdge2(int x, int y) {
  nxt2[cnt2] = pre2[x];
  to2[pre2[x] = cnt2++] = y;
}
int v[N], in[N], f[N];
bool vis[N], bar[N];
int main() {
  int n, m, x, s;
  n = readInt();
  m = readInt();
  memset(pre, -1, sizeof pre);
  memset(pre2, -1, sizeof pre2);
  while (m--) {
    x = readInt();
    addEdge(--x, readInt() - 1);
  }
  for (int i = 0; i < n; ++i) if (!dfn[i]) tarjan(i);
  for (int i = 0; i < n; ++i) v[scc[i]] += readInt();
  s = scc[readInt() - 1];
  m = readInt();
  while (m--) bar[scc[readInt() - 1]] = true;
  for (int x = 0; x < n; ++x)
    for (int i = pre[x]; ~i; i = nxt[i])
      if (scc[x] != scc[to[i]])
        addEdge2(scc[x], scc[to[i]]);
  int *que = stack, head = 0, tail = 0, ans = 0;
  vis[que[tail++] = s] = 1;
  while (head != tail) {
    int x = que[head++];
    for (int i = pre2[x]; ~i; i = nxt2[i])
      if (!vis[to2[i]]) que[tail++] = to2[i], vis[to2[i]] = 1;
  }
  for (int x = 1; x <= scnt; ++x) if (vis[x])
    for (int i = pre2[x]; ~i; i = nxt2[i])
      ++in[to2[i]];
  head = tail = 0;
  que[tail++] = s;
  while (head != tail) {
    int x = que[head++];
    f[x] += v[x];
    if (bar[x]) ans = std::max(ans, f[x]);
    for (int i = pre2[x]; ~i; i = nxt2[i]) {
      f[to2[i]] = std::max(f[to2[i]], f[x]);
      if (!--in[to2[i]]) que[tail++] = to2[i];
    }
  }
  return printf("%d\n", ans) & 0;
}

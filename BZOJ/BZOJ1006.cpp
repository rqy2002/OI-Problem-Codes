#include <cctype>
#include <cstdlib>
#include <cstdio>
#include <cstring>
const int N = 10050;
const int M = 1050000;
struct Node{
  int v, nxt;
}nodes[M];
int cnt;
int pre[N], to[M * 2], nxt[M * 2];
int head[N];
int f[N], P[N];
bool vis[N];
int n, m;
inline void add(int h, int v) {
  nodes[++cnt].v = v;
  nodes[cnt].nxt = head[h];
  head[h] = cnt;
}
void MCS() {
  memset(nodes, 0, sizeof nodes);
  memset(head, 0, sizeof head);
  memset(vis, 0, sizeof vis);
  memset(f, 0, sizeof f);
  int i, j, best = 0;
  for (i = 1; i <= n; ++i) 
    add(0, i);
  for (j = n; j; --j) 
    while (1) {
      int x;
      while (vis[nodes[x = head[best]].v]) head[best] = nodes[x].nxt;
      if (!x) { 
        --best;
        continue;
      }
      x = nodes[x].v;
      vis[P[j] = x] = 1;
      for (i = pre[x]; ~i; i = nxt[i]) {
        if (vis[to[i]]) continue;
        add(++f[to[i]], to[i]);
        if (f[to[i]] > best)
          best = f[to[i]];
      }
      break;
    }
}

int cnt2;
inline void addedge(int u, int v) {
  nxt[cnt2] = pre[u];
  to[pre[u] = cnt2++] = v;
}
inline int readInt() {
  int ans = 0;
  char c;
  do c = getchar(); while (!isdigit(c));
  do {
    ans = ans * 10 + c - '0';
    c = getchar();
  } while (isdigit(c));
  return ans;
}
int mark[N], color[N];
int main() {
  cnt = cnt2 = 0;
  memset(pre, -1, sizeof pre);
  n = readInt();
  m = readInt();
  int x, y;
  while (m--) {
    x = readInt();
    y = readInt();
    addedge(x, y);
    addedge(y, x);
  }
  MCS();
  memset(color, 0, sizeof color);
  memset(mark, 0, sizeof mark);
  int ans = 0;
  for (int j = n; j; --j) {
    int x = P[j];
    for (int i = pre[x]; ~i; i = nxt[i])
      mark[color[to[i]]] = j;
    for (color[x] = 1; mark[color[x]] == j; ++color[x]);
    if (color[x] > ans)
      ans = color[x];
  }
  printf("%d\n", ans);
  return 0;
}

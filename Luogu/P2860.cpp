#include <cstdio>

const int N = 5000;
const int M = 10000;

int n, pre[N], nxt[M * 2], to[M * 2], cnt;

inline void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  to[pre[y] = cnt++] = x;
}

int stack[N], top;
int dfn[N], cnt2, bcnt;
bool in[N];
int ans = 0;

inline int min(int x, int y) { return x < y ? x : y; }
int Tarjan(int x, int fe) {
  int lowx = dfn[x] = ++cnt2;
  stack[top++] = x;
  for (int i = pre[x]; i >= 0; i = nxt[i])
    if (dfn[to[i]] == 0)
      lowx = min(lowx, Tarjan(to[i], i));
    else if ((i ^ 1) != fe)
      lowx = min(lowx, dfn[to[i]]);
  if (lowx >= dfn[x]) {
    int tt = top;
    while (stack[--top] != x);
    int k = 0;
    for (int i = top; i < tt; ++i) in[stack[i]] = true;
    for (int i = top; i < tt; ++i)
      for (int j = pre[stack[i]]; j >= 0; j = nxt[j])
        if (!in[to[j]])
          ++k;
    if (k == 1) ++ans;
    for (int i = top; i < tt; ++i) in[stack[i]] = false;
  }
  return lowx;
}

int main() {
  int m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) pre[i] = -1;
  while (m--) {
    int x, y;
    scanf("%d%d", &x, &y);
    addEdge(x, y);
  }
  Tarjan(1, -1);
  printf("%d\n", (ans + 1) / 2);
  return 0;
}

/**************************************************************
 * Problem: Luogu P2444
 * Author: Rqy
 * Date: 2017 Dec 28
 * Algorithm: AC自动机
**************************************************************/
#include <cstdio>
#include <cstring>
const int N = 30050;
bool d[N], vis1[N], vis2[N];
int nxt[N][2], fail[N], cnt = 0;
char s[N];
int que[N];
bool dfs(int x) {
  if (vis1[x]) return true;
  if (vis2[x]) return false;
  if (d[x]) return false;
  vis1[x] = vis2[x] = true;
  for (int i = 0; i < 2; ++i)
    if (dfs(nxt[x][i])) return true;
  vis1[x] = false;
  return false;
}
int main() {
  int n;
  scanf("%d", &n);
  memset(nxt, 0, sizeof nxt);
  memset(d, 0, sizeof d);
  cnt = 1;
  for (int i = 0; i < n; ++i) {
    scanf("%s", s);
    int o = 0;
    for (int j = 0; s[j]; ++j) {
      int c = s[j] - '0';
      if (!nxt[o][c]) nxt[o][c] = cnt++;
      o = nxt[o][c];
    }
    d[o] = true;
  }
  int head = 0, tail = 0;
  for (int i = 0; i < 2; ++i) if (nxt[0][i])
    fail[que[tail++] = nxt[0][i]] = 0;
  while (head < tail)
    for (int i = 0, o = que[head++]; i < 2; ++i)
      if (nxt[o][i])
        d[nxt[o][i]] |= d[fail[que[tail++] = nxt[o][i]] = nxt[fail[o]][i]];
      else
        nxt[o][i] = nxt[fail[o]][i];
  memset(vis1, 0, sizeof vis1);
  memset(vis2, 0, sizeof vis2);
  printf("%s\n", dfs(0) ? "TAK" : "NIE");
  return 0;
}

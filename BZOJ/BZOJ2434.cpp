/**************************************************************
 * Problem: BZOJ2434
 * Author: Rqy
 * Date: 2018 Feb 28
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 100050;
int fa[N], fail[N], ch[N][26], cnt = 1, que[N];
int pre[N], nxt[N], left[N], right[N], cnt2, pos[N];
inline void addSon(int x, int y) { nxt[y] = pre[x]; pre[x] = y; }
void dfs(int x) {
  left[x] = ++cnt2;
  for (int y = pre[x]; y; y = nxt[y]) dfs(y);
  right[x] = cnt2;
}
int A[N];
void add(int i, int x) { for (; i <= cnt2; i += i & -i) A[i] += x; }
int get(int i) { int x = 0; for (; i; i -= i & -i) x += A[i]; return x; }
char s[N];
int preq[N], nxtq[N], to[N], ans[N];
inline void addQ(int x, int y) { nxtq[y] = preq[x]; preq[x] = y; }
int main() {
  scanf("%s", s);
  int o = 0, n = 0;
  for (char *c = s; *c; ++c) {
    if (*c == 'B') o = fa[o];
    else if (*c == 'P') pos[n++] = o;
    else {
      if (!ch[o][*c - 'a']) fa[ch[o][*c - 'a'] = cnt++] = o;
      o = ch[o][*c - 'a'];
    }
  }
  int hd = 0, tl = 0;
  for (int i = 0; i < 26; ++i)
    if (ch[0][i]) addSon(0, que[tl++] = ch[0][i]);
  while (hd < tl)
    for (int i = 0, x = que[hd++]; i < 26; ++i) if (ch[x][i]) {
      int y = ch[x][i], l = fail[x];
      while (l && !ch[l][i]) l = fail[l];
      addSon(fail[que[tl++] = y] = ch[l][i], y);
    }
  dfs(0);
  int m;
  scanf("%d", &m);
  memset(preq, -1, sizeof preq);
  for (int i = 0, x; i < m; ++i) {
    scanf("%d%d", &to[i], &x);
    to[i] = pos[to[i] - 1];
    addQ(x - 1, i);
  }
  n = o = 0;
  for (char *c = s; *c; ++c) {
    if (*c == 'B') add(left[o], -1), o = fa[o];
    else if (*c == 'P') {
      for (int i = preq[n++]; ~i; i = nxtq[i])
        ans[i] = get(right[to[i]]) - get(left[to[i]] - 1);
    } else o = ch[o][*c - 'a'], add(left[o], 1);
  }
  for (int i = 0; i < m; ++i)
    printf("%d\n", ans[i]);
  return 0;
}

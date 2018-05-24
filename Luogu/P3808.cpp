/**************************************************************
 * Problem: Luogu P3796
 * Author: Rqy
 * Date: 2017 Dec 28
 * Algorithm: AC自动机
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 1000050;
bool vis[N];
int v[N], fail[N], nxt[N][26], cnt;
int que[N];
char s[N];
int main() {
  int n;
  scanf("%d", &n);
  cnt = 1;
  memset(nxt, 0, sizeof nxt);
  for (int i = 0; i < n; ++i) {
    scanf("%s", s);
    int o = 0;
    for (int j = 0; s[j]; ++j) {
      int c = s[j] - 'a';
      if (!nxt[o][c]) nxt[o][c] = cnt++;
      o = nxt[o][c];
    }
    v[i] = o;
  }
  memset(fail, -1, sizeof fail);
  fail[0] = 0;
  int head = 0, tail = 0;
  for (int i = 0; i < 26; ++i) if (nxt[0][i]) {
    fail[nxt[0][i]] = 0;
    que[tail++] = nxt[0][i];
  }
  while (head < tail)
    for (int o = que[head++], i = 0; i < 26; ++i)
      if (nxt[o][i]) {
        fail[nxt[o][i]] = nxt[fail[o]][i];
        que[tail++] = nxt[o][i];
      } else {
        nxt[o][i] = nxt[fail[o]][i];
      }
  scanf("%s", s);
  int o = 0;
  vis[o] = true;
  for (int i = 0; s[i]; ++i) {
    int c = s[i] - 'a';
    o = nxt[o][c];
    for (int j = o; !vis[j]; j = fail[j]) vis[j] = true;
  }
  int ans = 0;
  for (int i = 0; i < n; ++i) if (vis[v[i]]) ++ans;
  printf("%d\n", ans);
  return 0;
}

/**************************************************************
 * Problem: Luogu P2414
 * Author: Rqy
 * Date: 2017 Dec 28
 * Algorithm: AC自动机,DFS,树状数组
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 100050;
int fa[N], p[N], nxt[N][26], fail[N], cc[N], cnt;
int que[N];
char s[N];
int lef[N], righ[N];
int left[N], right[N], cnt2 = 0;
int ans[N];
void dfs(int x) {
  left[x] = cnt2++;
  for (int i = lef[x]; i; i = righ[i])
    dfs(i);
  right[x] = cnt2 - 1;
}
struct Query{
  int x, y, id;
  bool operator<(const Query &t)const{
    return y < t.y;
  }
}q[N];
int S[N];
void add(int i, int x) {
  while (i < cnt2) {
    S[i] += x;
    i += i & -i;
  }
}
int query(int i) {
  int ans = 0;
  while (i) {
    ans += S[i];
    i -= i & -i;
  }
  return ans;
}
int main() {
  int n = 0, m;
  scanf("%s", s);
  int o = 0;
  cnt = 1;
  for (char *c = s; *c; ++c) {
    if (*c == 'P')
      p[++n] = o;
    else if (*c == 'B')
      o = fa[o];
    else {
      int t = *c - 'a';
      if (!nxt[o][t]) {
        cc[nxt[o][t] = cnt++] = t;
        fa[nxt[o][t]] = o;
      }
      o = nxt[o][t];
    }
  }
  int head = 0, tail = 0;
  for (int i = 0; i < 26; ++i) if (nxt[0][i])
    fail[que[tail++] = nxt[0][i]] = 0;
  while (head < tail) {
    o = que[head++];
    righ[o] = lef[fail[o]];
    lef[fail[o]] = o;
    for (int i = 0; i < 26; ++i)
      if (nxt[o][i]) {
        fail[nxt[o][i]] = nxt[fail[o]][i];
        que[tail++] = nxt[o][i];
      }
      else
        nxt[o][i] = nxt[fail[o]][i];
  }
  dfs(0);
  scanf("%d", &m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &q[i].x, &q[i].y);
    q[i].id = i;
  }
  std::sort(q, q + m);
  int j = 0, l = 0;
  o = 0;
  for (char *c = s; *c; ++c) {
    if (*c == 'P') {
      ++l;
      for (; q[j].y == l; ++j) {
        int x = p[q[j].x];
        ans[q[j].id] = query(right[x]) - query(left[x] - 1);
      }
    } else if (*c == 'B') {
      add(left[o], -1);
      o = fa[o];
    } else {
      o = nxt[o][*c - 'a'];
      add(left[o], 1);
    }
  }
  for (int i = 0; i < m; ++i) printf("%d\n", ans[i]);
  return 0;
}

/**************************************************************
 * Problem: BZOJ2555
 * Author: Rqy
 * Date: 2018 Feb 28
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 1500050;
namespace LCT{
int ch[N][2], fa[N], addv[N], v[N];
inline void add(int x, int y) {
  if (x) { v[x] += y; addv[x] += y; }
}
inline void pushd(int o) {
  if (addv[o]) {
    add(ch[o][0], addv[o]);
    add(ch[o][1], addv[o]);
    addv[o] = 0;
  }
}
inline int dir(int x) {
  return ch[fa[x]][0] == x ? 0 : ch[fa[x]][1] == x ? 1 : -1;
}
inline void rotate(int x) {
  int f = fa[x], d = dir(x);
  fa[x] = fa[f];
  if (~dir(f)) ch[fa[f]][dir(f)] = x;
  if ((ch[f][d] = ch[x][d ^ 1])) fa[ch[x][d ^ 1]] = f;
  fa[ch[x][d ^ 1] = f] = x;
}
int st[N];
void splay(int x) {
  int top = 0;
  for (int y = x; ~dir(y); y = fa[y]) st[top++] = fa[y];
  while (top--) pushd(st[top]);
  pushd(x);
  for (; ~dir(x); rotate(x))
    if (~dir(fa[x])) rotate(dir(fa[x]) == dir(x) ? fa[x] : x);
}
void access(int x) {
  splay(x); ch[x][1] = 0; int f;
  while ((f = fa[x])) { splay(f); ch[f][1] = x; x = f; }
}
inline void link(int x, int f) {
  fa[x] = f; access(f); splay(f); add(f, v[x]);
}
inline void cut(int x) {
  access(x); splay(x); add(ch[x][0], -v[x]);
  fa[ch[x][0]] = 0; ch[x][0] = 0;
}
};
namespace SAM{
int ch[N][26], fa[N], len[N], root, last, cnt;
inline int newNode(int x) {
  memcpy(ch[++cnt], ch[x], sizeof ch[x]);
  fa[cnt] = fa[x]; len[cnt] = len[x];
  return cnt;
}
void insert(int x) {
  int o = ++cnt, q = last;
  len[o] = len[last] + 1;
  last = o;
  LCT::v[o] = 1;
  for (; q && !ch[q][x]; q = fa[q]) ch[q][x] = o;
  if (!q) LCT::link(o, fa[o] = 1);
  else if (len[ch[q][x]] == len[q] + 1) LCT::link(o, fa[o] = ch[q][x]);
  else {
    int p = ch[q][x], pq = newNode(p); len[pq] = len[q] + 1;
    LCT::link(pq, fa[p]);
    fa[p] = fa[o] = pq;
    LCT::cut(p); LCT::link(p, pq); LCT::link(o, pq);
    for (; q && ch[q][x] == p; q = fa[q]) ch[q][x] = pq;
  }
}
int get(const char *s) {
  int o = root;
  for (const char *c = s; *c; ++c) {
    if (!ch[o][*c - 'A']) return 0;
    o = ch[o][*c - 'A'];
  }
  LCT::splay(o);
  return LCT::v[o];
}
void init() {
  root = last = ++cnt;
}
};
void decode(char *s, int l) {
  int len = strlen(s);
  for (int i = 0; i < len; ++i)
    std::swap(s[i], s[l = (l * 131 + i) % len]);
}
const int M = 3000050;
char s[M], op[10];
int main() {
  SAM::init();
  int n, mask = 0;
  scanf("%d", &n);
  scanf("%s", s);
  for (char *c = s; *c; ++c) SAM::insert(*c - 'A');
  while (n--) {
    scanf("%s%s", op, s);
    decode(s, mask);
    if (*op == 'Q') {
      int ans = SAM::get(s);
      mask ^= ans;
      printf("%d\n", ans);
    } else for (char *c = s; *c; ++c)
      SAM::insert(*c - 'A');
  }
  return 0;
}

/**************************************************************
 * Problem: BZOJ2049
 * Author: Rqy
 * Date: 2018 Feb 26
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 10050;
int fa[N], ch[N][2];
bool rev[N];
inline int dir(int x) {
  return ch[fa[x]][0] == x ? 0 : ch[fa[x]][1] == x ? 1 : -1;
}
inline void pushd(int x) {
  if (rev[x]) {
    rev[ch[x][0]] ^= 1; rev[ch[x][1]] ^= 1; rev[x] = 0;
    std::swap(ch[x][0], ch[x][1]);
  }
}
inline void rotate(int x) {
  int f = fa[x], d = dir(x);
  fa[x] = fa[f];
  if (~dir(f)) ch[fa[f]][dir(f)] = x;
  if (ch[f][d] = ch[x][d ^ 1]) fa[ch[f][d]] = f;
  fa[ch[x][d ^ 1] = f] = x;
}
int stack[N];
void splay(int x) {
  int top = 0, y = x;
  while (~dir(y)) stack[top++] = y = fa[y];
  while (top--) pushd(stack[top]); 
  pushd(x);
  for (; ~dir(x); rotate(x))
    if (~dir(fa[x])) rotate(dir(fa[x]) == dir(x) ? fa[x] : x);
}
void access(int x) {
  splay(x); ch[x][1] = 0; int v;
  while (v = fa[x]) { splay(v); ch[v][1] = x; x = v; }
}
inline void mkroot(int x) { access(x); splay(x); rev[x] ^= 1; }
inline void cut(int x, int y) {
  mkroot(x); access(y); splay(y);
  fa[x] = ch[y][0] = 0;
}
inline void link(int x, int y) {
  mkroot(x); splay(fa[x] = y);
}
inline bool query(int x, int y) {
  mkroot(x); access(y); splay(y); return fa[x] != 0 || x == y;
}
int main() {
  int n, m, x, y;
  scanf("%d%d", &n, &m);
  char s[20];
  while (m--) {
    scanf("%s%d%d", s, &x, &y);
    if (*s == 'C') link(x, y);
    if (*s == 'D') cut(x, y);
    if (*s == 'Q') puts(query(x, y) ? "Yes" : "No");
  }
  return 0;
}

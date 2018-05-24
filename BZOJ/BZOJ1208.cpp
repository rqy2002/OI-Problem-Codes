/**************************************************************
 * Problem: BZOJ1208
 * Author: Rqy
 * Date: 2017 Dec 07
 * Algorithm: Splay
**************************************************************/
#include <cstdio>
const int N = 80050;
const int mod = 1000000;
int ch[N][2], fa[N], root, v[N];
inline int dir(int x) { return ch[fa[x]][1] == x; }
inline void rotate(int x) {
  int f = fa[x], d = dir(x);
  if (fa[x] = fa[f]) ch[fa[f]][dir(f)] = x;
  else root = x;
  if (ch[f][d] = ch[x][d ^ 1]) fa[ch[f][d]] = f;
  fa[ch[x][d ^ 1] = f] = x;
}
inline void splay(int x) {
  for (; fa[x]; rotate(x))
    if (fa[fa[x]]) rotate(dir(fa[x]) == dir(x) ? fa[x] : x);
}
int cnt = 0;
inline int newNode(int x) {
  v[++cnt] = x;
  fa[cnt] = ch[cnt][0] = ch[cnt][1] = 0;
  return cnt;
}
inline void insert(int x) {
  int y = newNode(x);
  if (root == 0) root = y;
  int o = root;
  while (o != y) {
    if (v[o] < v[y]) {
      if (!ch[o][1]) fa[ch[o][1] = y] = o;
      o = ch[o][1];
    } else {
      if (!ch[o][0]) fa[ch[o][0] = y] = o;
      o = ch[o][0];
    }
  }
  splay(y);
}
inline int pop(int x) {
  int left = 0, right = 0;
  int o = root;
  while (o) {
    if (v[o] <= x) {
      left = o;
      o = ch[o][1];
    } else {
      right = o;
      o = ch[o][0];
    }
  }
  int ans;
  if (!right || (left && x - v[left] <= v[right] - x)) ans = x - v[o = left];
  else ans = v[o = right] - x;
  if (ch[o][1]) {
    right = ch[o][1];
    while (ch[right][0]) right = ch[right][0];
    splay(right);
  }
  while (ch[o][0]) rotate(ch[o][0]);
  if (root == o) root = 0;
  else ch[fa[o]][dir(o)] = 0;
  return ans;
}
int main() {
  int n, ans = 0;
  scanf("%d", &n);
  int t = 0, x, y;
  while (n--) {
    scanf("%d%d", &x, &y);
    if (!root || x == t) {
      insert(y);
      t = x;
    } else {
      ans = ((long long)ans + pop(y)) % mod;
    }
  }
  printf("%d\n", ans);
  return 0;
}

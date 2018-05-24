/**************************************************************
 * Problem: BZOJ3669
 * Author: _rqy
 * Date: 2018 Mar 19
**************************************************************/
#include <algorithm>
#include <cstdio>

const int M = 100050;
const int N = 50050 + M;

namespace LCT{
int fa[N], ch[N][2];
int val[N], maxP[N];
bool rev[N];

inline int dir(int x) {
  if (ch[fa[x]][0] == x) return 0;
  else if (ch[fa[x]][1] == x) return 1;
  else return -1;
}

inline void pushd(int x) {
  if (rev[x]) {
    std::swap(ch[x][0], ch[x][1]);
    rev[ch[x][0]] ^= 1;
    rev[ch[x][1]] ^= 1;
    rev[x] = 0;
  }
}

inline void upd(int x) {
  if (val[maxP[ch[x][0]]] > val[maxP[ch[x][1]]])
    maxP[x] = maxP[ch[x][0]];
  else
    maxP[x] = maxP[ch[x][1]];
  if (val[x] > val[maxP[x]])
    maxP[x] = x;
}

void Rotate(int x) {
  int d = dir(x), f = fa[x];
  fa[x] = fa[f];
  if (dir(f) != -1) ch[fa[f]][dir(f)] = x;
  if ((ch[f][d] = ch[x][d ^ 1]) != 0) fa[ch[f][d]] = f;
  upd(ch[x][d ^ 1] = f);
  upd(fa[f] = x);
}

void Splay(int x) {
  static int stack[N];
  int top = 0;
  for (int y = x; dir(y) != -1; y = fa[y]) stack[top++] = fa[y];
  while (top--) pushd(stack[top]);
  pushd(x);
  for (; dir(x) != -1; Rotate(x))
    if (dir(fa[x]) != -1) Rotate(dir(fa[x]) == dir(x) ? fa[x] : x);
}

void Access(int x) {
  Splay(x); ch[x][1] = 0; upd(x);
  while (fa[x] != 0) { Splay(fa[x]); ch[fa[x]][1] = x; upd(x = fa[x]); }
}

inline void MkRoot(int x) { Access(x); Splay(x); rev[x] ^= -1; }
inline int Query(int x, int y) {
  if (x == y) return 0;
  MkRoot(x); Access(y); Splay(y);
  if (fa[x] == 0) return -1;
  else return maxP[y];
}
inline void Link(int x, int y) {
  if (Query(x, y) == -1) { MkRoot(x); fa[x] = y; }
}
inline void Cut(int x, int y) {
  MkRoot(x); Access(y); Splay(y); fa[x] = ch[y][0] = 0; upd(y);
}
};

int n, m;

struct Edge{
  int from, to, A, B;
  friend bool operator<(const Edge &lhs, const Edge &rhs) {
    return lhs.A < rhs.A;
  }
}edges[M];

void Init() {
  using LCT::val;
  using LCT::maxP;

  scanf("%d%d", &n, &m);
  for (int i = 0; i <= n; ++i) {
    val[i] = 0;
    maxP[i] = i;
  }
  for (int i = 0; i < m; ++i)
    scanf("%d%d%d%d", &edges[i].from, &edges[i].to, &edges[i].A, &edges[i].B);
  std::sort(edges, edges + m);
  for (int i = 0; i < m; ++i) {
    val[i + n + 1] = edges[i].B;
    maxP[i + n + 1] = maxP[i + n + 1];
  }
}

void Link(int e) {
  using LCT::Link;
  using LCT::Cut;
  using LCT::Query;

  int u = edges[e].from, v = edges[e].to;
  if (u == v) return;
  int ee = Query(u, v), e1 = ee - n - 1;
  if (ee == -1) {
    Link(e + n + 1, u);
    Link(e + n + 1, v);
  } else if (edges[e1].B > edges[e].B) {
    Cut(ee, edges[e1].from);
    Cut(ee, edges[e1].to);
    Link(e + n + 1, u);
    Link(e + n + 1, v);
  }
}

int main(){
  Init();
  int ans = 0x7fffffff;
  for (int i = 0; i < m; ++i) {
    Link(i);
    int v = LCT::Query(1, n);
    if (v != -1) ans = std::min(ans, edges[i].A + edges[v - n - 1].B);
  }
  if (ans >= 10000000) puts("-1");
  else printf("%d\n", ans);
  return 0;
}

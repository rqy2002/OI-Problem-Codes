/**************************************************************
 * Problem: Luogu P3676
 * Author: Rqy
 * Date: 2017 Dec 24
 * Algorithm: 树链剖分
**************************************************************/
#include <cctype>
#include <cstdio>
#include <cstring>
typedef long long LL;
const LL N = 200050;
LL n;

inline char readChar() {
  static char buf[10000000], *p = buf, *end = buf;
  if (p == end) end = buf + fread(p = buf, sizeof(char), 10000000, stdin);
  return *(p++);
}

inline int readInt() {
  int ans = 0, c, f = 1;
  while (!isdigit(c = readChar())) if (c == '-') f *= -1;
  do ans = ans * 10 + c - '0';
  while (isdigit(c = readChar()));
  return ans * f;
}

namespace TreeChain{
LL A[N];
LL s[N];
LL pre[N], nxt[N * 2], to[N * 2], cnt;
LL dep[N], node[N], pos[N], top[N], fa[N], siz[N], belong[N], cnt2, cnt3;

inline void addEdge(LL x, LL y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  to[pre[y] = cnt++] = x;
}

void dfs1(LL x) {
  dep[x] = dep[fa[x]] + 1;
  siz[x] = 1;
  s[x] = A[x];
  for (LL i = pre[x]; ~i; i = nxt[i])
    if (to[i] != fa[x]) {
      fa[to[i]] = x;
      dfs1(to[i]);
      siz[x] += siz[to[i]];
      s[x] += s[to[i]];
    }
}

void dfs2(LL x, bool n = false) {
  if (n) {
    ++cnt2;
    top[cnt2] = x;
  }
  node[pos[x] = cnt3++] = x;
  belong[x] = cnt2;
  if (siz[x] > 1) {
    LL l = 0;
    for (LL i = pre[x]; ~i; i = nxt[i])
      if (to[i] != fa[x] && siz[to[i]] > siz[l])
        l = to[i];
    dfs2(l);
    for (LL i = pre[x]; ~i; i = nxt[i])
      if (to[i] != fa[x] && to[i] != l)
        dfs2(to[i], true);
  }
}

inline void work() {
  memset(pre, -1, sizeof pre);
  for (LL i = 1; i < n; ++i)
    addEdge(readInt(), readInt());
  for (LL i = 1; i <= n; ++i)
    A[i] = readInt();
  dfs1(1);
  cnt3 = 1;
  dfs2(1, true);
}
};

namespace SegTree{
LL ss[N * 4], ss2[N * 4], addv[N * 4];
#define lch (o << 1)
#define rch (o << 1 | 1)

inline void maintain(LL o, LL l, LL r) {
  using TreeChain::s;
  using TreeChain::node;
  if (l == r) {
    ss[o] = addv[o] + s[node[l]];
    ss2[o] = ss[o] * ss[o];
  } else {
    ss[o] = ss[lch] + ss[rch] + addv[o] * (r - l + 1);
    ss2[o] = ss2[lch] + ss2[rch] +
      addv[o] * addv[o] * (r - l + 1) + 2 * addv[o] * (ss[lch] + ss[rch]);
  }
}

inline void pushdown(LL o, LL l, LL r) {
  using TreeChain::s;
  using TreeChain::node;
  if (l == r) s[node[l]] += addv[o];
  else {
    addv[lch] += addv[o];
    addv[rch] += addv[o];
  }
  addv[o] = 0;
}

void build(LL o, LL l, LL r) {
  if (l != r) {
    LL mid = (l + r) / 2;
    build(lch, l, mid);
    build(rch, mid + 1, r);
  }
  maintain(o, l, r);
}

void modify(LL o, LL l, LL r, LL L, LL R, LL add) {
  if (l > R || r < L) return;
  if (r <= R && l >= L)
    addv[o] += add;
  else {
    LL mid = (l + r) / 2;
    modify(lch, l, mid, L, R, add);
    modify(rch, mid + 1, r, L, R, add);
  }
  maintain(o, l, r);
}

void query(LL o, LL l, LL r, LL L, LL R, LL &ans2, LL &ans) {
  maintain(o, l, r);
  if (l > R || r < L) return;
  if (r <= R && l >= L) {
    ans2 += ss2[o];
    ans += ss[o];
  } else {
    LL mid = (l + r) / 2;
    pushdown(o, l, r);
    query(lch, l, mid, L, R, ans2, ans);
    query(rch, mid + 1, r, L, R, ans2, ans);
  }
}
};

using TreeChain::A;
LL sa = 0;
LL query(LL x) {
  using SegTree::query;
  using TreeChain::belong;
  using TreeChain::pos;
  LL ans = 0, ss = 0, tmp;
  query(1, 1, n, 1, n, ans, tmp);
  LL k = 0;
  while (belong[x] != belong[1]) {
    LL top = TreeChain::top[belong[x]];
    k += pos[x] - pos[top] + 1;
    query(1, 1, n, pos[top], pos[x], tmp, ss);
    x = TreeChain::fa[top];
  }
  k += pos[x] - pos[1];
  query(1, 1, n, pos[1] + 1, pos[x], tmp, ss);
  return ans + sa * (k * sa - 2 * ss);
}

void modify(LL x, LL y) {
  using SegTree::modify;
  using TreeChain::belong;
  using TreeChain::pos;
  y -= A[x];
  A[x] += y;
  sa += y;
  while (x) {
    LL top = TreeChain::top[belong[x]];
    modify(1, 1, n, pos[top], pos[x], y);
    x = TreeChain::fa[top];
  }
}

int main() {
  n = readInt();
  LL q = readInt();
  TreeChain::work();
  sa = TreeChain::s[1];
  SegTree::build(1, 1, n);
  while (q--) {
    if (readInt() == 1) {
      LL x = readInt();
      LL y = readInt();
      modify(x, y);
    } else {
      LL x = readInt();
      printf("%lld\n", query(x));
    }
  }
  return 0;
}

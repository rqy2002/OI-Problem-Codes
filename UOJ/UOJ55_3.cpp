/**************************************************************
 * Problem: UOJ55
 * Author: Rqy
 * Date: 2017 Dec 19
 * Algorithm: See UOJ55.cpp
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <set>
typedef std::set<int> SI;
typedef long long LL;
const int N = 100050;
const int NN = N * 100;

int pre[N], to[N * 2], nxt[N * 2], c[N * 2], cnt;
int dep[N], dep2[N], fa[N][17];

inline void addEdge(int x, int y, int cc) {
  nxt[cnt] = pre[x];
  c[cnt] = cc;
  to[pre[x] = cnt++] = y;
}

void addNode_(int x, int f, int cc) {
  if (f) {
    addEdge(x, f, cc);
    addEdge(f, x, cc);
  }
  dep[x] = dep[f] + 1;
  dep2[x] = dep2[f] + cc;
  fa[x][0] = f;
  for (int i = 1; i < 17; ++i)
    fa[x][i] = fa[fa[x][i - 1]][i - 1];
}

int LCA(int x, int y) {
  if (dep[x] > dep[y]) std::swap(x, y);
  for (int i = 16; ~i; --i)
    if (dep[fa[y][i]] >= dep[x])
      y = fa[y][i];
  for (int i = 16; ~i; --i)
    if (fa[y][i] != fa[x][i]) {
      y = fa[y][i];
      x = fa[x][i];
    }
  return x == y ? x : fa[x][0];
}

inline int dis(int x, int y) {
  return dep2[x] + dep2[y] - 2 * dep2[LCA(x, y)];
}

int pool[NN], top;
int lch[NN], rch[NN], val[NN], key[NN], count[NN];
int siz[NN];

inline void maintain(int o) { siz[o] = siz[lch[o]] + siz[rch[o]] + count[o]; }
inline void Zig(int &o) { //Rotate to right
  int l = lch[o];
  lch[o] = rch[l];
  maintain(rch[l] = o);
  maintain(o = l);
}
inline void Zag(int &o) { //Rotate to left
  int r = rch[o];
  rch[o] = lch[r];
  maintain(lch[r] = o);
  maintain(o = r);
}

void insert(int &o, int x) {
  if (!o) {
    o = pool[--top];
    lch[o] = rch[o] = 0;
    val[o] = x;
    siz[o] = count[o] = 1;
    key[o] = rand();
  } else if (val[o] > x) {
    insert(lch[o], x);
    if (key[lch[o]] > key[o]) Zig(o);
  } else if (val[o] < x) {
    insert(rch[o], x);
    if (key[rch[o]] > key[o]) Zag(o);
  } else
    ++count[o];
  maintain(o);
}

void removeTree(int &x) {
  if (!x) return;
  removeTree(lch[x]);
  removeTree(rch[x]);
  pool[top++] = x;
  x = 0;
}

int query(int o, int x) {
  if (!o) return 0;
  else if (val[o] > x) return query(lch[o], x);
  else return query(rch[o], x) + siz[lch[o]] + count[o];
}

int r[N];
int vis[N], viss[N * 2], time;
int fa2[N];
int tree[N], sonTree[N];
SI son[N];

void remove(int x) {
  removeTree(tree[x]);
  vis[x] = time;
  for (SI::iterator i = son[x].begin(); i != son[x].end(); ++i) {
    remove(*i);
    removeTree(sonTree[*i]);
  }
  son[x].clear();
}

int getCentre(int x, int fa, int siz, int &ct) {
  int res = 1;
  bool ok = true;
  for (int i = pre[x]; ~i; i = nxt[i]) {
    if (vis[to[i]] != time || viss[i] == time) continue;
    if (to[i] == fa) continue;
    int ss = getCentre(to[i], x, siz, ct);
    if (ss * 2 > siz) ok = false;
    res += ss;
  }
  if (res * 2 < siz) ok = false;
  if (ok) ct = x;
  return res;
}

inline void insertAll(int x, int fa, int dep, int &tr) {
  insert(tr, dep - r[x]);
  for (int i = pre[x]; ~i; i = nxt[i]) {
    if (vis[to[i]] != time || viss[i] == time) continue;
    if (to[i] == fa) continue;
    insertAll(to[i], x, dep + c[i], tr);
  }
}

int divide(int x) {
  getCentre(x, 0, getCentre(x, 0, 1000000000, x), x);
  insertAll(x, 0, 0, tree[x]);
  for (int i = pre[x]; ~i; i = nxt[i]) {
    if (vis[to[i]] != time || viss[i] == time) continue;
    int p = 0;
    viss[i] = viss[i ^ 1] = time;
    insertAll(to[i], x, c[i], p);
    int sonx = divide(to[i]);
    sonTree[sonx] = p;
    son[x].insert(sonx);
    fa2[sonx] = x;
  }
  return x;
}

void rebuild(int x) {
  int f = fa2[x];
  son[f].erase(x);
  int p = sonTree[x];
  sonTree[x] = 0;
  ++time;
  remove(x);
  x = divide(x);
  sonTree[x] = p;
  son[f].insert(x);
  fa2[x] = f;
}

int addNode(int x, int f, int cc, int rr) {
  r[x] = rr;
  addNode_(x, f, cc);
  int ans = 0;
  fa2[x] = f;
  son[f].insert(x);
  for (int i = x; i; i = fa2[i]) {
    if (fa2[i]) {
      int d = dis(x, fa2[i]);
      ans += query(tree[fa2[i]], rr - d);
      ans -= query(sonTree[i], rr - d);
      insert(sonTree[i], d - rr);
    }
    int d = dis(x, i);
    insert(tree[i], d - rr);
  }
  int rebuildx = 0;
  for (int i = x; fa2[i]; i = fa2[i])
    if (siz[tree[i]] > 0.88 * siz[tree[fa2[i]]])
      rebuildx = fa2[i];
  if (rebuildx) rebuild(rebuildx);
  return ans;
}

int main() {
  top = 0;
  do pool[top] = top; while (++top < NN);
  int n, a, c, r;
  scanf("%*d%d", &n);
  std::fill(pre + 1, pre + n + 1, -1);
  LL ans = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%d", &a, &c, &r);
    a ^= (ans % 1000000000);
    printf("%lld\n", ans += addNode(i, a, c, r));
  }
  return 0;
}

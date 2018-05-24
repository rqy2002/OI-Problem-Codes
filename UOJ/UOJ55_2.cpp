/**************************************************************
 * Problem: UOJ55
 * Author: Rqy
 * Date: 2017 Dec 19
 * Algorithm: See UOJ55.cpp
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <set>
typedef long long LL;
typedef std::set<int> SI;
const int N = 100050;
const int NN = N * 100;

int pre[N], nxt[N * 2], to[N * 2], c[N * 2], cnt = 0;
int dep[N], dep2[N];
int fa[N][17];

inline void addEdge(int x, int y, int cc) {
  c[cnt] = cc;
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
}

namespace Tree{
inline void addNode(int x, int f, int cc) {
  if (f) {
    addEdge(x, f, cc);
    addEdge(f, x, cc);
  }
  fa[x][0] = f;
  dep[x] = dep[f] + 1;
  dep2[x] = dep2[f] + cc;
  for (int i = 1; i < 17; ++i)
    fa[x][i] = fa[fa[x][i - 1]][i - 1];
}

int LCA(int x, int y) {
  if (dep[x] > dep[y]) std::swap(x, y);
  for (int i = 16; ~i; --i)
    if (dep[fa[y][i]] >= dep[x])
      y = fa[y][i];
  for (int i = 16; ~i; --i)
    if (fa[x][i] != fa[y][i]) {
      x = fa[x][i];
      y = fa[y][i];
    }
  return x == y ? x : fa[x][0];
}

int dis(int x, int y) {
  int l = LCA(x, y);
  return dep2[x] + dep2[y] - dep2[l] * 2;
}
};

int lch[NN], rch[NN], siz[NN], val[NN], count[NN], key[NN];
int pool[NN], top = 0;

int newNode(int v) {
  int o = pool[--top];
  lch[o] = rch[o] = 0;
  count[o] = siz[o] = 1;
  val[o] = v;
  key[o] = rand();
  return o;
}

inline void maintain(int x) {
  siz[x] = count[x] + siz[lch[x]] + siz[rch[x]];
}

inline void Zig(int &o) { //Rotate to right
  int t = lch[o];
  lch[o] = rch[t];
  rch[t] = o;
  maintain(o);
  maintain(t);
  o = t;
}

inline void Zag(int &o) { //Rotate to left
  int t = rch[o];
  rch[o] = lch[t];
  lch[t] = o;
  maintain(o);
  maintain(t);
  o = t;
}

void insert(int &o, int x) {
  if (!o)
    o = newNode(x);
  else if (val[o] == x)
    ++count[o];
  else if (val[o] < x) {
    insert(rch[o], x);
    if (key[rch[o]] > key[o])
      Zag(o);
  } else {
    insert(lch[o], x);
    if (key[lch[o]] > key[o])
      Zig(o);
  }
  maintain(o);
}

int query(int o, int x) {
  if (!o) return 0;
  else if (val[o] > x) return query(lch[o], x);
  else return siz[lch[o]] + count[o] + query(rch[o], x);
}

void removeTree(int &o) {
  if (lch[o]) removeTree(lch[o]);
  if (rch[o]) removeTree(rch[o]);
  pool[top++] = o;
  o = 0;
}

int r[N];
int vis[N], viss[N * 2], time;
int tree[N], sonTree[N];
int fa2[N];
SI son[N];

void remove(int x) {
  vis[x] = time;
  removeTree(tree[x]);
  for (SI::iterator i = son[x].begin(); i != son[x].end(); ++i) {
    removeTree(sonTree[*i]);
    remove(*i);
  }
  son[x].clear();
}

int getCenter(int x, int fa, int siz, int &center) {
  int res = 1;
  bool ok = true;
  for (int i = pre[x]; ~i; i = nxt[i]) {
    if (viss[i] == time || vis[to[i]] != time) continue;
    if (to[i] == fa) continue;
    int ss = getCenter(to[i], x, siz, center);
    if (ss * 2 > siz) ok = false;
    res += ss;
  }
  if (res * 2 < siz) ok = false;
  if (ok) center = x;
  return res;
}

void insertAll(int x, int fa, int dep, int &tree) {
  insert(tree, dep - r[x]);
  for (int i = pre[x]; ~i; i = nxt[i]) {
    if (viss[i] == time || vis[to[i]] != time) continue;
    if (to[i] == fa) continue;
    insertAll(to[i], x, dep + c[i], tree);
  }
}

int divide(int x) {
  getCenter(x, 0, getCenter(x, 0, 100000000, x), x);
  insertAll(x, 0, 0, tree[x]);
  for (int i = pre[x]; ~i; i = nxt[i]) {
    if (viss[i] == time || vis[to[i]] != time) continue;
    int p = 0;
    viss[i] = viss[i ^ 1] = time;
    insertAll(to[i], x, c[i], p);
    int tmp = divide(to[i]);
    sonTree[tmp] = p;
    fa2[tmp] = x;
    son[x].insert(tmp);
  }
  return x;
}

inline void rebuild(int x) {
  int f = fa2[x];
  int p = sonTree[x];
  sonTree[x] = 0;
  if (f) son[f].erase(x);
  ++time;
  remove(x);
  x = divide(x);
  if (f) son[f].insert(x);
  sonTree[x] = p;
  fa2[x] = f;
}

int addNode(int x, int f, int cc, int rr) {
  Tree::addNode(x, f, cc);
  r[x] = rr;

  fa2[x] = f;
  son[f].insert(x);
  int ans = 0;
  for (int i = x; i; i = fa2[i]) {
    if (fa2[i]) {
      int d = Tree::dis(x, fa2[i]);
      ans += query(tree[fa2[i]], rr - d);
      ans -= query(sonTree[i], rr - d);
      insert(sonTree[i], d - rr);
    }
    int d = Tree::dis(x, i);
    insert(tree[i], d - rr);
  }

  int rebuildx = 0;
  for (int i = x; fa2[i]; i = fa2[i])
    if (siz[tree[fa2[i]]] * 0.88 < siz[tree[i]])
      rebuildx = fa2[i];
  if (rebuildx) rebuild(rebuildx);

  return ans;
}

int main() {
  for (int i = 0; i < NN; ++i)
    pool[i] = i;
  top = NN;

  int n;
  scanf("%*d%d", &n);
  std::fill(pre + 1, pre + N, -1);

  LL lastans = 0;
  int a, c, r;
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%d", &a, &c, &r);
    a ^= (lastans % 1000000000);
    lastans += addNode(i, a, c, r);
    printf("%lld\n", lastans);
  }
  return 0;
}

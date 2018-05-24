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

int pre[N], nxt[N * 2], to[N * 2], c[N * 2], cnt;
int dep[N], dep2[N];

namespace Tree{
  int fa[N][17];

  inline void addEdge(int x, int y, int cc) {
    nxt[cnt] = pre[x];
    c[cnt] = cc;
    to[pre[x] = cnt++] = y;
  }

  void addNode(int x, int f, int cc) {
    if ((fa[x][0] = f)) {
      addEdge(x, f, cc);
      addEdge(f, x, cc);
    }
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

  inline int dis(int x, int y) {
    return dep2[x] + dep2[y] - dep2[LCA(x, y)] * 2;
  }
};

struct Treap{
  static Treap* pool[NN];
  static int top;
  Treap *lch, *rch;
  int val, size, count, key;
 
  void* operator new(size_t, int v) {
    Treap *res = pool[--top];
    res->lch = res->rch = NULL;
    res->val = v;
    res->size = res->count = 1;
    res->key = rand();
    return res;
  }

  void operator delete(void *p) {
    pool[top++] = (Treap*)p;
  }
  
  void maintain() {
    size = count;
    if (lch) size += lch->size;
    if (rch) size += rch->size;
  }

  friend void Zig(Treap* &o) { // rotate to right
    Treap *l = o->lch;
    o->lch = l->rch;
    (l->rch = o)->maintain();
    (o = l)->maintain();
  }

  friend void Zag(Treap* &o) { // rotate to left
    Treap *r = o->rch;
    o->rch = r->lch;
    (r->lch = o)->maintain();
    (o = r)->maintain();
  }

  friend void insert(Treap* &o, int x) {
    if (!o) o = new (x)Treap;
    else if (o->val > x) {
      insert(o->lch, x);
      if (o->lch->key > o->key)
        Zig(o);
    } else if (o->val < x) {
      insert(o->rch, x);
      if (o->rch->key > o->key)
        Zag(o);
    } else
      ++o->count;
    o->maintain();
  }

  friend void remove(Treap* &o) {
    if (!o) return;
    remove(o->lch);
    remove(o->rch);
    delete o; o = NULL;
  }

  friend int query(Treap* o, int x) {
    if (!o) return 0;
    if (o->val <= x)
      return o->count + (o->lch ? o->lch->size : 0) + query(o->rch, x);
    else
      return query(o->lch, x);
  }
};

Treap* Treap::pool[NN];
int Treap::top;
Treap ppool[NN];

int r[N];
int fa[N];
int vis[N], vise[N * 2], time;
Treap *tree[N], *sonTree[N];
SI son[N];

void remove(int x) {
  vis[x] = time;
  remove(tree[x]);
  for (SI::iterator i = son[x].begin(); i != son[x].end(); ++i) {
    remove(*i);
    remove(sonTree[*i]);
  }
  son[x].clear();
}

int getCenter(int x, int fa, int siz, int &ct) {
  int res = 1;
  bool ok = true;
  for (int i = pre[x]; ~i; i = nxt[i]) {
    if (vise[i] == time || vis[to[i]] != time) continue;
    if (to[i] == fa) continue;
    int ss = getCenter(to[i], x, siz, ct);
    if (ss * 2 > siz) ok = false;
    res += ss;
  }
  if (res * 2 < siz) ok = false;
  if (ok) ct = x;
  return res;
}

void insertAll(int x, int fa, int dep, Treap* &p) {
  insert(p, dep - r[x]);
  for (int i = pre[x]; ~i; i = nxt[i]) {
    if (vise[i] == time || vis[to[i]] != time) continue;
    if (to[i] == fa) continue;
    insertAll(to[i], x, dep + c[i], p);
  }
}

int divide(int x) {
  getCenter(x, 0, getCenter(x, 0, 100000000, x), x);
  insertAll(x, 0, 0, tree[x]);
  for (int i = pre[x]; ~i; i = nxt[i]) {
    if (vise[i] == time || vis[to[i]] != time) continue;
    Treap *p = NULL;
    vise[i] = vise[i ^ 1] = time;
    insertAll(to[i], 0, c[i], p);
    int ss = divide(to[i]);
    fa[ss] = x;
    son[x].insert(ss);
    sonTree[ss] = p;
  }
  return x;
}

void rebuild(int x) {
  ++time;
  int f = fa[x];
  son[f].erase(x);
  Treap *p = sonTree[x];
  sonTree[x] = NULL;
  remove(x);
  x = divide(x);
  sonTree[x] = p;
  son[f].insert(x);
  fa[x] = f;
}

int addNode(int x, int f, int cc, int rr) {
  Tree::addNode(x, f, cc);
  son[fa[x] = f].insert(x);
  r[x] = rr;

  int ans = 0;
  for (int i = x; i; i = fa[i]) {
    if (fa[i]) {
      int d = Tree::dis(x, fa[i]);
      ans += query(tree[fa[i]], rr - d);
      ans -= query(sonTree[i], rr - d);
      insert(sonTree[i], d - rr);
    }
    int d = Tree::dis(x, i);
    insert(tree[i], d - rr);
  }

  int re = 0;
  for (int i = x; fa[i]; i = fa[i])
    if (tree[i]->size > tree[fa[i]]->size * 0.88)
      re = fa[i];
  if (re) rebuild(re);

  return ans;
}

int main() {
  for (int i = 0; i < NN; ++i)
    Treap::pool[Treap::top++] = &ppool[i];
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


/**************************************************************
 * Problem: BZOJ3435
 * Author: Rqy
 * Date: 2017 Dec 18
 * Algorithm: 倍增LCA+动态点分治+替罪羊树+treap(+垃圾回收)
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <set>
typedef long long LL;
const int N = 100050;
int pre[N], to[N * 2], nxt[N * 2], c[N * 2], cnt = 0;
int r[N];
inline void add_edge(int x, int y, int v) {
  nxt[cnt] = pre[x];
  c[cnt] = v;
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  c[cnt] = v;
  to[pre[y] = cnt++] = x;
}
namespace Tree{
  int dep[N], dep2[N], fa[N][17];
  void insert(int x, int c, int f) {
    add_edge(x, f, c);
    dep[x] = dep[fa[x][0] = f] + 1;
    dep2[x] = dep2[f] + c;
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
    return dep2[x] + dep2[y] - 2 * dep2[l];
  }
};
struct Treap;
typedef Treap* PTreap;
struct Treap{
  static std::stack<PTreap> bin;
  PTreap lch, rch;
  int val, key, cnt, siz;
  void* operator new(size_t, int v) {
    Treap *res;
    res = bin.top();
    bin.pop();
    res->val = v; res->key = rand();
    res->cnt = 1; res->siz = 1;
    res->lch = res->rch = NULL;
    return res;
  }
  void operator delete(void *t) {
    bin.push((PTreap)t);
  }
  void update() {
    siz = cnt;
    if (lch != NULL) siz += lch->siz;
    if (rch != NULL) siz += rch->siz;
  }
  friend void Zig(PTreap &t) { //右旋
    PTreap l = t->lch;
    t->lch = l->rch;
    l->rch = t;
    t->update();
    l->update();
    t = l;
  }
  friend void Zag(PTreap &t) { //左旋
    Treap *r = t->rch;
    t->rch = r->lch;
    r->lch = t;
    t->update();
    r->update();
    t = r;
  }
  friend int query(PTreap o, int x) {
    if (o == NULL) return 0;
    if (o->val > x) return query(o->lch, x);
    else return query(o->rch, x) + (o->lch == NULL ? 0 : o->lch->siz) + o->cnt;
  }
  friend void insert(PTreap &o, int x) {
    if (o == NULL)
      o = new (x)Treap;
    else if (o->val == x)
      ++o->cnt;
    else if (o->val > x) {
      insert(o->lch, x);
      if (o->lch->key > o->key)
        Zig(o);
    } else {
      insert(o->rch, x);
      if (o->rch->key > o->key)
        Zag(o);
    }
    o->update();
  }
  friend void remove(PTreap &x) {
    if (x == NULL) return;
    remove(x->lch);
    remove(x->rch);
    delete x; x = NULL;
  }
};
std::stack<PTreap> Treap::bin;
namespace Dynamic_TreeDivision{
  PTreap tree[N], sonTree[N];
  int time, vise[N * 2];
  int fa[N], vis[N];
  std::set<int> son[N];
  void remove(int x) {
    vis[x] = time;
    for (std::set<int>::iterator i = son[x].begin(); i != son[x].end(); ++i) {
      remove(*i);
      remove(sonTree[*i]);
    }
    son[x].clear();
    remove(tree[x]);
  }
  int getCentre(int x, int f, int siz, int &ct) {
    int res = 1;
    bool ok = true;
    for (int i = pre[x]; ~i; i = nxt[i]) {
      if (vise[i] == time) continue;
      if (to[i] == f) continue;
      if (vis[to[i]] != time) continue;
      int ss = getCentre(to[i], x, siz, ct);
      if (ss > siz / 2) ok = false;
      res += ss;
    }
    if (siz - res > siz / 2) ok = false;
    if (ok) ct = x;
    return res;
  }
  void insertAll(int x, int f, int dep, PTreap &p) {
    insert(p, dep - r[x]);
    for (int i = pre[x]; ~i; i = nxt[i]) {
      if (vise[i] == time) continue;
      if (to[i] == f) continue;
      if (vis[to[i]] != time) continue;
      insertAll(to[i], x, dep + c[i], p);
    }
  }
  int divide(int x) {
    getCentre(x, 0, getCentre(x, 0, 1000000000, x), x);
    insertAll(x, 0, 0, tree[x]);
    for (int i = pre[x]; ~i; i = nxt[i]) {
      if (vise[i] == time) continue;
      if (vis[to[i]] != time) continue;
      vise[i] = vise[i ^ 1] = time;
      PTreap p = NULL;
      insertAll(to[i], 0, c[i], p);
      int s = divide(to[i]);
      fa[s] = x;
      son[x].insert(s);
      sonTree[s] = p;
    }
    return x;
  }
  void rebuild(int x) {
    ++time;
    remove(x);
    int ff = fa[x];
    PTreap p = sonTree[x];
    sonTree[x] = NULL;
    if (ff != 0) son[ff].erase(x);
    x = divide(x);
    fa[x] = ff;
    sonTree[x] = p;
    if (ff != 0) son[ff].insert(x);
  }
  LL insert(int x, int f) {
    LL ans = 0;
    son[f].insert(x);
    fa[x] = f;
    for (int i = x; i; i = fa[i]) {
      if (fa[i] != 0) {
        int d = Tree::dis(fa[i], x);
        ans += query(tree[fa[i]], r[x] - d);
        ans -= query(sonTree[i], r[x] - d);
        insert(sonTree[i], d - r[x]);
      }
      int d = Tree::dis(i, x);
      insert(tree[i], d - r[x]);
    }
    int rebuildx = 0;
    for (int i = x; fa[i]; i = fa[i])
      if (tree[i]->siz > tree[fa[i]]->siz * 0.88)
        rebuildx = fa[i];
    if (rebuildx) rebuild(rebuildx);
    return ans;
  }
};
Treap node[N * 100];
int main() {
  for (int i = 0; i < N * 100; ++i)
    Treap::bin.push(node + i);
  int n, a, cc, v;
  scanf("%*d%d", &n);
  LL lastans = 0;
  pre[0] = -1;
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%d", &a, &cc, &v);
    r[i] = v;
    a ^= lastans % 1000000000;
    pre[i] = -1;
    Tree::insert(i, cc, a);
    lastans += Dynamic_TreeDivision::insert(i, a);
    printf("%lld\n", lastans);
  }
  return 0;
}

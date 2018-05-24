/**************************************************************
 * Problem: UOJ55
 * Author: Rqy
 * Date: 2017 Dec 20
 * Algorithm: See UOJ55.cpp
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <set>
typedef long long LL;
typedef std::set<int> SI;

const int N = 100050;
const int NN = N * 100;

int pre[N], to[N * 2], nxt[N * 2], c[N * 2], cnt;
int dep[N], dep2[N], fa[N][17];

inline void addEdge(int x, int y, int cc) {
  c[cnt] = cc;
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
}

void addNode_(int x, int f, int cc) {
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

inline int dis(int x, int y) {
  return dep2[x] + dep2[y] - 2 * dep2[LCA(x, y)];
}

int siz[NN], ch[NN][2], val[NN], count[NN], key[NN];
int pool[NN], top;

inline int newNode(int x) {
  int o = pool[--top];
  ch[o][0] = ch[o][1] = 0;
  val[o] = x;
  count[o] = siz[o] = 1;
  key[o] = rand();
  return o;
}

inline void maintain(int o) {
  siz[o] = siz[ch[o][0]] + siz[ch[o][1]] + count[o];
}

inline void Zig(int &o, int d) { //d = 0: to right
  int l = ch[o][d];
  ch[o][d] = ch[l][d ^ 1];
  maintain(ch[l][d ^ 1] = o);
  maintain(o = l);
}

void removeTree(int &o) {
  if (!o) return;
  removeTree(ch[o][0]);
  removeTree(ch[o][1]);
  pool[top++] = o; o = 0;
}

void insert(int &o, int x) {
  if (!o) o = newNode(x);
  else if (val[o] == x) ++count[o];
  else {
    int d = (val[o] < x);
    insert(ch[o][d], x);
    if (key[ch[o][d]] > key[o]) Zig(o, d);
  }
  maintain(o);
}

int query(int o, int x) {
  if (!o) return 0;
  if (val[o] > x) return query(ch[o][0], x);
  else return count[o] + siz[ch[o][0]] + query(ch[o][1], x);
}

int r[N];
int vis[N], vise[N * 2], time;
int fa2[N], tree[N], sonTree[N];
SI son[N];

void remove(int x) {
  vis[x] = time;
  removeTree(tree[x]);
  for (SI::iterator i = son[x].begin(); i != son[x].end(); ++i) {
    remove(*i);
    removeTree(sonTree[*i]);
  }
  son[x].clear();
}

int getCenter(int x, int fa, int size, int &ct) {
  int res = 1;
  bool ok = true;
  for (int i = pre[x]; ~i; i = nxt[i]) {
    if (vis[to[i]] != time || vise[i] == time) continue;
    if (to[i] == fa) continue;
    int ss = getCenter(to[i], x, size, ct);
    if (ss * 2 > size) ok = false;
    res += ss;
  }
  if (res * 2 < size) ok = false;
  if (ok) ct = x;
  return res;
}

void insertAll(int x, int fa, int dep, int &Tree) {
  insert(Tree, dep - r[x]);
  for (int i = pre[x]; ~i; i = nxt[i]) {
    if (vis[to[i]] != time || vise[i] == time) continue;
    if (to[i] == fa) continue;
    insertAll(to[i], x, dep + c[i], Tree);
  }
}

int divide(int x) {
  getCenter(x, 0, getCenter(x, 0, 100000000, x), x);
  insertAll(x, 0, 0, tree[x]);
  for (int i = pre[x]; ~i; i = nxt[i]) {
    if (vis[to[i]] != time || vise[i] == time) continue;
    int p = 0;
    vise[i] = vise[i ^ 1] = time;
    insertAll(to[i], x, c[i], p);
    int ss = divide(to[i]);
    fa2[ss] = x;
    son[x].insert(ss);
    sonTree[ss] = p;
  }
  return x;
}

void rebuild(int x) {
  int f = fa2[x];
  son[f].erase(x);
  ++time;
  int p = sonTree[x];
  sonTree[x] = 0;
  remove(x);
  x = divide(x);
  sonTree[x] = p;
  son[f].insert(x);
  fa2[x] = f;
}

int addNode(int x, int f, int cc, int rr) {
  fa2[x] = f;
  addNode_(x, f, cc);
  r[x] = rr;
  son[f].insert(x);

  int ans = 0;
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

  int re = 0;
  for (int i = x; fa2[i]; i = fa2[i])
    if (siz[tree[i]] > siz[tree[fa2[i]]] * 0.88)
      re = fa2[fa2[i]] ? fa2[fa2[i]] : fa2[i];
  if (re) rebuild(re);

  return ans;
}

int main() {
  for (int i = 0; i < NN; ++i)
    pool[top++] = i;
  int n, a, c, r;
  LL ans = 0;
  scanf("%*d%d", &n);
  std::fill(pre + 1, pre + n + 1, -1);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%d", &a, &c, &r);
    a ^= (ans % 1000000000);
    printf("%lld\n", ans += addNode(i, a, c, r));
  }
  return 0;
}

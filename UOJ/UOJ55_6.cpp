#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>

const int N = 100050;
typedef long long LL;
typedef std::set<int> SI;

/* Treap */

const int NN = 5000050;
int ch[NN][2], val[NN], key[NN], siz[NN], cnt[NN], st[NN], top;

inline void upd(int o) { siz[o] = siz[ch[o][0]] + siz[ch[o][1]] + cnt[o]; }

inline void rotate(int &o, int d) {
  int c = ch[o][d];
  ch[o][d] = ch[c][d ^ 1];
  upd(ch[c][d ^ 1] = o);
  upd(o = c);
}

void rmTreap(int &x) {
  if (!x) return;
  rmTreap(ch[x][0]);
  rmTreap(ch[x][1]);
  st[top++] = x;
  x = 0;
}

int newNode(int x) {
  int nn = st[--top];
  val[nn] = x;
  cnt[nn] = siz[nn] = 1;
  key[nn] = rand();
  ch[nn][0] = ch[nn][1] = 0;
  return nn;
}

void insert(int &o, int x) {
  if (!o) o = newNode(x);
  else if (x == val[o]) ++cnt[o];
  else {
    int d = (x > val[o]);
    insert(ch[o][d], x);
    if (key[ch[o][d]] > key[o])
      rotate(o, d);
  }
  upd(o);
}

int countLT(int o, int x) {
  if (!o) return 0;
  return val[o] > x
      ? countLT(ch[o][0], x)
      : siz[ch[o][0]] + cnt[o] + countLT(ch[o][1], x);
}

/* Tree */

int pre[N], nxt[N * 2], to[N * 2], cost[N * 2], cnt_;
int treefa[N][20], dep[N], dep2[N];

inline void addEdge(int x, int y, int c) {
  nxt[cnt_] = pre[x];
  cost[cnt_] = c;
  to[pre[x] = cnt_++] = y;
}

void addNode1(int x, int f, int c) {
  pre[x] = -1;
  treefa[x][0] = f;
  for (int i = 0; treefa[x][i]; ++i)
    treefa[x][i + 1] = treefa[treefa[x][i]][i];
  addEdge(x, f, c);
  addEdge(f, x, c);
  dep[x] = dep[f] + 1;
  dep2[x] = dep2[f] + c;
}

int LCA(int x, int y) {
  if (dep[x] < dep[y]) std::swap(x, y);
  for (int i = 19; ~i; --i)
    if (dep[treefa[x][i]] >= dep[y])
      x = treefa[x][i];
  for (int i = 19; ~i; --i)
    if (treefa[x][i] != treefa[y][i]) {
      x = treefa[x][i];
      y = treefa[y][i];
    }
  return x == y ? x : treefa[x][0];
}

inline int dis(int x, int y) {
  return dep2[x] + dep2[y] - 2 * dep2[LCA(x, y)];
}

/* Tree Division */

int fa[N], tree[N], sonTree[N], R[N];
int sizt[N], vis[N], visE[N * 2], tim;
SI son[N];
const double alpha = 0.88;

void clear(int x) {
  vis[x] = tim;
  rmTreap(tree[x]);
  for (SI::iterator i = son[x].begin(); i != son[x].end(); ++i) {
    rmTreap(sonTree[*i]);
    clear(*i);
  }
  son[x].clear();
}

int getSiz(int x, int f) {
  sizt[x] = 1;
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != f && vis[to[i]] == tim && visE[i] < tim)
      sizt[x] += getSiz(to[i], x);
  return sizt[x];
}

void getCenter(int x, int f, int S, int &c) {
  int maxv = S - sizt[x];
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != f && vis[to[i]] == tim && visE[i] < tim)
      maxv = std::max(maxv, siz[to[i]]);
  if (maxv <= S / 2)
    c = x;
}

void insertTo(int x, int f, int d, int &treap) {
  insert(treap, d - R[x]);
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != f && vis[to[i]] == tim && visE[i] < tim)
      insertTo(to[i], x, d + cost[i], treap);
}

int divide(int x) {
  getCenter(x, 0, getSiz(x, 0), x);
  insertTo(x, 0, 0, tree[x]);
  for (int i = pre[x]; ~i; i = nxt[i])
    if (vis[to[i]] == tim && visE[i] < tim) {
      visE[i] = visE[i ^ 1] = tim;
      int p = 0;
      insertTo(to[i], 0, cost[i], p);
      int s = divide(to[i]);
      sonTree[s] = p;
      fa[s] = x;
      son[x].insert(s);
    }
  return x;
}

inline void rebuild(int x) {
  clear(x);
  int p = sonTree[x];
  sonTree[x] = 0;
  int f = fa[x];
  son[f].erase(x);
  x = divide(x);
  son[f].insert(x);
  fa[x] = f;
  sonTree[x] = p;
}

LL ans;
void addNode(int x, int f, int c, int r) {
  addNode1(x, f, c);
  son[f].insert(x);
  fa[x] = f;
  R[x] = r;
  for (int i = x; i; i = fa[i]) {
    if (fa[i]) {
      int d = dis(fa[i], x);
      ans += countLT(tree[fa[i]], r - d);
      ans -= countLT(sonTree[i], r - d);
      insert(sonTree[i], d - r);
    }
    int d = dis(i, x);
    insert(tree[i], d - r);
  }
  int re = 0;
  for (int i = x; fa[i]; i = fa[i])
    if (siz[tree[i]] >= siz[tree[fa[i]]] * alpha)
      re = fa[i];
  if (re) rebuild(re);
}

int main() {
  top = 0;
  for (int i = 1; i < NN; ++i)
    st[top++] = i;
  int n;
  scanf("%*d%d", &n);
  ans = 0;
  int a, r, c;
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%d", &a, &c, &r);
    a ^= (ans % 1000000000);
    addNode(i, a, c, r);
    printf("%lld\n", ans);
  }
  return 0;
}

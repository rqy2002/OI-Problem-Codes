#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <set>

const int N = 100050;

namespace Treap{
  const int NN = N * 100;
  int ch[NN][2], key[NN], val[NN], cnt[NN], siz[NN];
  int top, pool[NN];

  inline void Init() {
    top = 0;
    for (int i = 1; i < NN; ++i)
      pool[top++] = i;
  }

  inline int NewNode(int v) {
    int o = pool[--top];
    ch[o][0] = ch[o][1] = 0;
    key[o] = rand();
    val[o] = v;
    cnt[o] = siz[o] = 1;
    return o;
  }

  inline void upd(int o) {
    siz[o] = siz[ch[o][0]] + siz[ch[o][1]] + cnt[o];
  }

  inline void Rotate(int &o, int d) {
    int x = ch[o][d];
    ch[o][d] = ch[x][d ^ 1];
    upd(ch[x][d ^ 1] = o);
    upd(o = x);
  }

  void Insert(int &o, int v) {
    if (o == 0) {
      o = NewNode(v);
    } else {
      if (val[o] == v) {
        ++cnt[o];
      } else {
        int d = v > val[o];
        Insert(ch[o][d], v);
        if (key[ch[o][d]] > key[o]) Rotate(o, d);
      }
      upd(o);
    }
  }

  void Delete(int &o) {
    if (o == 0) return;
    Delete(ch[o][0]);
    Delete(ch[o][1]);
    pool[top++] = o;
    o = 0;
  }

  int Query(int o, int x) {
    // the number of values in `o` which is not greater than `x`
    if (o == 0) return 0;
    else if (val[o] > x) return Query(ch[o][0], x);
    else return Query(ch[o][1], x) + siz[ch[o][0]] + cnt[o];
  }
};

int fa[N], r[N], siz[N];
int fa2[N][20], dep[N], dep2[N];
int pre[N], nxt[N * 2], to[N * 2], cc[N * 2], cnt;
int treap[N], sonTreap[N];
int visNode[N], visEdge[N * 2], cur;
std::set<int> son[N];

inline void AddEdge(int x, int y, int c) {
  nxt[cnt] = pre[x];
  cc[cnt] = c;
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  cc[cnt] = c;
  to[pre[y] = cnt++] = x;
}

int GetSize(int x, int f) {
  siz[x] = 1;
  for (int i = pre[x]; i != -1; i = nxt[i])
    if (to[i] != f && visNode[to[i]] == cur && visEdge[i] != cur)
      siz[x] += GetSize(to[i], x);
  return siz[x];
}

int GetCenter(int x, int f, int S) {
  for (int i = pre[x]; i != -1; i = nxt[i])
    if (to[i] != f && visNode[to[i]] == cur && visEdge[i] != cur
        && siz[to[i]] * 2 >= S)
      return GetCenter(to[i], x, S);
  return x;
}

void AddToTreap(int x, int f, int d, int &tr) {
  Treap::Insert(tr, d - r[x]);
  for (int i = pre[x]; i != -1; i = nxt[i])
    if (to[i] != f && visNode[to[i]] == cur && visEdge[i] != cur)
      AddToTreap(to[i], x, d + cc[i], tr);
}

int Divide(int x) {
  x = GetCenter(x, 0, GetSize(x, 0));
  AddToTreap(x, 0, 0, treap[x]);
  for (int i = pre[x]; i != -1; i = nxt[i])
    if (visNode[to[i]] == cur && visEdge[i] != cur) {
      int p = 0;
      AddToTreap(to[i], x, cc[i], p);
      visEdge[i] = visEdge[i ^ 1] = cur;
      int s = Divide(to[i]);
      fa[s] = x;
      son[x].insert(s);
      sonTreap[s] = p;
    }
  return x;
}

void Destruct(int x) {
  visNode[x] = cur;
  Treap::Delete(treap[x]);
  for (std::set<int>::iterator it = son[x].begin(); it != son[x].end(); ++it) {
    Treap::Delete(sonTreap[*it]);
    Destruct(*it);
  }
  son[x].clear();
}

void Rebuild(int x) {
  ++cur;
  int f = fa[x];
  son[f].erase(x);
  int p = sonTreap[x];
  Destruct(x);
  x = Divide(x);
  sonTreap[x] = p;
  son[f].insert(x);
  fa[x] = f;
}

int LCA(int x, int y) {
  if (dep[x] < dep[y]) std::swap(x, y);
  for (int t = 19; t >= 0; --t)
    if (dep[fa2[x][t]] >= dep[y])
      x = fa2[x][t];
  if (x == y) return x;
  for (int t = 19; t >= 0; --t)
    if (fa2[x][t] != fa2[y][t]) {
      x = fa2[x][t];
      y = fa2[y][t];
    }
  return fa2[x][0];
}

inline int Dist(int x, int y) {
  return dep2[x] + dep2[y] - 2 * dep2[LCA(x, y)];
}

void InitLCA(int x, int f, int c) {
  AddEdge(x, f, c);
  fa2[x][0] = f;
  for (int i = 0; fa2[x][i] != 0; ++i)
    fa2[x][i + 1] = fa2[fa2[x][i]][i];
  dep[x] = dep[f] + 1;
  dep2[x] = dep2[f] + c;
}

int AddNode(int x, int f, int c, int r) {
  using Treap::Insert;
  using Treap::Query;
  InitLCA(x, f, c);
  fa[x] = f;
  ::r[x] = r;
  son[f].insert(x);

  int ans = 0;
  for (int i = x; i != 0; i = fa[i]) {
    if (fa[i] != 0) {
      int d = Dist(x, fa[i]);
      ans += Query(treap[fa[i]], r - d) - Query(sonTreap[i], r - d);
      Insert(sonTreap[i], d - r);
    }
    int d = Dist(x, i);
    Insert(treap[i], d - r);
  }

  int _tmp = 0;
  for (int i = x; fa[i] != 0; i = fa[i])
    if (Treap::siz[treap[i]] > Treap::siz[treap[fa[i]]] * 0.8)
      _tmp = fa[i];
  if (_tmp != 0) Rebuild(_tmp);

  return ans;
}

int main() {
  int n;
  scanf("%*d%d", &n);
  memset(pre, -1, sizeof pre);
  Treap::Init();
  long long ans = 0;
  for (int i = 1, f, c, r; i <= n; ++i) {
    scanf("%d%d%d", &f, &c, &r);
    f = (f ^ ans) % 1000000000;
    printf("%lld\n", ans += AddNode(i, f, c, r));
  }
  return 0;
}

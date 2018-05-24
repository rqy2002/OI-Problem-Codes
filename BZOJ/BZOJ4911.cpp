#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 30050;
const int M = 128;
const int mod = 10007;

int n, m;
int inv[mod];
int count[M];

struct Int{
  int a, p; // a * mod^p
  Int(int t = 0) : a(t == 0 ? 1 : t), p(t == 0) {}
  Int(int a, int p) : a(a), p(p) {}
  inline operator int() const { return p == 0 ? a : 0; }
  Int operator+(int x) const {
    if ((x %= mod) != 0)
      return Int(p > 0 ? x : (a + x) % mod, 0);
    else
      return *this;
  }
  Int &operator*=(int x) {
    if ((x %= mod) == 0) ++p;
    else (a *= x) %= mod;
    return *this;
  }
  Int &operator/=(int x) {
    if ((x %= mod) == 0) --p;
    else (a *= inv[(x + mod) % mod]) %= mod;
    return *this;
  }
};

Int H[N][M];
int F[N][M];

struct Msg{
  int sum[M], suf[M], pre[M], mul[M];
  Msg() { Init(); }
  Msg(Int H[M]) {
    memset(sum, 0, sizeof sum);
    memset(suf, 0, sizeof suf);
    memset(pre, 0, sizeof pre);
    memset(mul, 0, sizeof mul);
    for (int i = 0; i < m; ++i)
      sum[i] = suf[i] = pre[i] = mul[i] = H[i];
  }
  void Init() {
    memset(sum, 0, sizeof sum);
    memset(suf, 0, sizeof suf);
    memset(pre, 0, sizeof pre);
    for (int i = 0; i < m; ++i)
      mul[i] = 1;
  }
  friend Msg operator*(const Msg &l, const Msg &r) {
    Msg ans;
    for (int i = 0; i < m; ++i) {
      ans.sum[i] = (l.sum[i] + r.sum[i] + l.suf[i] * r.pre[i]) % mod;
      ans.pre[i] = (l.pre[i] + l.mul[i] * r.pre[i]) % mod;
      ans.suf[i] = (r.suf[i] + r.mul[i] * l.suf[i]) % mod;
      ans.mul[i] = l.mul[i] * r.mul[i] % mod;
    }
    return ans;
  }
}msgv[N * 4], tmp;

int node[N];

void upd(int o, int l, int r) {
  if (l == r)
    msgv[o] = Msg(H[node[l]]);
  else
    msgv[o] = msgv[o << 1] * msgv[o << 1 | 1];
}

void Build(int o, int l, int r) {
  if (l != r) {
    int mid = (l + r) >> 1;
    Build(o << 1, l, mid);
    Build(o << 1 | 1, mid + 1, r);
  }
  upd(o, l, r);
}

void Query(int o, int l, int r, int L, int R) {
  if (R < l || r < L) return;
  if (L <= l && r <= R) return void(tmp = tmp * msgv[o]);
  int mid = (l + r) >> 1;
  Query(o << 1, l, mid, L, R);
  Query(o << 1 | 1, mid + 1, r, L, R);
}

void Modify(int o, int l, int r, int x) {
  if (r < x || l > x) return;
  if (l != r) {
    int mid = (l + r) >> 1;
    Modify(o << 1, l, mid, x);
    Modify(o << 1 | 1, mid + 1, r, x);
  }
  upd(o, l, r);
}

int siz[N], fa[N], pos[N], top[N], bottom[N], son[N];
int pre[N], to[N * 2], nxt[N * 2], val[N];

inline void addEdge(int x, int y) {
  static int cnt = 0;
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  to[pre[y] = cnt++] = x;
}

int dfs0(int x, int f) {
  fa[x] = f;
  son[x] = 0;
  siz[x] = 1;
  for (int i = pre[x]; i != -1; i = nxt[i])
    if (to[i] != f) {
      siz[x] += dfs0(to[i], x);
      if (siz[to[i]] > siz[son[x]]) son[x] = to[i];
    }
  return siz[x];
}

int Ans[M];

int dfs1(int x, int tp) {
  static int cnt = 0;
  node[pos[x] = ++cnt] = x;
  top[x] = tp;
  if (son[x] != 0) bottom[x] = dfs1(son[x], tp);
  else bottom[x] = x;

  for (int i = 0; i < m; ++i) H[x][i] = 1;

  for (int i = pre[x]; i != -1; i = nxt[i])
    if (to[i] != fa[x] && to[i] != son[x]) {
      dfs1(to[i], to[i]);
      for (int j = 0; j < m; ++j)
        H[x][j] *= 1 + F[to[i]][j];
    }

  for (int i = 0; i < m; ++i)
    if (count[i & val[x]] & 1)
      H[x][i] *= -1;

  for (int i = 0; i < m; ++i) F[x][i] = H[x][i];
  if (son[x])
    for (int i = 0; i < m; ++i)
      (F[x][i] *= 1 + F[son[x]][i]) %= mod;
  for (int i = 0; i < m; ++i)
    (Ans[i] += F[x][i]) %= mod;
  
  return bottom[x];
}

void Cut(int x) {
  if (x == 0) return;
  Modify(1, 1, n, pos[x]);
  int y = top[x];
  Cut(fa[y]);
  tmp.Init();
  Query(1, 1, n, pos[y], pos[bottom[y]]);
  for (int i = 0; i < m; ++i) (Ans[i] -= tmp.sum[i]) %= mod;
  for (int i = 0; i < m; ++i) H[fa[y]][i] /= 1 + tmp.pre[i];
}

void Link(int x) {
  if (x == 0) return;
  Modify(1, 1, n, pos[x]);
  int y = top[x];
  tmp.Init();
  Query(1, 1, n, pos[y], pos[bottom[y]]);
  for (int i = 0; i < m; ++i) (Ans[i] += tmp.sum[i]) %= mod;
  for (int i = 0; i < m; ++i) H[fa[y]][i] *= 1 + tmp.pre[i];
  Link(fa[y]);
}

void Modify(int x, int v) {
  Cut(x);
  
  for (int i = 0; i < m; ++i)
    if (count[i & val[x]] & 1)
      H[x][i] *= -1;

  val[x] = v;

  for (int i = 0; i < m; ++i)
    if (count[i & val[x]] & 1)
      H[x][i] *= -1;

  Link(x);
}

char s[100];

int main() {
  scanf("%d%d", &n, &m);

  for (int i = 1; i < m; ++i)
    count[i] = count[i & (i - 1)] + 1;
  inv[1] = 1;
  for (int i = 2; i < mod; ++i)
    inv[i] = -(mod / i) * inv[mod % i] % mod;

  for (int i = 1; i <= n; ++i)
    scanf("%d", &val[i]);
  memset(pre, -1, sizeof pre);
  for (int i = 1, x, y; i < n; ++i) {
    scanf("%d%d", &x, &y);
    addEdge(x, y);
  }

  dfs0(1, 0);
  dfs1(1, 1);
  Build(1, 1, n);

  int q;
  scanf("%d", &q);
  while (q--) {
    int x;
    scanf("%s%d", s, &x);
    if (*s == 'C') {
      int y;
      scanf("%d", &y);
      Modify(x, y);
    } else {
      int ans = 0;
      for (int i = 0; i < m; ++i)
        (ans += (count[i & x] & 1 ? -1 : 1) * Ans[i]) %= mod;
      printf("%d\n", (ans * inv[m] % mod + mod) % mod);
    }
  }

  return 0;
}

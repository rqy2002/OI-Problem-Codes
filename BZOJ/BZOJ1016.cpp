/**************************************************************
 * Problem: BZOJ1016
 * Author: Rqy
 * Date: 2018 Feb 22
 * Algorithm: MST, Matrix-Tree
**************************************************************/
#include <algorithm>
#include <cstdio>
const int mod = 31011;
const int mod1 = 3;
const int mod2 = 10337;
const int g1 = 20674;
const int g2 = 10338;
const int N = 105;
const int M = 1005;
int pre[N], nxt[M * 2], to[M * 2], c[M * 2], cnt = 1;
int n, m, fa[N];
int Find(int x) { return fa[x] ? fa[x] = Find(fa[x]) : x; }
int pow_mod(int a, int b, int p) {
  int ans = 1;
  for (; b; b >>= 1, a = a * a % p)
    if (b & 1) ans = ans * a % p;
  return ans;
}
inline int inv(int a, int p) { return pow_mod(a, p - 2, p); }
struct Edge{
  int a, b, v;
  bool operator<(const Edge &e)const{
    return v < e.v;
  }
  void addEdge() {
    a = Find(a); b = Find(b);
    nxt[cnt] = pre[a];
    c[cnt] = v;
    to[pre[a] = cnt++] = b;
    nxt[cnt] = pre[b];
    c[cnt] = v;
    to[pre[b] = cnt++] = a;
  }
}e[M];
int A[N][N], num, B[N][N], pos[N];
void dfs(int x, int cc, int f) {
  if (x != f) fa[x] = f;
  pos[x] = num++;
  for (int i = 0; i <= pos[x]; ++i)
    A[i][pos[x]] = A[pos[x]][i] = 0;
  for (int i = pre[x]; c[i] == cc; i = nxt[i]) {
    int u = to[i];
    if (!~pos[u]) dfs(u, cc, f);
    --A[pos[x]][pos[u]];
    ++A[pos[x]][pos[x]];
  }
}
int solve(int A[N][N], int n, int p) {
  --n;
  int f = 1;
  for (int i = 0; i < n; ++i) {
    int j = i;
    while (!(A[i][j] % p) && j < n) ++j;
    if (j >= n) return 0;
    if (j != i) {
      f *= -1;
      for (int k = i; k < n; ++k)
        std::swap(A[i][k], A[j][k]);
    }
    int v = inv(A[i][i], p);
    f = f * A[i][i] % p;
    for (int k = i; k < n; ++k)
      A[i][k] = A[i][k] * v % p;
    for (int j = i + 1; j < n; ++j)
      for (int k = n - 1; k >= i; --k)
        A[j][k] = (A[j][k] - A[j][i] * A[i][k]) % p;
  }
  return f;
}
int ans1 = 1, ans2 = 1;
void solve() {
  for (int i = 0; i < num; ++i)
    for (int j = 0; j < num; ++j)
      B[i][j] = A[i][j];
  ans1 = ans1 * solve(A, num, mod1) % mod1;
  ans2 = ans2 * solve(B, num, mod2) % mod2;
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i)
    scanf("%d%d%d", &e[i].a, &e[i].b, &e[i].v);
  std::sort(e, e + m);
  for (int i = 0, j; i < m; ) {
    j = i;
    while (j < m && e[j].v == e[i].v) ++j;
    for (int k = i; k < j; ++k) e[k].addEdge();
    for (int k = 1; k <= n; ++k) pos[k] = -1;
    for (int k = 1; k <= n; ++k) if (Find(k) == k) {
      num = 0;
      dfs(k, e[i].v, k);
      solve();
    }
    i = j;
  }
  int t = 0;
  for (int i = 1; i <= n; ++i) t += (Find(i) == i);
  printf("%d\n", t > 1 ? 0 : ((ans1 * g1 + ans2 * g2) % mod + mod) % mod);
  return 0;
}

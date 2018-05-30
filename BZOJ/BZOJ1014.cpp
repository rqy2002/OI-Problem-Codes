#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
typedef long long LL;
inline int readInt() {
  int ans = 0, c;
  while (!isdigit(c = getchar()));
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getchar()));
  return ans;
}
const int base = 31;
const int N = 100050;
int pbase[N];
inline int getHash(int h1, int h2, int l2) {
  return h1 * pbase[l2] + h2;
}
struct Splay{
  int son[N][2], fa[N];
  int v[N], len[N], hash[N];
  int root, cnt;
  inline void upd(int x) {
    int lc = son[x][0], rc = son[x][1];
    len[x] = len[lc] + len[rc] + 1;
    hash[x] = getHash(getHash(hash[lc], v[x], 1), hash[rc], len[rc]);
  }
  inline int dir(int x) { return son[fa[x]][1] == x; }
  inline void rotate(int x) {
    int f = fa[x], d = dir(x);
    if (son[f][d] = son[x][d ^ 1])
      fa[son[f][d]] = f;
    if (fa[x] = fa[f])
      son[fa[f]][dir(f)] = x;
    upd(son[fa[f] = x][d ^ 1] = f);
    upd(x);
  }
  void splay(int x, int p = 0) {
    for (; fa[x] != p; rotate(x))
      if (fa[fa[x]] != p) rotate(dir(fa[x]) == dir(x) ? fa[x] : x);
    if (!p) root = x;
  }
  void kth(int k, int x = -1) {
    if (x == -1) x = root;
    int y = fa[x];
    while (k != len[son[x][0]]) {
      if (k < len[son[x][0]]) {
        x = son[x][0];
      } else {
        k -= len[son[x][0]] + 1;
        x = son[x][1];
      }
    }
    splay(x, y);
  }
  void insert(int k, int w) {
    int p = ++cnt;
    v[p] = w;
    kth(k);
    if (!root) {
      root = p;
    } else {
      if (son[p][1] = son[root][1])
        fa[son[p][1]] = p;
      if (son[p][0] = root)
        fa[root] = p;
      son[root][1] = 0;
      upd(root);
      upd(root = p);
    }
  }
  inline void modify(int k, int w) {
    kth(k);
    v[root] = w;
    upd(root);
  }
  inline int query(int l, int r) {
    kth(r + 1);
    kth(l - 1, son[root][0]);
    return hash[son[son[root][0]][1]];
  }
};
Splay T;

int n, m;
char s[N];
bool check(int a, int b, int l) {
  return T.query(a, a + l - 1) == T.query(b, b + l - 1);
}
int query(int a, int b) {
  int l = 0, r = n - std::max(a, b) - 1;
  while (l < r) {
    int mid = r + (l - r) / 2;
    if (check(a, b, mid)) l = mid;
    else r = mid - 1;
  }
  return l;
}
int main() {
  pbase[0] = 1;
  for (int i = 1; i < N; ++i) pbase[i] = (LL)pbase[i - 1] * base;
  scanf("%s", s + 1);
  n = strlen(s + 1) + 2;
  s[0] = s[n - 1] = 'z' + 1;
  for (int i = 0; i < n; ++i) T.insert(std::max(0, i - 1), s[i] - 'a');
  scanf("%d", &m);
  while (m--) {
    int x;
    while (!isalpha(*s = getchar()));
    if (*s == 'Q') {
      printf("%d\n", query(readInt(), readInt()));
    } else if (*s == 'R') {
      x = readInt();
      while (!isalpha(*s = getchar()));
      T.modify(x, *s - 'a');
    } else {
      x = readInt();
      while (!isalpha(*s = getchar()));
      T.insert(x, *s - 'a');
      ++n;
    }
  }
  return 0;
}

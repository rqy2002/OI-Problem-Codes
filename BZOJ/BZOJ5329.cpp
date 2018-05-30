#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>

const int L = 10000000;
inline char getChar() {
  static char s[L], *end = s, *p = s;
  if (p == end) {
    if (feof(stdin)) return EOF;
    end = s + fread(p = s, 1, L, stdin);
  }
  return *(p++);
}

int readInt() {
  int ans = 0, c;
  while (!isdigit(c = getChar()));
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getChar()));
  return ans;
}

char s[L], *p = s, *end = s + L;
inline void putChar(char c) {
  if (p == end) fwrite(p = s, 1, L, stdout);
  *(p++) = c;
}

void printInt(int x, char c = ' ') {
  if (x >= 10) printInt(x / 10, EOF);
  putChar(x % 10 + '0');
  if (c != EOF) putChar(c);
}

const int N = 100050;
const int M = 400050;

int n, m, pre[N], nxt[M], to[M], cnt;

inline void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  to[pre[y] = cnt++] = x;
}

namespace Tree{
const int N = 200050;

int n, pre[N], nxt[N * 2], to[N * 2], cnt;
bool ty[N]; // true: circle; false: square

inline void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  to[pre[y] = cnt++] = x;
}

int dep2[N], pos[N], dep[N], nd[N * 2], cnt2;

void dfs(int x, int fa) {
  dep2[x] = dep2[fa] + ty[x];
  nd[pos[x] = ++cnt2] = x;
  dep[x] = dep[fa] + 1;
  for (int i = pre[x]; i >= 0; i = nxt[i])
    if (to[i] != fa) {
      dfs(to[i], x);
      nd[++cnt2] = x;
    }
}

inline int mind(int x, int y) { return dep[x] < dep[y] ? x : y; }

int minv[20][N * 2], log2[N * 2];

void InitRMQ() {
  for (int i = 1; i <= cnt2; ++i) minv[0][i] = nd[i];
  for (int i = 1; (1 << i) <= cnt2; ++i)
    for (int j = 1; (j + (1 << i)) <= cnt2 + 1; ++j)
      minv[i][j] = mind(minv[i - 1][j], minv[i - 1][j + (1 << (i - 1))]);
  for (int i = 1, j = 0; i <= cnt2; ++i)
    log2[i] = j += (i >= (1 << (j + 1)));
}

inline int LCA(int x, int y) {
  if ((x = pos[x]) > (y = pos[y])) std::swap(x, y);
  int k = log2[y - x + 1];
  return mind(minv[k][x], minv[k][y - (1 << k) + 1]);
}

inline int count(int x, int y) {
  int l = LCA(x, y);
  return dep2[x] + dep2[y] - 2 * dep2[l] + ty[l] - ty[x] - ty[y];
}

bool cmp(int a, int b) { return pos[a] < pos[b]; } 

int A[N];
int stack[N], top;

void Solve() {
  cnt2 = 0;
  dfs(1, 0);
  InitRMQ();
  int q = readInt();
  while (q--) {
    int s = readInt();
    for (int i = 0; i < s; ++i) A[i] = readInt();
    std::sort(A, A + s, cmp);
    int ans = 0;
    top = 0;
    for (int i = 0; i < s; ++i) {
      int x = A[i];
      while (top > 1 && LCA(stack[top - 2], x) == LCA(stack[top - 1], x)) {
        ans += count(stack[top - 2], stack[top - 1]);
        --top;
      }
      if (top > 0) {
        int l = LCA(stack[top - 1], x);
        if (l != stack[top - 1]) {
          ans += count(stack[top - 1], l) + ty[l];
          stack[top - 1] = l;
        }
      }
      stack[top++] = x;
    }
    while (top > 1) ans += count(stack[top - 2], stack[top - 1]), --top;
    printInt(ans, '\n');
  }
}
};

int dfn[N], cnt2;
int stack[N], top, bcnt;

int Tarjan(int x, int fa) {
  int lowx = dfn[x] = ++cnt2;
  stack[top++] = x;
  for (int i = pre[x]; i >= 0; i = nxt[i])
    if (to[i] != fa) {
      if (dfn[to[i]] == 0) lowx = std::min(lowx, Tarjan(to[i], x));
      else lowx = std::min(lowx, dfn[to[i]]);
    }
  if (lowx >= dfn[fa]) {
    int nn = n + (++bcnt);
    Tree::ty[nn] = false;
    Tree::addEdge(x, nn);
    if (fa > 0) Tree::addEdge(fa, nn);
    while (stack[--top] != x) Tree::addEdge(stack[top], nn);
  }
  return lowx;
}

int main() {
  //freopen("game.in", "r", stdin);
  //freopen("game.out", "w", stdout);
  int T = readInt();
  while (T--) {
    n = readInt();
    m = readInt();
    memset(pre, -1, sizeof pre);
    memset(Tree::pre, -1, sizeof Tree::pre);
    cnt = Tree::cnt = 0;
    for (int i = 0; i < m; ++i)
      addEdge(readInt(), readInt());
    for (int i = 1; i <= n; ++i) Tree::ty[i] = true;
    memset(dfn, 0, sizeof dfn);
    top = bcnt = 0;
    Tarjan(1, 0);
    Tree::n = n + bcnt;
    Tree::Solve();
  }
  fwrite(s, 1, p - s, stdout);
  return 0;
}

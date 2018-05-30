#include <cstdio>
#include <queue>
#include <algorithm>
#include <cctype>

typedef long long LL;

const int N = 2000;
const int M = 50000;
const LL INF = 1e18;

int to[M], cost[M], ret[M], pre[N], nxt[M], cnt;
int S, T, pn;
LL dis[N];
int fa[N];

bool Spfa() {
  static std::queue<int> Q;
  static bool inQue[N];
  std::fill(dis, dis + pn, INF);
  std::fill(inQue, inQue + pn, 0);
  dis[S] = 0;
  while (!Q.empty()) Q.pop();
  Q.push(S);
  inQue[S] = 1;
  while (!Q.empty()) {
    int x = Q.front(); Q.pop();
    for (int j = pre[x]; j >= 0; j = nxt[j])
      if (ret[j] && dis[to[j]] > dis[x] + cost[j]) {
        dis[to[j]] = dis[x] + cost[j];
        fa[to[j]] = j;
        if (!inQue[to[j]]) {
          Q.push(to[j]);
          inQue[to[j]] = true;
        }
      }
    inQue[x] = false;
  }
  return dis[T] < INF;
}

LL MCMF() {
  LL ans = 0;
  while (Spfa()) {
    ans += dis[T];
    for (int i = T; i != S; i = to[fa[i] ^ 1]) {
      --ret[fa[i]];
      ++ret[fa[i] ^ 1];
    }
  }
  return ans;
}

inline void _addedge(int x, int y, int w, int c) {
  nxt[cnt] = pre[x]; 
  to[pre[x] = cnt] = y;
  cost[cnt] = w;
  ret[cnt++] = c;
}

inline void addedge(int x, int y, int w) {
  _addedge(x, y, w, 1);
  _addedge(y, x, -w, 0);
}

inline int read() {
  int ans = 0;
  char c;
  do c = getchar(); while (!isdigit(c));
  while (isdigit(c)) {
    ans = ans * 10 + c - '0';
    c = getchar();
  }
  return ans;
}

int main() {
  int n, m;
  n = read();
  m = read();
  S = n * 2;
  T = S + 1;
  pn = T + 1;
  std::fill(pre, pre + pn, -1);
  for (int i = 0; i < n; ++i) {
    addedge(S, i + n, read());
    addedge(S, i, 0);
    addedge(i + n, T, 0);
  }
  for (int i = 0; i < m; ++i) {
    int x = read(), y = read();
    if (x > y) std::swap(x, y);
    addedge(x - 1, y + n - 1, read());
    
  }
  return !printf("%d", MCMF());
}

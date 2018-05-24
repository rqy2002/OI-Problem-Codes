/**************************************************************
 * Problem: Luogu P2254
 * Author: _rqy
 * Date: 2018 Mar 21
**************************************************************/
#include <algorithm>
#include <cstdio>

const int N = 205;

int n, m;
bool map[N][N];

struct MonoQueue{
  int pos[N], val[N], hd, tl;
  void init() { hd = tl = 0; }
  void push(int p, int x) {
    while (tl > hd && val[tl - 1] < x) --tl;
    pos[tl] = p; val[tl++] = x;
  }
  inline void pop(int p) {
    if (hd < tl && pos[hd] == p) ++hd;
  }
  inline int getMax() const { return hd == tl ? -100000 : val[hd]; }
}Q;

int f[N][N];

void WorkUp(int t) {
  for (int j = 0; j < m; ++j) {
    Q.init();
    for (int i = n - 1; i >= 0; --i) {
      if (!map[i][j]) {
        Q.init();
      } else {
        Q.push(i, f[i][j] + i);
        f[i][j] = Q.getMax() - i;
        Q.pop(i + t);
      }
    }
  }
}

void WorkDown(int t) {
  for (int j = 0; j < m; ++j) {
    Q.init();
    for (int i = 0; i < n; ++i) {
      if (!map[i][j]) {
        Q.init();
      } else {
        Q.push(i, f[i][j] - i);
        f[i][j] = Q.getMax() + i;
        Q.pop(i - t);
      }
    }
  }
}

void WorkLeft(int t) {
  for (int i = 0; i < n; ++i) {
    Q.init();
    for (int j = m - 1; j >= 0; --j) {
      if (!map[i][j]) {
        Q.init();
      } else {
        Q.push(j, f[i][j] + j);
        f[i][j] = Q.getMax() - j;
        Q.pop(j + t);
      }
    }
  }
}

void WorkRight(int t) {
  for (int i = 0; i < n; ++i) {
    Q.init();
    for (int j = 0; j < m; ++j) {
      if (!map[i][j]) {
        Q.init();
      } else {
        Q.push(j, f[i][j] - j);
        f[i][j] = Q.getMax() + j;
        Q.pop(j - t);
      }
    }
  }
}

int main() {
  int x, y, k;
  scanf("%d%d%d%d%d", &n, &m, &x, &y, &k);
  static char _s[N];
  for (int i = 0; i < n; ++i) {
    scanf("%s", _s);
    for (int j = 0; j < m; ++j)
      map[i][j] = (_s[j] == '.');
  }

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      f[i][j] = (i == x - 1 && j == y - 1) ? 0 : -100000;

  while (k--) {
    int s, t, k;
    scanf("%d%d%d", &s, &t, &k);
    t = t - s + 1;
    if (k == 1) WorkUp(t);
    else if (k == 2) WorkDown(t);
    else if (k == 3) WorkLeft(t);
    else WorkRight(t);
  }

  int ans = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      ans = std::max(ans, f[i][j]);
  printf("%d\n", ans);
  return 0;
}

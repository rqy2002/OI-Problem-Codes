/**************************************************************
 * Problem: Luogu P2463
 * Author: Rqy
 * Date: 2017 Dec 26
 * Algorithm: 后缀数组
**************************************************************/
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <map>
inline char getChar() {
  static char buf[10000000], *end = buf, *p = buf;
  if (p == end) end = buf + fread(p = buf, sizeof(char), 10000000, stdin);
  return *(p++);
}
inline int readInt() {
  int ans = 0, c;
  while (!isdigit(c = getChar()));
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getChar()));
  return ans;
}
const int N = 1050;
int s[N * N], m, n;
int belong[N * N];
int sa[N * N], tmp[2][N * N], c[N * N], rank[N * N], height[N * N];
int q;
int get(int i) {
  static std::map<int, int> M;
  if (M.count(i)) return M[i];
  return M[i] = q++;
}
int vis[N * N], vtime;
bool check(int mid) {
  int t = 0;
  ++vtime;
  for (int i = 1; i < n; ++i) {
    if (height[i] < mid) t = 0, ++vtime;
    if (~belong[sa[i]] && vis[belong[sa[i]]] < vtime) {
      if (++t == m) return true;
      vis[belong[sa[i]]] = vtime;
    }
  }
  return false;
}
int main() {
  q = m = readInt();
  int i;
  memset(s, -1, sizeof s);
  memset(tmp, -1, sizeof tmp);
  for (i = n = 0; i < m; ++i) {
    int l = readInt() - 1;
    for (int k = 0, j = readInt(), t; k < l; ++k) {
      belong[n] = i;
      s[n++] = get((t = readInt()) - j);
      j = t;
    }
    belong[n] = -1;
    s[n++] = i;
  }
  int *x = tmp[0], *y = tmp[1];
  for (i = 0; i < q; ++i) c[i] = 0;
  for (i = 0; i < n; ++i) ++c[x[i] = s[i]];
  for (i = 1; i < q; ++i) c[i] += c[i - 1];
  for (i = n - 1; ~i; --i) sa[--c[x[i]]] = i;
  for (int k = 1; k == 1 || q < n; k <<= 1, std::swap(x, y)) {
    int j = 0;
    for (i = n - k; i < n; ++i) y[j++] = i;
    for (i = 0; i < n; ++i) if (sa[i] >= k) y[j++] = sa[i] - k;

    for (i = 0; i < q; ++i) c[i] = 0;
    for (i = 0; i < n; ++i) ++c[x[y[i]]];
    for (i = 1; i < q; ++i) c[i] += c[i - 1];
    for (i = n - 1; ~i; --i) sa[--c[x[y[i]]]] = y[i];

    q = 0;
    y[sa[0]] = q++;
    for (i = 1; i < n; ++i)
      y[sa[i]] = (x[sa[i]] == x[sa[i - 1]] &&
          x[sa[i] + k] == x[sa[i - 1] + k]) ? q - 1 : q++;
  }
  for (i = 0; i < n; ++i) rank[sa[i]] = i;
  for (int k = i = 0; i < n; ++i) {
    if (k) --k;
    if (rank[i]) {
      int j = sa[rank[i] - 1];
      while (i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
      height[rank[i]] = k;
    }
  }
  vtime = 0;
  int l = 0, r = n;
  while (l < r) {
    int mid = r + (l - r) / 2;
    if (check(mid)) l = mid;
    else r = mid - 1;
  }
  printf("%d\n", l + 1);
  return 0;
}

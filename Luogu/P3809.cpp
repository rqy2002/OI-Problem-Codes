/**************************************************************
 * Problem: Luogu P3809
 * Author: Rqy
 * Date: 2017 Dec 25
 * Algorithm: 后缀数组
 **************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int L = 10000000;
char buf[L], *p = buf;
inline void putChar(char c) {
  *(p++) = c;
  if (p == buf + L) fwrite(p = buf, sizeof(char), L, stdout);
}
inline void putInt(int x) {
  static int t[20];
  int p = 0;
  while (x) t[p++] = x % 10, x /= 10;
  while (p--) putChar((char)(t[p] + '0'));
  putChar(' ');
}
const int N = 2000050;
char s[N];
int sa[N], tmp[2][N];
int c[N];
int get(char c) {
  if (c >= '0' && c <= '9') return c - '0';
  else if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
  else return c - 'a' + 10 + 26;
}
int main() {
  scanf("%s", s);
  int n = (int)strlen(s), m = 10 + 26 + 26, i;
  memset(tmp, -1, sizeof tmp);
  int *x = tmp[0], *y = tmp[1];
  for (i = 0; i < m; ++i) c[i] = 0;
  for (i = 0; i < n; ++i) ++c[x[i] = get(s[i])];
  for (i = 1; i < m; ++i) c[i] += c[i - 1];
  for (i = n - 1; ~i; --i) sa[--c[x[i]]] = i;
  for (int k = 1; k == 1 || m < n; k <<= 1, std::swap(x, y)) {
    int j = 0;
    for (i = n - k; i < n; ++i) y[j++] = i;
    for (i = 0; i < n; ++i) if (sa[i] >= k) y[j++] = sa[i] - k;

    for (i = 0; i < m; ++i) c[i] = 0;
    for (i = 0; i < n; ++i) ++c[x[y[i]]];
    for (i = 1; i < m; ++i) c[i] += c[i - 1];
    for (i = n - 1; ~i; --i) sa[--c[x[y[i]]]] = y[i];

    m = 0;
    y[sa[0]] = m++;
    for (i = 1; i < n; ++i)
      y[sa[i]] = (x[sa[i]] == x[sa[i - 1]] &&
          x[sa[i] + k] == x[sa[i - 1] + k]) ? m - 1 : m++;
  }
  for (i = 0; i < n; ++i) putInt(sa[i] + 1);
  fwrite(buf, sizeof(char), p - buf, stdout);
  return 0;
}

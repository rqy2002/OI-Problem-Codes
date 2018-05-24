/**************************************************************
 * Problem: NOI2017-Integer
 * Author: Rqy
 * Date: 2018 Mar 05
 * Algorithm: 线段树
**************************************************************/
#include <algorithm>
#include <cctype>
#include <cstdio>
const int L = 10000000;
char buf[L], *p = buf, *end = buf;
inline int getChar() {
  if (p == buf && feof(stdin)) return EOF;
  if (p == end) end = buf + fread(p = buf, sizeof(char), L, stdin);
  return *(p++);
}
inline int readInt() {
  int ans = 0, c, f = 1;
  while (!isdigit(c = getChar()) && c != '-');
  if (c == '-') f = -1, c = getChar();
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getChar()));
  return ans * f;
}
const int N = 4002000;
const int B = 1000500;
typedef unsigned int U;
typedef unsigned long long ULL;
const U all[2] = {0U, ~0U};
U v[2][N];
int cmp[N];
inline void upd(int o, int l, int r) {
  if (l == r) {
    cmp[o] = v[0][l] < v[1][l] ? -1 : v[0][l] == v[1][l] ? 0 : 1;
  } else {
    cmp[o] = cmp[o << 1 | 1] ? cmp[o << 1 | 1] : cmp[o << 1];
  }
}
void modify(int o, int l, int r, int x) {
  if (x < l || r < x) return;
  if (l < r) {
    int mid = (l + r) / 2;
    modify(o << 1, l, mid, x);
    modify(o << 1 | 1, mid + 1, r, x);
  }
  upd(o, l, r);
}
int query(int o, int l, int r, int x) {
  if (r <= x) return cmp[o];
  if (l > x) return 0;
  int mid = (l + r) / 2;
  int t = query(o << 1 | 1, mid + 1, r, x);
  return t ? t : query(o << 1, l, mid, x);
}
inline bool check(U a, U b) { return (ULL)a + (ULL)b >= (1ULL << 32); }
void add(int x, int b) {
  int f = x < 0; x = f ? -x : x;
  int b1 = b >> 5, b2 = b & 31;
  U x1 = (U)x << b2;
  U t = check(v[f][b1], x1);
  U x2 = ((U)(x >> (31 - b2)) / 2) + t;
  v[f][b1] += x1;
  modify(1, 0, B, b1);
  t = check(v[f][++b1], x2);
  v[f][b1] += x2;
  modify(1, 0, B, b1);
  while (t) {
    t = check(v[f][++b1], 1U);
    v[f][b1] += 1U;
    modify(1, 0, B, b1);
  }
}
inline int query(int x) {
  int x1 = x >> 5, x2 = x & 31;
  return
    (((2ULL << 32) + v[0][x1] - v[1][x1] - (query(1, 0, B, x1 - 1) < 0))
     >> x2) & 1;
}
int main() {
  int n = readInt();
  readInt(); readInt(); readInt();
  while (n--)
    if (readInt() == 1) {
      int x = readInt();
      add(x, readInt());
    } else
      printf("%d\n", query(readInt()));
  return 0;
}

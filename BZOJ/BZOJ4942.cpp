/**************************************************************
 * Problem: NOI2017-Integer
 * Author: Rqy
 * Date: 2018 Mar 05
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <set>
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
U v[2][N];
std::set<int> S;
void modify(int x) {
  bool y = S.count(x);
  if (v[0][x] == v[1][x] && y) S.erase(x);
  else if (v[0][x] != v[1][x] && !y) S.insert(x);
}
int queryS(int x) {
  std::set<int>::iterator it = S.lower_bound(x);
  if (it == S.begin()) return 0;
  x = *(--it);
  return v[1][x] > v[0][x] ? -1 : 1;
}
inline bool check(U a, U b) { return (ULL)a + (ULL)b >= (1ULL << 32); }
void add(int x, int b) {
  int f = x < 0; x = f ? -x : x;
  int b1 = b >> 5, b2 = b & 31;
  U x1 = (U)x << b2;
  U t = check(v[f][b1], x1);
  U x2 = ((U)(x >> (31 - b2)) / 2) + t;
  v[f][b1] += x1;
  modify(b1);
  t = check(v[f][++b1], x2);
  v[f][b1] += x2;
  modify(b1);
  while (t) {
    t = check(v[f][++b1], 1U);
    v[f][b1] += 1U;
    modify(b1);
  }
}
inline int query(int x) {
  int x1 = x >> 5, x2 = x & 31;
  return (((2ULL << 32) + v[0][x1] - v[1][x1] - (queryS(x1) < 0)) >> x2) & 1;
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

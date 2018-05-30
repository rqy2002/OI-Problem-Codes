#include <algorithm>
#include <cctype>
#include <cstdio>
const int N = 250050;
inline int readInt() {
  int ans = 0;
  char c;
  do c = getchar(); while (!isdigit(c));
  do {
    ans = ans * 10 + c - '0';
    c = getchar();
  } while (isdigit(c));
  return ans;
}
inline char readChar() {
  char c;
  do c = getchar(); while (isspace(c));
  return c;
}
int left[N], siz[N], fa[N];
int A[N], n;
inline void add(int i, int x) {
  while (i <= n) {
    A[i] += x;
    i += i & -i;
  }
}
inline int query(int i) {
  int ans = 0;
  while (i) {
    ans += A[i];
    i -= i & -i;
  }
  return ans;
}
int main() {
  n = readInt();
  for (int i = 1; i < n; ++i) {
    int a = readInt(), b = readInt();
    if (a > b) std::swap(a, b);
    fa[b] = a;
  }
  fa[1] = 0;
  for (int i = n; i; --i) {
    left[i] = siz[fa[i]] + 1;
    siz[fa[i]] += ++siz[i];
  }
  for (int i = 1; i <= n; ++i)
    left[i] += left[fa[i]];
  for (int i = 2; i <= n; ++i) {
    add(left[i], 1);
    add(left[i] + siz[i], -1);
  }
  int m = readInt() + n - 1;
  while (m--) {
    if (readChar() == 'W')
      printf("%d\n", query(left[readInt()]));
    else {
      int a = std::max(readInt(), readInt());
      add(left[a], -1);
      add(left[a] + siz[a], 1);
    }
  }
  return 0;
}

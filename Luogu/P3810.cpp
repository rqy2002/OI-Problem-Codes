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

const int N = 100050;
const int M = 39999983;

struct{
  LL key[M];
  int val[M];

  int operator()(int i, int j, int) {
    LL x = (LL)i * N + j;
    int t = x % M;
    while (key[t] != 0 && key[t] != x) if (++t == M) t = 0;
    return val[t];
  }

  int& operator()(int i, int j) {
    LL x = (LL)i * N + j;
    int t = x % M;
    while (key[t] != 0 && key[t] != x) if (++t == M) t = 0;
    key[t] = x;
    return val[t];
  }
} H;

struct Point{
  int a, b, c;

  inline bool operator<(const Point &t) const {
    return a == t.a ? b == t.b ? c < t.c : b < t.b : a < t.a;
  }

  inline bool operator==(const Point &t) const {
    return a == t.a && b == t.b && c == t.c;
  }
} P[N];

int n, na, nb, nc, A[N], B[N], C[N], ans[N];

void Add(int x, int y) {
  for (int i = x; i <= nb; i += i & -i)
    for (int j = y; j <= nc; j += j & -j)
      ++H(i, j);
}

int Query(int x, int y) {
  int ans = 0;
  for (int i = x; i > 0; i -= i & -i)
    for (int j = y; j > 0; j -= j & -j)
      ans += H(i, j, 0);
  return ans;
}

inline int sortUnique(int *begin, int *end) {
  std::sort(begin, end);
  return std::unique(begin, end) - begin;
}

int main() {
  n = readInt();
  readInt();
  for (int i = 0; i < n; ++i) {
    A[i] = P[i].a = readInt();
    B[i] = P[i].b = readInt();
    C[i] = P[i].c = readInt();
  }
  na = sortUnique(A, A + n);
  nb = sortUnique(B, B + n);
  nc = sortUnique(C, C + n);
  for (int i = 0; i < n; ++i) {
    P[i].a = std::lower_bound(A, A + na, P[i].a) - A + 1;
    P[i].b = std::lower_bound(B, B + nb, P[i].b) - B + 1;
    P[i].c = std::lower_bound(C, C + nc, P[i].c) - C + 1;
  }
  std::sort(P, P + n);
  for (int i = 0, j = 0, l = 0; i < n; ++i) {
    while (j < i || (j < n && P[j] == P[i])) ++j;
    if (i > 0 && P[i - 1] < P[i])
      l = Query(P[i].b, P[i].c) + j - i - 1;
    ++ans[l];
    Add(P[i].b, P[i].c);
  }
  for (int i = 0; i < n; ++i) printf("%d\n", ans[i]);
  return 0;
}

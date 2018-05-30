#include <algorithm>
#include <cstdio>
int p[10];
int f[10][10];
inline bool check(int a, int b) {
  return std::abs(a - b) >= 2;
}
int count(int N) {
  if (!N) return 0;
  int n = 0;
  while (N) {
    p[n++] = N % 10;
    N /= 10;
  }
  p[n] = 0;
  bool ok = true;
  for (int j = 0; j < 10; ++j) f[n][j] = 0;
  for (int i = n - 1; ~i; --i) {
    for (int j = 0; j < 10; ++j) {
      f[i][j] = ok && (j < p[i]) && ((i == n - 1 && j) || check(p[i + 1], j));
      if (i != n - 1 && j) ++f[i][j];
      for (int k = 0; k < 10; ++k)
        if (check(k, j)) f[i][j] += f[i + 1][k];
    }
    if (i < n - 1 && !check(p[i], p[i + 1])) ok = false;
  }
  int ans = ok;
  for (int i = 0; i < 10; ++i)
    ans += f[0][i];
  return ans;
}
int main() {
  int A, B;
  scanf("%d%d", &A, &B);
  printf("%d\n", count(B) - count(A - 1));
  return 0;
}

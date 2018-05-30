#include <cctype>
#include <cstdio>
const int K = 105;
int A[100];
int a[K];
inline int get() {
  int c;
  while (!isdigit(c = getchar()));
  return c - '0';
}
void solve(int dep) {
  int t = get();
  if (t == 0)
    ++a[dep * 2];
  else if (t == 2) {
    solve(dep - 1);
    solve(dep - 1);
    solve(dep - 1);
    solve(dep - 1);
  }
}
int main() {
  int k;
  scanf("%d", &k);
  solve(k);
  int len = 1;
  for (int i = 0; i < k * 2; ++i) {
    a[i + 1] += a[i] / 2;
    a[i] %= 2;
  }
  for (int i = k * 2; ~i; --i) {
    int t;
    for (int j = t = 0; j < len; ++j) {
      t = (A[j] = A[j] * 2 + t) / 10;
      A[j] %= 10;
    }
    if (t) A[len++] = t;
    if (a[i]) ++A[0];
  }
  while (len--) putchar(A[len] + '0');
  putchar('\n');
  return 0;
}

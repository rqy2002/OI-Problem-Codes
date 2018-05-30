#include <cstdio>
int A[10000], lenA;
bool mark[1005];
inline int get(int n, int p) {
  int ans = 0;
  while (n) ans += (n /= p);
  return ans;
}
int main() {
  int n;
  scanf("%d", &n);
  lenA = 1;
  A[0] = 1;
  for (int i = 2; i <= 2 * n; ++i) if (!mark[i]) {
    for (int j = i * i; j <= 2 * n; j += i) mark[j] = 1;
    for (int k = get(2 * n, i) - get(n, i) - get(n + 1, i); k; --k) {
      int t, j;
      for (t = j = 0; j < lenA || t; ++j) {
        t = (A[j] = A[j] * i + t) / 10;
        A[j] %= 10;
      }
      lenA = j;
    }
  }
  while (lenA--) putchar(A[lenA] + '0');
  return 0;
}

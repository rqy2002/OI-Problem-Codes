#include <cstdio>
const int N = 100050;
int A[N];
int _T[N * 2];
int *T = _T + N;
int main() {
  int n, b, p;
  scanf("%d%d", &n, &b);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &A[i]);
    if (A[i] == b) p = i;
  }
  int l = 0;
  ++T[0];
  for (int i = p - 1; ~i; --i) {
    if (A[i] > b) --l;
    else ++l;
    ++T[l];
  }
  l = 0;
  int ans = T[0];
  for (int i = p + 1; i < n; ++i) {
    if (A[i] < b) --l;
    else ++l;
    ans += T[l];
  }
  printf("%d\n", ans);
  return 0;
}

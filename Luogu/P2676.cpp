#include <algorithm>
#include <cstdio>
int A[20005];
int main() {
  int n, b;
  scanf("%d%d", &n, &b);
  for (int i = 0; i < n; ++i) scanf("%d", &A[i]);
  std::sort(A, A + n);
  for (int i = n - 1; ~i; --i) if ((b -= A[i]) <= 0) {
    printf("%d\n", n - i);
    break;
  }
  return 0;
}

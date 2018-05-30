#include <algorithm>
#include <cstdio>
const int N = 100050;
int n;
int A[55];
bool mark[N];
int prime[N], prcnt;
void getPrime() {
  prcnt = 0;
  for (int i = 2; i < N; ++i) {
    if (!mark[i]) prime[prcnt++] = i;
    for (int j = 0; j < prcnt && i * prime[j] < N; ++j) {
      mark[i * prime[j]] = 1;
      if (!(i % prime[j])) break;
    }
  }
}
int f[N];
int main() {
  scanf("%d", &n);
  int maxv = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &A[i]);
    maxv = std::max(maxv, A[i]);
  }
  getPrime();
  for (int i = maxv; i; --i) {
    f[i] = 0;
    for (int j = 0; j < n; ++j) f[i] += A[j] / i;
    for (int j = 0; j < prcnt && i * prime[j] <= maxv; ++j) {
      int anst = f[i * prime[j]];
      for (int k = 0; k < n; ++k) anst += A[k] / i % prime[j];
      f[i] = std::min(f[i], anst);
    }
  }
  printf("%d\n", f[1]);
  return 0;
}

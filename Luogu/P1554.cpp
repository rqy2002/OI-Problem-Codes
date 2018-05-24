#include <algorithm>
#include <cstdio>
int A[10];
void get(int x) {
  if (x == 0) return;
  get(x / 10); ++A[x % 10];
}
int main() {
  int M, N;
  scanf("%d%d", &M, &N);
  for (int i = M; i <= N; ++i)
    get(i);
  for (int i = 0; i < 10; ++i)
    printf("%d ", A[i]);
  return 0;
}

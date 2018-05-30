#include<cstdio>
const int N = 50050;
typedef long long LL;
LL C[N], f[N];
int L;
inline LL calc(int j, int i) {
  return f[j] + (C[i] - C[j] - L) * (C[i] - C[j] - L); 
}
int main() {
  int n, i, j;
  scanf("%d%d", &n, &L);
  ++L;
  C[0] = 0;
  for (i = 1; i <= n; ++i) {
    scanf("%lld", &C[i]);
    ++C[i];
    C[i] += C[i - 1];
  }
  f[0] = 0;
  for (i = 1, j = 0; i <= n; ++i) {
    f[i] = calc(j, i);
    for (int q = j + 1; q < i; ++q)
      if (f[i] >= calc(q, i)) {
        j = q;
        f[i] = calc(q, i);
      }
  }
  printf("%lld", f[n]);
  return 0;
}

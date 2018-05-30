#include <algorithm>
#include <cstdio>
const int N = 1000050;
struct Info{
  int co, x;
  bool operator<(const Info &l) const {
    return x < l.x;
  }
}A[N];
int T[65], l;
int main() {
  int n = 0, k, t;
  scanf("%*d%d", &k);
  for (int i = 0; i < k; ++i) {
    scanf("%d", &t);
    while (t--) {
      scanf("%d", &A[n].x);
      A[n++].co = i;
    }
  }
  std::sort(A, A + n);
  l = 0;
  int ans = 2000000000;
  for (int i = 0, j = 0; j < n; ++i) {
    while (j < n && l < k) 
      if (!(T[A[j++].co]++)) ++l;
    if (l == k)
      ans = std::min(ans, A[j - 1].x - A[i].x);
    if (!(--T[A[i].co])) --l;
  }
  printf("%d\n", ans);
  return 0;
}

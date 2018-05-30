#include <algorithm>
#include <cctype>
#include <cstdio>
using std::min;
typedef long long LL;
LL INF = 1000000000000000LL;
const int N = 100050;
inline int readInt() {
  int ans = 0;
  char c;
  do c = getchar(); while (!isdigit(c));
  while (isdigit(c)) {
    ans = ans * 10 + c - '0';
    c = getchar();
  }
  return ans;
}
LL A[N], B[N];
LL f[N];
inline LL cost(int i, int j) {
  if (A[i] == B[j]) return INF;
  return std::abs(A[i] - B[j]);
}
int main() {
  int n = readInt();
  for (int i = 1; i <= n; ++i) {
    A[i] = readInt();
    B[i] = readInt();
  }
  if (n == 1 && A[1] == B[1]) return puts("-1"), 0;
  std::sort(A + 1, A + n + 1);
  std::sort(B + 1, B + n + 1);
  f[0] = 0;
  for (int i = 1; i <= n; ++i) {
    f[i] = f[i - 1] + cost(i, i);
    if (i > 1) f[i] = min(f[i], f[i - 2] + cost(i, i - 1) + cost(i - 1, i));
    if (i > 2) {
      f[i] = min(f[i], f[i - 3] + cost(i, i - 2) + cost(i - 1, i - 1) + cost(i - 2, i));
      f[i] = min(f[i], f[i - 3] + cost(i, i - 2) + cost(i - 1, i) + cost(i - 2, i - 1));
      f[i] = min(f[i], f[i - 3] + cost(i, i - 1) + cost(i - 2, i) + cost(i - 1, i - 2));
    }
  }
  printf("%lld\n", f[n]);
  return 0;
}

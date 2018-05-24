#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>

namespace Hash{
  const int Mod = 29999999;
  int key[Mod], val[Mod];
  int lastt, lasts;
  bool count(int t) {
    int s = t % Mod;
    while (key[s] != t && key[s] != 0)
      if (++s == Mod) s = 0;
    lastt = t; lasts = s;
    return key[s] == t;
  }
  int &query(int t) {
    int s = t % Mod;
    if (t == lastt) s = lasts;
    else while (key[s] != t && key[s] != 0) if (++s == Mod) s = 0;
    key[s] = t;
    return val[s];
  }
};

typedef long long LL;
const int N = 15;
const int mod = 1000000007;
const int M = 500;

int n, m, A[M], B[M], C[M];

int f(int S1, int S2) {
  // E[S1,S2] * 2^|S|
  if (S1 == 0) return 1;
  if (Hash::count(S1 << n | S2)) return Hash::query(S1 << n | S2);
  int &ans = Hash::query(S1 << n | S2) = 0, x = 0;
  while ((S1 >> x & 1) == 0) ++x;
  for (int i = 0; i < m; ++i)
    if ((A[i] & S1) == A[i] && (B[i] & S2) == B[i] && (A[i] >> x & 1) == 1)
    ans = (ans + f(S1 & ~A[i], S2 & ~B[i]) * C[i]) % mod;
  return ans;
}

int main() {
  int c;
  scanf("%d%d", &n, &c);
  while (c--) {
    int t, x, y;
    scanf("%d", &t);
    if (t == 0) {
      scanf("%d%d", &x, &y);
      A[m] = 1 << (x - 1), B[m] = 1 << (y - 1), C[m++] = 1;
    } else {
      scanf("%d%d", &x, &y);
      A[m] = 1 << (x - 1), B[m] = 1 << (y - 1), C[m++] = 1;
      scanf("%d%d", &x, &y);
      A[m] = 1 << (x - 1), B[m] = 1 << (y - 1), C[m++] = 1;
      if (A[m - 1] != A[m - 2] && B[m - 1] != B[m - 2]) {
        A[m] = A[m - 1] | A[m - 2], B[m] = B[m - 1] | B[m - 2];
        C[m++] = (t == 1 ? 1 : -1);
      }
    }
  }
  printf("%d\n", (f((1 << n) - 1, (1 << n) - 1) + mod) % mod);
  return 0;
}

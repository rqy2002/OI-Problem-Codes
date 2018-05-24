/**************************************************************
 * Problem: BZOJ4916
 * Author: Rqy
 * Date: 2018 Feb 26
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
typedef long long LL;
const int N = 1000050;
const int mod = 1000000007;
const int inv2 = (mod + 1) / 2;
const int inv6 = (mod + 1) / 6;
int B[N], pr[N / 5], cnt, n, B2[1050];
int s1(int i) { return (LL)i * (i + 1) % mod * inv2 % mod; }
int s2(int i) { return (LL)i * (i + 1) % mod * (2 * i + 1) % mod * inv6 % mod; }
int get(int d) {
  if (n / d < N) return B[n / d];
  //if (n / d == 1) return 1;
  int &ans = B2[d];
  if (ans) return ans;
  int m = n / d;
  ans = s2(m);
  for (int i = 2, last; i <= m; i = last + 1) {
    last = m / (m / i);
    ans = (ans - (LL)(s1(last) - s1(i - 1)) * get(i * d)) % mod;
  }
  return ans;
}
int main() {
  scanf("%d", &n);
  B[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (!B[i])
      B[pr[cnt++] = i] = i - 1;
    for (int j = 0; j < cnt && pr[j] <= (N - 1) / i; ++j)
      if (i % pr[j]) B[i * pr[j]] = B[i] * (pr[j] - 1);
      else {
        B[i * pr[j]] = B[i] * pr[j];
        break;
      }
  }
  for (int i = 2; i < N; ++i)
    B[i] = ((LL)B[i] * i + B[i - 1]) % mod;
  printf("1\n%d\n", (get(1) + mod) % mod);
  return 0;
}

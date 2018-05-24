/**************************************************************
 * Problem: Luogu P3768
 * Author: Rqy
 * Date: 2017 Dec 23
 * Algorithm: 杜教筛
**************************************************************/
#include <cstdio>
#include <map>
typedef long long LL;
typedef std::map<LL, LL> MLL;
const int N23 = 5000000;
int pr[N23 / 10], cnt;
LL S[N23];
LL n, p, inv[10];
void getS() {
  S[1] = 1;
  cnt = 0;
  for (int i = 2; i < N23; ++i) {
    if (!S[i])
      S[pr[cnt++] = i] = i - 1;
    for (int j = 0; j < cnt && (LL)pr[j] * i < N23; ++j) {
      if (i % pr[j]) S[i * pr[j]] = S[i] * S[pr[j]];
      else {
        S[i * pr[j]] = S[i] * pr[j];
        break;
      }
    }
  }
  for (int i = 2; i < N23; ++i)
    S[i] = (S[i] * i % p * i % p + S[i - 1]) % p;
}
MLL ans;
inline LL sq(LL a) {
  a %= p;
  return a * (a + 1) % p * (2 * a + 1) % p * inv[6] % p;
}
LL getAns(LL k) {
  if (k < N23) return S[k];
  if (ans.count(k)) return ans[k];
  LL ansk = k % p * ((1 + k) % p) % p * inv[2] % p;
  ansk = ansk * ansk % p;
  for (LL i = 2, last; i < k; i = last + 1) {
    last = k / (k / i);
    ansk = (ansk - (sq(last) - sq(i - 1)) % p * getAns(k / i) % p) % p;
  }
  return ans[k] = ansk;
}
int main() {
  scanf("%lld%lld", &p, &n);
  inv[1] = 1;
  for (int i = 2; i < 10; ++i) inv[i] = p - (p / i) * inv[p % i] % p;
  getS();
  LL ans = 0;
  for (LL i = 1, last; i < n; i = last + 1) {
    last = n / (n / i);
    LL q = n / i % p;
    q = q * (q + 1) % p * inv[2] % p;
    ans = (ans + (getAns(last) - getAns(i - 1)) % p * q % p * q % p);
  }
  printf("%lld\n", (ans + p) % p);
  return 0;
}


#include<cstdio>
#include<cstring>
#include<map>
typedef long long LL;
typedef std::map<int, LL> Map;
Map _phi, _mu;
int n;
const int N = 5000000;
LL phi[N], mu[N];
int pr[1000000];
void init(int n) {                    //计算[1, n]的phi值及mu值 
  memset(phi, -1, sizeof phi);
  memset(mu, -1, sizeof mu);
  int prnum = 0, i, j;
  phi[1] = mu[1] = 1;
  phi[0] = mu[0] = 0;
  for (i = 2; i <= n; ++i) {
    if (phi[i] < 0) {
      pr[prnum++] = i;
      phi[i] = i - 1;
      mu[i] = -1;
    }
    for (j = 0; j < prnum && (LL)i * pr[j] <= n; ++j) {
      if (i % pr[j]) {
        phi[i * pr[j]] = phi[i] * (pr[j] - 1);
        mu[i * pr[j]] = -mu[i];
      } else {
        phi[i * pr[j]] = phi[i] * pr[j];
        mu[i * pr[j]] = 0;
        break;
      }
    }
  }
  //for (i = 1; i <= 30; ++i) {
  //  printf("%d %d\n", i, phi[i]);
  //}
  for (i = 2; i <= n; ++i) {
    phi[i] += phi[i - 1];
    mu[i] += mu[i - 1];
  }
}
LL CalcPhi(LL n) {
  Map::iterator it; 
  if (n < N)
    return phi[n];
  if ((it = _phi.find(n)) != _phi.end())
    return it->second;
  LL i, last, ans = (LL)n * (n + 1) >> 1;
  for (i = 2; i <= n; i = last + 1) {
    last = n / (n / i);
    ans -= (last - i + 1) * CalcPhi(n / i);
  }
  return _phi[n] = ans;
}
LL CalcMu(LL n) {
  Map::iterator it; 
  if (n < N)
    return mu[n];
  if ((it = _mu.find(n)) != _mu.end())
    return it->second;
  LL i, last, ans = 1;
  for (i = 2; i <= n; i = last + 1) {
    last = n / (n / i);
    ans -= (last - i + 1) * CalcMu(n / i);
  }
  return _mu[n] = ans;
}
int main() {
  init(N - 1);
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    printf("%lld %lld\n", CalcPhi(n), CalcMu(n));
  }
  return 0;
}

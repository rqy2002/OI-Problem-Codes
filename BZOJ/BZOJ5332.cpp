
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <functional>

const int N = 100050;
const int M = 40;
const int mod = 1000000007;

typedef long long LL;

int A, B, C;
int F[N], tau[N];
bool mark[N];
int pr[N], cnt;
int FF[M + 1][M + 1][M + 1];

void Init() {
  int n = N - 1;
  for (int i = 1; i <= n; ++i) tau[i] = 1;
  for (int i = 2; i <= n; ++i) if (!mark[i]) {
    pr[cnt++] = i;
    for (int j = 1; j <= n / i; ++j) {
      mark[i * j] = 1;
      tau[i * j] += tau[j];
    }
  }
  for (int i = 1; i <= n; ++i) F[i] = F[i - 1] + tau[i];
  for (int i = 0; i < cnt - i; ++i)
    std::swap(pr[i], pr[cnt - i - 1]);
  for (int i = 1; i <= M; ++i)
    for (int j = 1; j <= M; ++j)
      for (int k = 1; k <= M; ++k)
        FF[i][j][k] =
          (0ll + FF[i - 1][j][k] + FF[i][j - 1][k] + FF[i][j][k - 1]
          - FF[i - 1][j - 1][k] - FF[i - 1][j][k - 1] - FF[i][j - 1][k - 1]
          + FF[i - 1][j - 1][k - 1] + tau[i * j * k]) % mod;
}

inline void Mod(int &a) {
  if (a >= mod) a -= mod;
  if (a < 0) a += mod;
}

int t = 0;
int dfs(int x, int A, int B, int C) {
  if (!pr[x]) return (LL)F[A] % mod * F[B] % mod * F[C] % mod;
  ++t;
  int p = pr[x];
  int n = std::max(std::max(A, B), C);
  if (p > n && n <= M) {
    return FF[A][B][C];
  }
  if (!(A && B && C)) return 0;
  int ans = dfs(x + 1, A, B, C);
  if (A >= p && B >= p) Mod(ans -= dfs(x + 1, A / p, B / p, C));
  if (B >= p && C >= p) Mod(ans -= dfs(x + 1, A, B / p, C / p));
  if (A >= p && C >= p) Mod(ans -= dfs(x + 1, A / p, B, C / p));
  if (A >= p && B >= p && C >= p) {
    int t = dfs(x + 1, A / p, B / p, C / p);
    Mod(t <<= 1);
    Mod(ans += t);
  }
  return ans;
}

int main() {
  //freopen("divsum.in", "r", stdin);
  //freopen("divsum.out", "w", stdout);
  Init();
  int T;
  scanf("%d", &T);
  while (T--) {
    int A, B, C;
    scanf("%d%d%d", &A, &B, &C);
    int c = 0;
    while (pr[c] > A && pr[c] > B && pr[c] > C) ++c;
    printf("%d\n", dfs(c, A, B, C));
  }
  //printf("%d\n", clock());
  return 0;
}

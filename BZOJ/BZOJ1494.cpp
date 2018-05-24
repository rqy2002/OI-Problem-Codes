/**************************************************************
 * Problem: BZOJ1494
 * Author: _rqy
 * Date: 2018 Mar 21
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long LL;

const int K = 5;
const int WK = 52;
const int mod = 65521;

int k;
LL n, A[WK][WK];

struct State{
  int A[K];

  State() { std::fill(A, A + k, 0); }
  State(int *A) { std::copy(A, A + k, this->A); }

  void toStd() {
    static int B[K * 2];
    std::fill(B, B + k * 2, -1);
    for (int i = 0, j = 0; i < k; ++i)
      A[i] = (B[A[i]] == -1 ? B[A[i]] = j++ : B[A[i]]);
  }

  int getAns() {
    toStd();
    static bool vis[K];
    std::fill(vis, vis + K, false);
    int ans = 1;
    for (int i = 0; i < k; ++i) if (!vis[i]) {
      int t = 0;
      for (int j = i; j < k; ++j)
        if (A[i] == A[j]) { vis[j] = true; ++t; }
      for (int j = 0; j < t - 2; ++j) ans *= t;
    }
    return ans;
  }

  int& getId() {
    static int id[15625]; // K^K

    toStd();
    int ans = 0;
    for (int i = 0; i < k; ++i)
      ans = ans * k + A[i];
    return id[ans];
  }

  int nextState(int _linkK) {
    static bool linkK[K];
    static int nxtA[K];

    for (int i = 0; i < k; ++i)
      linkK[i] = ((_linkK >> i) & 1) == 1;

    bool link0 = false;
    for (int i = 1; i < k; ++i) if (A[i] == 0) link0 = true;
    if (!link0 && !linkK[0]) return -1;
    for (int i = 0; i < k; ++i) if (linkK[i])
      for (int j = i + 1; j < k; ++j) if (linkK[j] && A[i] == A[j])
        return -1;

    std::copy(A + 1, A + k, nxtA);
    nxtA[k - 1] = k;
    for (int i = 0; i < k; ++i) if (linkK[i])
      for (int j = 1; j < k; ++j) if (A[i] == A[j])
        nxtA[j - 1] = k;

    State s(nxtA);
    return s.getId();
  }
}states[WK];
int cnt;

void dfs(int x, int num) {
  static int _t[K];
  if (x == k) {
    (states[cnt] = State(_t)).getId() = cnt;
    ++cnt;
    return;
  }
  for (_t[x] = 0; _t[x] <= num; ++_t[x])
    dfs(x + 1, std::max(num, _t[x] + 1));
}
inline void GenState() { dfs(0, 0); }

LL An[WK][WK];
void Mul(const LL A[WK][WK], const LL B[WK][WK], LL C[WK][WK]) {
  static LL _tmp[WK][WK];
  for (int i = 0; i < cnt; ++i)
    for (int j = 0; j < cnt; ++j)
      _tmp[i][j] = 0;
  for (int i = 0; i < cnt; ++i)
    for (int j = 0; j < cnt; ++j)
      for (int k = 0; k < cnt; ++k)
        (_tmp[i][k] += A[i][j] * B[j][k]) %= mod;
  for (int i = 0; i < cnt; ++i)
    for (int j = 0; j < cnt; ++j)
      C[i][j] = _tmp[i][j];
}
int main() {
  scanf("%d%lld", &k, &n);
  if (n < k) k = n;
  GenState();

  for (int i = 0; i < cnt; ++i)
    for (int S = 0; S < (1 << k); ++S) {
      int v = states[i].nextState(S);
      if (v != -1) ++A[i][v];
    }

  for (int i = 0; i < cnt; ++i) An[i][i] = 1;
  for (n -= k; n > 0; n >>= 1, Mul(A, A, A))
    if ((n & 1) == 1) Mul(An, A, An);

  LL ans = 0;
  for (int i = 0; i < cnt; ++i)
    (ans += An[i][0] * states[i].getAns()) %= mod;
  printf("%lld\n", ans);
  return 0;
}

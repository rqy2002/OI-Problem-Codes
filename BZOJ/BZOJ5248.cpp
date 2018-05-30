#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <map>

inline int readInt() {
  int ans = 0, c;
  while (!isdigit(c = getchar()));
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getchar()));
  return ans;
}

const int N = 11;
const int T = 200000;
const int INF = 0x3fffffff;

typedef long long LL;

int n, m;
int A[N][N], B[N][N];

struct State{
  int A[N];
};

LL encode(const State &s) {
  LL ans = 0;
  for (int i = m - 1; i >= 0; --i)
    ans = ans * (n + 1) + s.A[i];
  return ans;
}

State decode(LL x) {
  State s;
  for (int i = 0; i < m; ++i) {
    s.A[i] = x % (n + 1);
    x /= (n + 1);
  }
  return s;
}

std::map<LL, int> _f;
int f(LL x, bool player) {
  if (_f.count(x)) return _f[x];
  State s = decode(x);

  bool isFinal = true;
  for (int i = 0; i < m; ++i)
    if (s.A[i] < n) isFinal = false;
  if (isFinal) return _f[x] = 0;

  int &ans = _f[x];
  ans = player ? -INF : INF;
  for (int i = 0; i < m; ++i)
    if (s.A[i] < n && (i == 0 || s.A[i] + 1 <= s.A[i - 1])) {
      ++s.A[i];
      int ans2 = f(encode(s), !player)
                + (player ? A[s.A[i] - 1][i] : -B[s.A[i] - 1][i]);
      ans = player ? std::max(ans, ans2) : std::min(ans, ans2);
      --s.A[i];
    }

  return ans;
}

int main() {
  n = readInt(); m = readInt();
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      A[i][j] = readInt();
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      B[i][j] = readInt();
  printf("%d\n", f(0LL, true));
  return 0;
}

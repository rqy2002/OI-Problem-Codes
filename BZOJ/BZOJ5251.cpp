#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>

typedef std::set<int> SI;
typedef std::vector<int> VI;

inline int readInt() {
  int ans = 0, c, f = 1;
  while (!isdigit(c = getchar())) if (c == '-') f *= -1;
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getchar()));
  return ans * f;
}

const int N = 205;

int n, m;
int match[N], matchC[N];
int b[N], s[N], ans[N];
SI dui[N];
VI A[N][N];
bool visy[N];

bool dfs(int x, bool real = true) {
  int l = matchC[x] == 0 ? 1 : matchC[x];
  int r = matchC[x] == 0 ? m : matchC[x];
  for (int i = l; i <= r; ++i)
    for (VI::iterator it = A[x][i].begin(); it != A[x][i].end(); ++it) {
      int y = *it;
      if (visy[y]) continue;
      visy[y] = true;
      if (dui[y].size() < b[y]) {
        if (real) {
          match[x] = y;
          matchC[x] = i;
          dui[y].insert(x);
        }
        return true;
      }
      for (SI::iterator it2 = dui[y].begin(); it2 != dui[y].end(); ++it2)
        if (dfs(*it2, real)) {
          if (real) {
            dui[y].erase(it2);
            match[x] = y;
            matchC[x] = i;
            dui[y].insert(x);
          }
          return true;
        }
    }
  return false;
}

void init() {
  n = readInt();
  m = readInt();
  for (int i = 1; i <= m; ++i) {
    b[i] = readInt();
    dui[i].clear();
  }
  for (int i = 1; i <= n; ++i) {
    match[i] = matchC[i] = 0;
    ans[i] = 0;
    for (int j = 1; j <= m; ++j)
      A[i][j].clear();
    for (int j = 1; j <= m; ++j)
      A[i][readInt()].push_back(j);
  }
  for (int i = 1; i <= n; ++i)
    s[i] = readInt();
}

int main() {
  int T;
  scanf("%d%*d", &T);
  while (T--) {
    init();
    for (int i = 1; i <= n; ++i) {
      for (int j = i; j <= n; ++j) {
        memset(visy, 0, sizeof visy);
        int tm = m; m = s[j];
        if (dfs(j, false)) ans[j] = i;
        m = tm;
      }
      memset(visy, 0, sizeof visy);
      dfs(i);
      printf("%d ", matchC[i] == 0 ? m + 1 : matchC[i]);
    }
    puts("");
    for (int i = 1; i <= n; ++i)
      printf("%d ", i - ans[i]);
    puts("");
  }
  return 0;
}

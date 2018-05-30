#include <cstdio>
#include <cstring>
#include <vector>
const int M = 200050;
int cnt;
int ans[M];
std::vector<int> G[M * 2];
int deletetime[M * 2];
int del[M * 2];
int f[M * 2];
int Find(int x) { return (f[x] >= 0) ? (f[x] = Find(f[x])) : x; }
void Union(int x, int y) {
  int xx = Find(x), yy = Find(y);
  if (xx != yy) {
    f[xx] = yy;
    --cnt;
  }
}
void Union(int x) {
  for (int i = G[x].size() - 1; i >= 0; --i)
    if (deletetime[G[x][i]] <= deletetime[x]) Union(x, G[x][i]);
}
int main() {
  int n, m, x, y;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &x, &y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  int k;
  scanf("%d", &k);
  for (int i = 0; i < k; ++i) {
    scanf("%d", &del[i]);
    deletetime[del[i]] = k - i;
  }
  cnt = n;
  memset(f, -1, sizeof f);
  for (int i = 0; i < n; ++i)
    if (!deletetime[i]) Union(i);
  ans[k] = cnt - k;
  for (int i = k - 1; i >= 0; --i) {
    Union(del[i]);
    ans[i] = cnt - i;
  }
  for (int i = 0; i <= k; ++i) printf("%d\n", ans[i]);
  return 0;
}

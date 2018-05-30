#include <algorithm>
#include <cstdio>
using std::abs;
using std::min;
const int N = 1050;
const int INF = 100000000;
int f[6][N][N];
int a[6], b[6], c[6];
int sa[6], sb[6], sc[6], sum;
const int v[6] = {100, 50, 20, 10, 5, 1};
int Ta, Tb, Tc;
int dfs(int k, int aa, int bb) {
  if (k == 6) return aa == Ta && bb == Tb ? 0 : INF;
  int cc = sum - aa - bb;
  if (aa - Ta > sa[k] || bb - Tb > sb[k] || cc - Tc > sc[k])
    return INF;
  if (~f[k][aa][bb]) return f[k][aa][bb];
  int &ans = f[k][aa][bb];
  ans = INF;
  for (int lac = 0; lac <= a[k]; ++lac)
    for (int lbc = 0; lbc <= b[k]; ++lbc)
      ans = min(ans, dfs(k + 1, aa - lac * v[k], bb - lbc * v[k]) + abs(lac) + abs(lbc));
  for (int lab = 0; lab <= a[k]; ++lab)
    for (int lcb = 0; lcb <= c[k]; ++lcb)
      ans = min(ans, dfs(k + 1, aa - lab * v[k], bb + (lab + lcb) * v[k]) + abs(lab) + abs(lcb));
  for (int lba = 0; lba <= b[k]; ++lba)
    for (int lca = 0; lca <= c[k]; ++lca)
      ans = min(ans, dfs(k + 1, aa + (lba + lca) * v[k], bb - lba * v[k]) + abs(lba) + abs(lca));
  for (int lac = 0; lac <= c[k]; ++lac)
    for (int lbc = 0; lbc + lac <= c[k]; ++lbc)
      ans = min(ans, dfs(k + 1, aa + lac * v[k], bb + lbc * v[k]) + abs(lac) + abs(lbc));
  for (int lab = 0; lab <= b[k]; ++lab)
    for (int lcb = 0; lcb + lab <= b[k]; ++lcb)
      ans = min(ans, dfs(k + 1, aa + lab * v[k], bb - (lab + lcb) * v[k]) + abs(lab) + abs(lcb));
  for (int lba = 0; lba <= a[k]; ++lba)
    for (int lca = 0; lca + lba <= a[k]; ++lca)
      ans = min(ans, dfs(k + 1, aa - (lba + lca) * v[k], bb + lba * v[k]) + abs(lba) + abs(lca));
  return ans;
}
int main() {
  int gab, gbc, gca;
  scanf("%d%d%d", &gab, &gbc, &gca);
  for (int i = 0; i < 6; ++i) scanf("%d", &a[i]);
  for (int i = 0; i < 6; ++i) scanf("%d", &b[i]);
  for (int i = 0; i < 6; ++i) scanf("%d", &c[i]);
  sa[5] = a[5];
  for (int i = 4; ~i; --i) sa[i] = sa[i + 1] + a[i] * v[i];
  sb[5] = b[5];
  for (int i = 4; ~i; --i) sb[i] = sb[i + 1] + b[i] * v[i];
  sc[5] = c[5];
  for (int i = 4; ~i; --i) sc[i] = sc[i + 1] + c[i] * v[i];
  Ta = sa[0] - gab + gca;
  Tb = sb[0] - gbc + gab;
  Tc = sc[0] - gca + gbc;
  if (Ta < 0 || Tb < 0 || Tc < 0) return puts("impossible"), 0;
  std::fill(f[0][0], f[6][0], -1);
  int ans = dfs(0, sa[0], sb[0]);
  if (ans > 1000) return puts("impossible"), 0;
  printf("%d\n", ans);
  return 0;
}

#include <algorithm>
#include <cstdio>
const int K = 11;
const int mod = 20110520;
const int pow3[K + 4] = {
  1, 3, 9, 27, 81, 243,
  729, 2187, 6561, 19683,
  59049, 177147, 531441, 1594323
};
bool P[105][K];
int _f[2][1000000];
char ss[105];
inline int get(int S, int y) {
  return S / pow3[y] % 3;
}
int main() {
  int r, c;
  scanf("%d%d", &r, &c);
  for (int i = 0; i < r; ++i) {
    scanf("%s", ss);
    for (int j = 0; j < c; ++j)
      (r > c ? P[i][j] : P[j][i]) = (ss[j] == '*');
  }
  if (r < c) std::swap(r, c);
  int *f = _f[0], *g = _f[1];
  f[0] = 1;
  for (int i = 0; i < r; ++i)
    for (int j = 0; j < c; ++j) {
      std::fill(g, g + pow3[c + 1], 0);
      for (int last = 0; last < pow3[c + 1]; ++last) {
        int a = get(last, c), b = get(last, 0);
        if (!j && b) continue;
        int S2 = last % pow3[c] / 3 * 9;
#define upd(u, v) (g[S2 + u * 3 + v] += f[last]) %= mod
        if (P[i][j]) { if (!a && !b) upd(0, 0); }
        else switch (a * 3 + b) {
          case 0:
            upd(0, 1); upd(1, 0); upd(2, 2);
            break;
          case 1:
            upd(0, 1); upd(2, 0);
            break;
          case 2:
            upd(0, 2); upd(0, 0);
            break;
          case 3:
            upd(1, 0); upd(0, 2);
            break;
          case 4:
            upd(0, 0);
            break;
          case 6:
            upd(2, 0); upd(0, 0);
            break;
        }
      }
      std::swap(f, g);
    }
  printf("%d\n", f[0]);
  return 0;
}

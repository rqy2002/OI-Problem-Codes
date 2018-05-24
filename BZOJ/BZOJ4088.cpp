#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 105;
typedef int VC[N][N][N];
int n, m, H[N][N], top[N * 2][N * 2];
VC R, G, B;
char s[3][4];

inline VC& GetVC(char c) {
  if (c == 'R') return R;
  else if (c == 'G') return G;
  else return B;
}

inline void chk(int &a, int b) { a = std::max(a, b); }

inline int& Top(int i, int j, int h, int di, int dj) {
  int a = i + (di < 0 ? di * (h - 100) : di * h);
  int b = j + (dj < 0 ? dj * (h - 100) : dj * h);
  return top[a][b];
}

void Solve2(VC &T, int di, int dj,
    int a0, int a1, int a2, int b0, int b1, int b2) {
#define TOP(i, j, h) (Top((i), (j), (h), di, dj))
  memset(top, 0, sizeof top);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      for (int h = 1; h <= H[i][j]; ++h) {
        chk(TOP(i, j, h), 3 * h + 2);
        chk(TOP(i - di, j, h), 3 * h + 1);
        chk(TOP(i - di, j - dj, h), 3 * h + 0);
      }
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      for (int h = 1; h <= H[i][j]; ++h) {
        if (TOP(i, j, h) == 3 * h + 2) T[i][j][h] |= a0;
        if (TOP(i - di, j, h) == 3 * h + 1) T[i][j][h] |= a1;
        if (TOP(i - di, j - dj, h) == 3 * h + 0) T[i][j][h] |= a2;
      }
  memset(top, 0, sizeof top);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      for (int h = 1; h <= H[i][j]; ++h) {
        chk(TOP(i, j, h), 3 * h + 2);
        chk(TOP(i, j - dj, h), 3 * h + 1);
        chk(TOP(i - di, j - dj, h), 3 * h + 0);
      }
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      for (int h = 1; h <= H[i][j]; ++h) {
        if (TOP(i, j, h) == 3 * h + 2) T[i][j][h] |= b0;
        if (TOP(i, j - dj, h) == 3 * h + 1) T[i][j][h] |= b1;
        if (TOP(i - di, j - dj, h) == 3 * h + 0) T[i][j][h] |= b2;
      }
#undef TOP
}

void Solve1(VC &T, int di, int dj, int a0, int a1) {
#define TOP(i, j, h) (Top((i), (j), (h), di, dj))
  memset(top, 0, sizeof top);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      for (int h = 1; h <= H[i][j]; ++h) {
        chk(TOP(i, j, h), 2 * h + 1);
        chk(TOP(i - di, j - dj, h), 2 * h + 0);
      }
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      for (int h = 1; h <= H[i][j]; ++h) {
        if (TOP(i, j, h) == 2 * h + 1) T[i][j][h] |= a0;
        if (TOP(i - di, j - dj, h) == 2 * h + 0) T[i][j][h] |= a1;
      }
#undef TOP
}

const char *format[13] = {
  "    +-------+",
  "   /d\\aaaa'/|",
  "  /dd.*'bb/i|",
  " /.cccc\\b/i/|",
  "+-------+i.j|",
  "|\\eeeee/|\\:j|",
  "|h\\eee/f|l*j|",
  "|hh\\e/ff|l:\\|",
  "|hhhXfff|l'k+",
  "|hh/g\\ff|/k/",
  "|h/ggg\\f|k/",
  "|/ggggg\\|/",
  "+-------+"
};

int len[N * 30];
char ans[N * 30][N * 30];

void Show() {
  int a = -10000, b = -10000;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      a = std::max(a, 8 * H[i][j] - 4 * i);
      b = std::max(b, 4 * i - 8 * j);
    }
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      for (int h = 1; h <= H[i][j]; ++h) {
        int x = a - 8 * h + 4 * i, y = b - 4 * i + 8 * j;
        for (int u = 0; u < 13; ++u)
          for (int v = 0; format[u][v] != '\0'; ++v) {
            if (format[u][v] == ' ') continue;
            else if (format[u][v] >= 'a' && format[u][v] <= 'l') {
              int t = format[u][v] - 'a';
              char c = "KRGYBPCW"[((R[i][j][h] >> t) & 1)
                                | (((G[i][j][h] >> t) & 1) << 1)
                                | (((B[i][j][h] >> t) & 1) << 2)];
              ans[x + u][y + v] = c;
            } else
              ans[x + u][y + v] = format[u][v];
            chk(len[x + u], y + v + 1);
          }
      }
  for (int i = 0; len[i]; ++i) {
    for (int j = 0; j < len[i]; ++j)
      if (ans[i][j] == '\0') ans[i][j] = ' ';
    ans[i][len[i]] = '\0';
    puts(ans[i]);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      scanf("%d", &H[i][j]);

  scanf("%s%s%s", s[0], s[1], s[2]);

  if (s[0][0] != '*')
    Solve2(GetVC(s[0][0]), 1, 1, 12, 0, 0, 3, 0, 0);
  if (s[0][1] != '*')
    Solve1(GetVC(s[0][1]), 1, 0, 15, 0);
  if (s[0][2] != '*')
    Solve2(GetVC(s[0][2]), 1, -1, 6, 0, 1536, 9, 2304, 0);
  if (s[1][0] != '*')
    Solve1(GetVC(s[1][0]), 0, 1, 15, 0);
  if (s[1][1] != '*')
    Solve1(GetVC(s[1][1]), 0, 0, 15, 0);
  if (s[1][2] != '*')
    Solve1(GetVC(s[1][2]), 0, -1, 15, 3840);
  if (s[2][0] != '*')
    Solve2(GetVC(s[2][0]), -1, 1, 9, 48, 0, 6, 0, 192);
  if (s[2][1] != '*')
    Solve1(GetVC(s[2][1]), -1, 0, 15, 240);
  if (s[2][2] != '*')
    Solve2(GetVC(s[2][2]), -1, -1, 3, 144, 3072, 12, 768, 96);

  Show();

  return 0;
}

#include <cstdio>
#include <cstring>
#include <queue>
const int MAXN = 10000;
const int mod = 10007;
int ch[MAXN][26], cnt, match[MAXN];
int fail[MAXN];
char s[1000];
void addstring() {
  int r = 0;
  for (int i = 0; s[i] != '\0'; ++i) {
    if (!ch[r][s[i] - 'A']) match[ch[r][s[i] - 'A'] = cnt++] = false;
    r = ch[r][s[i] - 'A'];
  }
  match[r] = true;
}
std::queue<int> Q;
void getfail() {
  while (!Q.empty()) Q.pop();
  fail[0] = 0;
  for (int i = 0; i < 26; ++i)
    if (ch[0][i]) {
      fail[ch[0][i]] = 0;
      Q.push(ch[0][i]);
    }
  while (!Q.empty()) {
    int x = Q.front();
    Q.pop();
    for (int i = 0; i < 26; ++i)
      if (ch[x][i]) {
        match[ch[x][i]] |= match[ch[fail[x]][i]];
        fail[ch[x][i]] = ch[fail[x]][i];
        Q.push(ch[x][i]);
      } else {
        ch[x][i] = ch[fail[x]][i];
      }
  }
}
int f[MAXN][105];
int solve(int x, int k) {
  if (match[x]) return 0;
  if (!k) return 1;
  if (f[x][k] >= 0) return f[x][k];
  int &ans = f[x][k];
  ans = 0;
  for (int i = 0; i < 26; ++i) ans = (ans + solve(ch[x][i], k - 1)) % mod;
  return ans;
}
int main() {
  int n, m;
  cnt = 1;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%s", s);
    addstring();
  }
  getfail();
  int ans = 1;
  for (int i = 0; i < m; ++i) ans = ans * 26 % mod;
  memset(f, -1, sizeof f);
  printf("%d", (ans - solve(0, m) + mod) % mod);
  return 0;
}

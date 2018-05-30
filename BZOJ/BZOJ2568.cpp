#include <algorithm>
#include <cstdio>
#include <set>
typedef long long LL;
const int mod = 1000000009;
inline int lowbit(int x) { return x & -x; }
const int N = 1 << 16;
int s[16][N];
void add(int a, int k, int x) {
  for (++k; k <= N; k += lowbit(k))
    s[a][k] += x;
}
int query(int a, int k) {
  int ans = 0;
  for (++k; k; k -= lowbit(k)) ans += s[a][k];
  return ans;
}
std::multiset<int> S;
int main() {
  int m, x, cnt = 0, num = 0;
  scanf("%d", &m);
  char s[10];
  while (m--) {
    scanf("%s%d", s, &x);
    if (*s == 'I') {
      ++num;
      S.insert(x -= cnt);
      for (int i = 0; i < 16; ++i) add(i, ((1 << (i + 1)) - 1) & x, 1);
    } else if (*s == 'D') {
      int l = S.count(x -= cnt);
      num -= l;
      S.erase(x);
      for (int i = 0; i < 16; ++i) add(i, ((1 << (i + 1)) - 1) & x, -l);
    } else if (*s == 'A') {
      cnt += x;
    } else {
      int r = ((1 << x) - cnt - 1) & ((1 << (x + 1)) - 1), l = (-cnt) & ((1 << (x + 1)) - 1);
      if (r >= l)
        printf("%d\n", num - query(x, r) + query(x, l - 1));
      else
        printf("%d\n", query(x, l - 1) - query(x, r));
    }
  }
  return 0;
}

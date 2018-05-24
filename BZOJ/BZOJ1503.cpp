/**************************************************************
 * Problem: BZOJ1503
 * Author: Rqy
 * Date: 2017 Dec 20
 * Algorithm: Treap
**************************************************************/
#include <cstdio>
#include <cstdlib>
const int N = 100050;
int root = 0, val[N], key[N], count[N], ch[N][2], siz[N], cnt = 0;
void maintain(int o) { siz[o] = siz[ch[o][0]] + siz[ch[o][1]] + count[o]; }
void rotate(int &o, int d) {
  int t = ch[o][d];
  ch[o][d] = ch[t][d ^ 1];
  maintain(ch[t][d ^ 1] = o);
  maintain(o = t);
}
int rm(int &o, int t) {
  if (!o) return 0;
  if (val[o] < t) {
    int ans = count[o] + siz[ch[o][0]];
    return ans + rm(o = ch[o][1], t);
  }
  else {
    int ans = rm(ch[o][0], t);
    maintain(o);
    return ans;
  }
}
void insert(int &o, int t) {
  if (!o) {
    val[o = ++cnt] = t;
    siz[o] = count[o] = 1;
    ch[o][0] = ch[o][1] = 0;
    key[o] = rand();
  } else if (val[o] == t)
    ++count[o];
  else {
    int d = val[o] < t;
    insert(ch[o][d], t);
    if (key[ch[o][d]] > key[o]) rotate(o, d);
  }
  maintain(o);
}
int query(int o, int k) {
  if (siz[ch[o][1]] >= k) return query(ch[o][1], k);
  else if (siz[ch[o][1]] + count[o] >= k) return val[o];
  else return query(ch[o][0], k - siz[ch[o][1]] - count[o]);
}
char s[10];
int main() {
  int n, x, add = 0, ans = 0, min;
  scanf("%d%d", &n, &min);
  for (int i = 0; i < n; ++i) {
    scanf("%s%d", s, &x);
    if (*s == 'I') { if (x >= min) insert(root, x - add); }
    else if (*s == 'S') ans += rm(root, min - (add -= x));
    else if (*s == 'A') add += x;
    else if (siz[root] < x) printf("-1\n");
    else printf("%d\n", query(root, x) + add);
  }
  printf("%d\n", ans);
  return 0;
}

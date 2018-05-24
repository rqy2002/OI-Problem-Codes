/**************************************************************
 * Problem: Luogu P2048
 * Author: Rqy
 * Date: 2017 Dec 28
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <queue>
const int N = 500050;
typedef long long LL;
int minv[20][N], mini[20][N];
int n, S[N], t2[N];
void buildST() {
  for (int i = 0; i < n; ++i) {
    minv[0][i] = S[i];
    mini[0][i] = i;
  }
  for (int k = 1; k < 20; ++k) {
    int h = 1 << (k - 1);
    for (int i = 0, j = h; j < n; ++i, ++j) {
      if (minv[k - 1][i] < minv[k - 1][j]) {
        minv[k][i] = minv[k - 1][i];
        mini[k][i] = mini[k - 1][i];
      } else {
        minv[k][i] = minv[k - 1][j];
        mini[k][i] = mini[k - 1][j];
      }
    }
  }
}
int query(int l, int r) {
  int k = t2[r - l + 1];
  r = r - (1 << k) + 1;
  if (minv[k][l] < minv[k][r]) return mini[k][l];
  else return mini[k][r];
}
struct Node{
  int ll, lr, tl, v, rv;
  Node(int ll, int lr, int rv) : ll(ll), lr(lr), rv(rv) {
    tl = query(ll, lr);
    v = rv - S[tl];
  }
  bool operator<(const Node &t)const{
    return v < t.v;
  }
};
std::priority_queue<Node> PQ;
int main() {
  for (int i = 0; (1 << i) < N; ++i)
    for (int j = 0; j < (1 << i) && j + (1 << i) < N; ++j)
      t2[j + (1 << i)] = i;
  int k, l, r;
  scanf("%d%d%d%d", &n, &k, &l, &r);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &S[i]);
    if (i) S[i] += S[i - 1];
  }
  buildST();
  while (!PQ.empty()) PQ.pop();
  for (int i = l; i <= n; ++i)
    PQ.push(Node(std::max(0, i - r), i - l, S[i]));
  LL ans = 0;
  while (k--) {
    Node x = PQ.top();
    PQ.pop();
    ans += x.v;
    if (x.tl > x.ll) PQ.push(Node(x.ll, x.tl - 1, x.rv));
    if (x.tl < x.lr) PQ.push(Node(x.tl + 1, x.lr, x.rv));
  }
  printf("%lld\n", ans);
  return 0;
}

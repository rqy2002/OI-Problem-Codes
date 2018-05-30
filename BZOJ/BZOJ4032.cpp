#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <queue>
const int N = 4050;
struct Node{
  int nxt[26], pa, len;
};
struct Automation{
  Node nodes[N];
  int cnt;
  inline int newNode(int l = 0) {
    memcpy(&nodes[cnt].nxt, &nodes[l].nxt, sizeof(int) * 26);
    nodes[cnt].pa = nodes[l].pa;
    nodes[cnt].len = nodes[l].len;
    return cnt++;
  }
  int root;
  int seq_last[26], last;
  void init() {
    memset(&nodes[0], 0, sizeof(Node));
    cnt = 1;
    root = newNode();
    for (int i = 0; i < 26; ++i)
      seq_last[i] = root;
    last = root;
  }
  void seq_append(int x) {
    int ne = newNode();
    for (int i = 0; i < 26; ++i)
      for (int q = seq_last[i]; q && !nodes[q].nxt[x]; q = nodes[q].pa)
        nodes[q].nxt[x] = ne;
    nodes[ne].pa = seq_last[x];
    seq_last[x] = ne;
  }
  void suffix_append(int x) {
    int ne = newNode();
    nodes[ne].len = nodes[last].len + 1;
    int q = last;
    while (q && !nodes[q].nxt[x]) {
      nodes[q].nxt[x] = ne;
      q = nodes[q].pa;
    }
    if (!q) {
      nodes[last = ne].pa = root;
      return;
    }
    int p = nodes[q].nxt[x];
    if (nodes[p].len == nodes[q].len + 1) {
      nodes[last = ne].pa = p;
      return;
    }
    int pq = newNode(p);
    nodes[pq].len = nodes[q].len + 1;
    nodes[last = ne].pa = nodes[p].pa = pq;
    while (q && nodes[q].nxt[x] == p) {
      nodes[q].nxt[x] = pq;
      q = nodes[q].pa;
    }
  }
};
struct AAA{
  int x, y, len;
  AAA(int a, int b, int c) : x(a), y(b), len(c) {}
};
std::bitset<N> vis[N];
std::queue<AAA> Q;
int bfs(const Automation &A, const Automation &B) {
  while (!Q.empty()) Q.pop();
  Q.push(AAA(A.root, B.root, 0));
  for (int i = 0; i < A.cnt; ++i)
    vis[i].reset();
  vis[A.root][B.root] = 1;
  while (!Q.empty()) {
    AAA x = Q.front(); Q.pop();
    const Node &a = A.nodes[x.x], &b = B.nodes[x.y];
    for (int i = 0; i < 26; ++i) {
      int l = a.nxt[i], r = b.nxt[i];
      if (!l) continue;
      if (!r) return x.len + 1;
      if (!vis[l][r]) Q.push(AAA(l, r, x.len + 1));
      vis[l][r] = 1;
    }
  }
  return -1;
}
Automation a, b;
char s[N], p[N];
int main() {
  scanf("%s%s", s, p);
  a.init();
  for (char *r = s; *r; ++r)
    a.suffix_append(*r - 'a');
  b.init();
  for (char *r = p; *r; ++r)
    b.suffix_append(*r - 'a');
  printf("%d\n", bfs(a, b));
  b.init();
  for (char *r = p; *r; ++r)
    b.seq_append(*r - 'a');
  printf("%d\n", bfs(a, b));
  a.init();
  for (char *r = s; *r; ++r)
    a.seq_append(*r - 'a');
  int ans4 = bfs(a, b);
  b.init();
  for (char *r = p; *r; ++r)
    b.suffix_append(*r - 'a');
  printf("%d\n", bfs(a, b));
  printf("%d\n", ans4);
  return 0;
}

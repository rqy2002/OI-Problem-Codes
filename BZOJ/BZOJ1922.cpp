#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm> 
typedef long long LL;
struct HeapNode{
  int num;
  LL dist;
  inline bool operator < (const HeapNode &x) const {
    return dist > x.dist;
  }
};
struct Edge{
  int to;
  LL dist;
};
using std::vector;
const int N = 4010, M = 70010;
int n, m;
vector<int> protect[N];
vector<Edge> G[N];
int protector[N];
LL dis[N];
std::priority_queue<HeapNode> heap;
LL Dijkstra() {
  while (!heap.empty()) heap.pop();
  std::fill(dis + 2, dis + n + 1, 100000000000000LL);
  dis[1] = 0;
  heap.push((HeapNode){1, 0});
  while (!heap.empty()) {
    HeapNode u = heap.top(); heap.pop();
    if (u.dist != dis[u.num]) continue;
    if (u.num == n) return u.dist;
    for (vector<int>::iterator i = protect[u.num].begin(); i != protect[u.num].end(); ++i)
      if (--protector[*i] == 0)
        heap.push((HeapNode){*i, dis[*i] = std::max(dis[*i], u.dist)});
    for (vector<Edge>::iterator i = G[u.num].begin(); i != G[u.num].end(); ++i) {
      if (dis[i->to] > u.dist + i->dist) {
        dis[i->to] = u.dist + i->dist;
        if (!protector[i->to])
          heap.push((HeapNode){i->to, dis[i->to]});
      }
    }
  }
}
int main() {
  scanf("%d%d", &n, &m);
  int i, x, y, z;
  for (i = 0; i < m; ++i) {
    scanf("%d%d%d", &x, &y, &z);
    G[x].push_back((Edge){y, (LL)z});
  }
  for (i = 1; i <= n; ++i) {
    scanf("%d", &protector[i]);
    for (x = 0; x < protector[i]; ++x) {
      scanf("%d", &y);
      protect[y].push_back(i);
    }
  }
  printf("%lld", Dijkstra());
  return 0;
}

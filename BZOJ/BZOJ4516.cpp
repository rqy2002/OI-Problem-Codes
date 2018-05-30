#include<cstdio>
#include<map>
using namespace std;
typedef long long LL;
const int MAXN = 100010;
struct Node{;
	int len;
	int pre;
	Node(int p = 0, int l = 0): pre(p), len(l)
	{
	}
	Node(const Node &q): pre(q.pre), len(q.len)
	{}
	const Node& operator = (const Node &q)
	{
		pre = q.pre;
		len = q.len;
		return *this;
	}
}nodes[MAXN * 2];
map<int, int> children[MAXN * 2];
int num = 0;
int last, root;
void attend(int);
int newNode(int p = 0, int l = 0)
{
	children[++num].clear();
	nodes[num] = Node(p, l);
	return num;
}
int copyNode(int q)
{
	children[++num] = children[q];
	nodes[num] = nodes[q];
	return num;
}
int main()
{
	root = last = newNode();
	int n, x;
	scanf("%d", &n);
	LL ans = 0;
	while(n--)
	{
		scanf("%d", &x);
		attend(x);
		ans += nodes[last].len - nodes[nodes[last].pre].len;
		printf("%lld\n", ans); 
	}
	//for(int i = 0; i <= num; i++)
	//{
	//	printf("%d %d\n", nodes[i].pre, nodes[i].len);
	//}
	return 0;
}
void attend(int c)
{
	int np = newNode(last, nodes[last].len + 1);
	int p;
	for(p = last; p && !children[p].count(c); p = nodes[p].pre)
		children[p][c] = np;
	if(!p)
	{
		nodes[np].pre = root;
		last = np;
		return;
	}
	int q = children[p][c];
	if(nodes[q].len == nodes[p].len + 1)
	{
		nodes[np].pre = q;
		last = np;
		return;
	}
	int nq = copyNode(q);
	nodes[nq].len = nodes[p].len + 1;
	nodes[np].pre = nodes[q].pre = nq;
	for(; p && (children[p][c] == q); p = nodes[p].pre)
		children[p][c] = nq;
	last = np;
	return;
}

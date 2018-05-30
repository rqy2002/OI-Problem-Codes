#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
typedef long long LL;
const LL INF = 20000000000000000;
const int maxn = 210;
int n;
LL A[maxn], B[maxn], C[maxn];
struct MaxFlowWhenValueIsNotLessThanZero{
	struct Edge{
		int from, to;
		LL flow, cap, cost;
		Edge* next;
		Edge* fan;
		Edge():from(-1), to(-1), flow(0), cap(0), cost(0)
		{}
		Edge(int f, int t, LL c, LL co, Edge *ne):
			from(f), to(t), flow(0), cap(c), cost(co), next(ne)
		{}
	};
	Edge* pre[maxn];
	MaxFlowWhenValueIsNotLessThanZero()
	{
		memset(pre, 0, sizeof(pre));
	}
	void addedge(int from, int to, LL cap, LL cost)
	{
		pre[from] = new Edge(from, to, cap, cost, pre[from]);
		pre[to] = new Edge(to, from, 0, -cost, pre[to]);
		pre[from]->fan = pre[to];
		pre[to]->fan = pre[from];
	}
	LL dis[maxn], minflow[maxn];
	Edge* par[maxn];
	std::queue<int> Q;
	bool InQ[maxn];
	bool visited[maxn];
	bool SPFA(int s, int t)
	{
		while(!Q.empty()) Q.pop();
		memset(visited, 0, sizeof(visited));
		memset(InQ, 0, sizeof(InQ));
		dis[s] = 0;
		par[s] = NULL;
		visited[s] = true;
		minflow[s] = INF; 
		Q.push(s);
		while(!Q.empty())
		{
			int u = Q.front();
			Q.pop();
			InQ[u] = false;
			for(Edge *i = pre[u]; i; i = i->next) if(i->cap > i->flow)
			{
				int v = i->to;
				if(!visited[v] || i->cost + dis[u] > dis[v])
				{
					par[v] = i;
					minflow[v] = std::min(minflow[u], i->cap - i->flow);
					if(!InQ[v])
					{
						InQ[v] = true;
						Q.push(v);
					}
					visited[v] = true;
					dis[v] = i->cost + dis[u];
				}
			}
		}
		return visited[t];
	}
	LL solve(int s, int t)
	{
		LL ans = 0, sum = 0;
		while(SPFA(s, t))
		{
			LL flow = minflow[t];
			if(dis[t] < 0)
				flow = std::min(flow, -sum / dis[t]);
			int l = t;
			while(l != s)
			{
				par[l]->flow += flow;
				par[l]->fan->flow -= flow;
				l = par[l]->from;
			}
			sum += flow * dis[t];
			ans += flow;
			if(sum < -dis[t])
				return ans;
		}
		return ans;
	}
};

MaxFlowWhenValueIsNotLessThanZero solver;
const int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
bool isprime(int x)
{
	if(x == 1) return false;
	for(int i = 0; i < 15; i++)
	{
		if(x == prime[i]) return true;
		LL ans = 1, p = prime[i], t = x - 1;
		for(; t; t >>= 1, p = p * p % x)
			if(t & 1) ans = ans * p % x;
		if(ans != 1) return false;
	}
	return true;
}
int lr[maxn];
bool con[maxn][maxn];
void dfs(int u)
{
	for(int v = 0; v < n; v++) if(con[u][v] && !lr[v])
	{
		lr[v] = 3 - lr[u];
		dfs(v);
	}
}
int main()
{
	//freopen("c.in", "r", stdin);
	//freopen("d.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%lld", A + i);
	for(int i = 0; i < n; i++) scanf("%lld", B + i);
	for(int i = 0; i < n; i++) scanf("%lld", C + i);
	memset(lr, 0, sizeof(lr));
	for(int i = 0; i < n; i++) 
		for(int j = i + 1; j < n; j++)
			con[j][i] = con[i][j] = (A[i] > A[j]) 
						? (A[i] % A[j] == 0 && isprime(A[i] / A[j])) 
						: (A[j] % A[i] == 0 && isprime(A[j] / A[i]));
	for(int i = 0; i < n; i++) if(!lr[i])
	{
		lr[i] = 1;
		dfs(i);
	}
	for(int i = 0; i < n; i++) 
	{
		if(lr[i] == 1)
			solver.addedge(n, i, B[i], 0);
		else
			solver.addedge(i, n + 1, B[i], 0);
	}
	for(int i = 0; i < n; i++) 
		for(int j = i + 1; j < n; j++)
			if(con[i][j])
			{
				if(lr[i] == 1)
					solver.addedge(i, j, std::max(B[i], B[j]), C[i] * C[j]);
				else
					solver.addedge(j, i, std::max(B[i], B[j]), C[i] * C[j]);
			}
	printf("%lld", solver.solve(n, n + 1));
	return 0;
}

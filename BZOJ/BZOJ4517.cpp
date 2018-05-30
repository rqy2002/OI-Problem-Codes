#include<cstdio>
typedef long long LL;
const int mod = 1E9 + 7;
int D[1000005];
int f[1000005];
int f2[1000005];
int mul(int a, int b)
{
	if(!a) return 1;
	int ans = mul(a / 2, b);
	ans = (LL)ans * ans % mod;
	if(a & 1)
		ans = (LL)ans * b % mod;
	return ans;
}
int main()
{
	D[0] = 1;
	D[1] = 0;
	f[0] = f[1] = 1;
	for(int i = 2; i <= 1000000; i++)
	{
		f[i] = (LL)f[i-1] * i % mod;
		D[i] = (LL)(i-1) * ((LL)D[i-1] + D[i-2] % mod) % mod; 
	}
	f2[1000000] = mul(mod - 2, f[1000000]);
	for(int i = 999999; i >= 0; i--)
	{
		f2[i] = (LL)f2[i+1] * (i + 1) % mod;
	}
	int T, n, m;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d%d", &n, &m);
		printf("%d\n", (int)(((LL)f[n] * f2[m] % mod * f2[n-m] % mod) * D[n-m] % mod));
	}
	return 0;
}

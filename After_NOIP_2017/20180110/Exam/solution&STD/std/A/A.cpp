#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <queue>
using namespace std;
typedef long long LL;
#define For(i,a,b) for (int i = (a); i <= (b); i++)
#define Cor(i,a,b) for (int i = (a); i >= (b); i--)
#define rep(i,a) for (int i = 0; i < a; i++)
#define Fill(a,b) memset(a,b,sizeof(a))
const int maxn = 500010;
const int maxm = 1e6 + 10;
const int inf = 1e9;
struct node
{
	int v, id, p;
}P[maxn];
int n, m;
int f[maxn];
void init()
{
	scanf("%d%d", &n, &m);
	For(i, 1, n)
		scanf("%d", &P[i].v), P[i].id = i, P[i].p = f[i] = inf;
	rep(i, m)
	{
		int x;
		scanf("%d", &x);
		if (P[x].p == inf)
			P[x].p = f[x] = i;
	}
}
struct BIT
{
	int val[maxm];
	void add(int x, int v)
	{
		for (int i = x; i < maxm; i += i & (-i))
			val[i] += v;
	}
	int ask(int x)
	{
		int ret = 0;
		for (int i = x; i; i -= i & (-i))
			ret += val[i];
		return ret;
	}
}b;
int g[maxn];
LL F[maxn];
int mn[maxn<<2];
void up(int id,int l,int r,int v,int w)
{
    if(l==r){
        mn[id]=min(mn[id],w);return;
    }
    int mid=(l+r)>>1;
    if(v<=mid) up(id<<1,l,mid,v,w);
    else up(id<<1|1,mid+1,r,v,w);
    mn[id]=min(mn[id<<1],mn[id<<1|1]);
}
int q(int id,int l,int r,int tl,int tr)
{
    if(tl==l&&r==tr) return mn[id];
    int mid=(l+r)>>1;
    if(tr<=mid) return q(id<<1,l,mid,tl,tr);
    else if(tl>mid) return q(id<<1|1,mid+1,r,tl,tr);
    else return min(q(id<<1,l,mid,tl,mid),q(id<<1|1,mid+1,r,mid+1,tr));
}
int a[maxn];
map<int,int> mp;
void solve()
{
	LL ans = 0;
	Cor(i, n, 1)
	{
		g[i] = b.ask(P[i].v);
		b.add(P[i].v + 1, 1);
		ans += g[i];
		a[i]=P[i].v;
	}
	sort(a+1,a+1+n);
	int cnt=1;
	for(int i=1;i<=n;i++)
    {
        if(mp[a[i]]) continue;
        mp[a[i]]=cnt++;
    }
	printf("%lld\n", ans);
	memset(mn,127,sizeof(mn));
	for(int i=1;i<=n;i++)
    {
        P[i].v=mp[P[i].v];
        up(1,1,cnt,P[i].v,P[i].p);
        int t=q(1,1,cnt,P[i].v,cnt);
        if(t>m) continue;
        F[t]+=g[i];
    }
	rep(i, m)
	{
		ans -= F[i];
		printf("%lld\n", ans);
	}
}
int main()
{
	//freopen("A.in", "r", stdin);
	//freopen("A.out", "w", stdout);
	init();
	solve();
	return 0;
}

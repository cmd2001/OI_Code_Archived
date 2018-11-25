#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=5e2+1e1;
const int inf=1e8;
const double eps=1e-10;

struct point
{
	double x,y;
	point(double xx=0,double yy=0)
	{
		x=xx,y=yy;
	}
	friend point operator - (const point &a,const point &b)
	{
		return point(a.x-b.x,a.y-b.y);
	}
	friend double operator * (const point &a,const point &b)
	{
		return a.x*b.y-a.y*b.x;
	}
}tar[maxn],bss[maxn];

int dis[maxn][maxn],m,n;

bool line(point x,point y) // judge all target points in segment(x,y) or not
{
	if(x.x>y.x) swap(x,y);
	for(int i=1;i<=n;i++) if(tar[i].x<x.x||tar[i].x>y.x) return 0;
	if(x.y>y.y) swap(x,y);
	for(int i=1;i<=n;i++) if(tar[i].y<x.y||tar[i].y>y.y) return 0;
	return 1;
}
int judge(const point &x,const point &y) // x is the frist point , y is the second ?
{
	int abo,bel;
	abo=bel=0;
	double lam;
	for(int i=1;i<=n;i++)
	{
		lam=(y-x)*(tar[i]-x);
		if(lam>eps) ++abo;
		if(lam<-eps) ++bel;
		if(abo*bel) return 0; // not same side
	}
	if((!abo)&&(!bel)&&line(x,y)) // all points in a line
	{
		puts("2");
		return -1;
	}
	//if(abo&&bel) puts("Fuck you!");
	if(abo) return 1; // 1 means link x->y
	if(bel) return 2; // 2 means link y->x
	return 3;
}

inline void floyd()
{
	int ans=inf;
	for(int k=1;k<=m;k++)
		for(int i=1;i<=m;i++)
			if(dis[i][k]<inf)
				for(int j=1;j<=m;j++) dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	for(int i=1;i<=m;i++) ans=min(ans,dis[i][i]);
	if(ans>=inf||ans<=2) ans=-1;
	//debug<<"in floyd ans="<<ans<<endl;
	printf("%d\n",ans);
}

inline void link()
{
	int ret;
	for(int i=1;i<=m;i++)
	{
		for(int j=i+1;j<=m;j++)
		{
			ret=judge(bss[i],bss[j]);
			if(ret==-1) return;
			if(ret==1) dis[i][j]=1;
			else if(ret==2) dis[j][i]=1;
			else if(ret==3) dis[i][j]=dis[j][i]=1;
		}
	}
	floyd();
}

inline bool jil()
{
	for(int i=1;i<=m;i++) if(fabs(bss[i].x-bss[1].x)>eps||fabs(bss[i].y-bss[1].y)>eps) return 0;
	for(int i=1;i<=n;i++) if(fabs(tar[i].x-bss[1].x)>eps||fabs(tar[i].y-bss[1].y)>eps) return 0;
	puts("1");
	return 1;
}

int main()
{
	memset(dis,127/3,sizeof(dis));
	double k;
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++) scanf("%lf%lf%lf",&bss[i].x,&bss[i].y,&k);
	for(int i=1;i<=n;i++) scanf("%lf%lf%lf",&tar[i].x,&tar[i].y,&k);
	if(jil()) return 0;
	link();
	return 0;
}


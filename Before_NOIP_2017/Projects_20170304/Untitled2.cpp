#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const double eps=1e-8;
int cmp(const double a)
{
	if(fabs(a)<eps) return 0;
	return a>0?1:-1;
}
struct point
{
	double x,y;
	void in(const double &a,const double &b){x=a,y=b;}
}p[220];
struct node
{
	point a,b;
	void in(const point &m,const point &n){a=m,b=n;}
}in[110];
struct vec
{
	double dx,dy;
	void in(double m,double n){dx=m,dy=n;}
	friend double operator * (const vec &a,const vec &b) {return a.dx*b.dy-b.dx*a.dy;}
}v,v1,v2;
int t,n;
bool flag;
bool judge(const point &a,const point &b)
{
	if(cmp(a.x-b.x)==0&&cmp(a.y-b.y)==0) return 0;
	v.in(b.x-a.x,b.y-a.y);
	for(int i=1;i<=n;i++)
	{
		v1.in(in[i].a.x-a.x,in[i].a.y-a.y);v2.in(in[i].b.x-a.x,in[i].b.y-a.y);
		if(cmp((v*v1)*(v*v2))>0) return 0;
	}
	return 1;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		flag=0;
		double a,b,c,d;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
			p[i*2-1].in(a,b),p[i*2].in(c,d);
			in[i].in(p[i*2-1],p[i*2]);
		}
		for(int i=1;i<=2*n&&!flag;i++)
		{
			for(int j=i+1;j<=2*n&&!flag;j++)
			{
				flag=judge(p[i],p[j]);
			}
		}
		if(flag) printf("Yes!\n");
		else printf("No!\n");
	}
	return 0;
}
	


#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const double eps=1e-8;
int dcmp(double a)
{
    if(fabs(a)<eps) return 0;
    else return a>0?1:-1;
}
struct point
{
    double x,y;
    void in(const double &a,const double &b){x=a,y=b;}
}p[440];
struct node
{
    point a,b;
    void in(const double &x1,const double &y1,const double &x2,const double &y2){a.x=x1,a.y=y1,b.x=x2,b.y=y2;}
}in[220];
struct vec
{
    double dx,dy;
    friend double multi (const vec &a,const vec &b){return a.dx*b.dy-b.dx*a.dy;}
    void in(const double &x,const double &y){dx=x,dy=y;}
}v,v1,v2;
int t,n;
bool flag;
bool judge(const point &a,const point &b)
{
    if(dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0) return 0;
    const point &m=a;
    v.in(b.x-m.x,b.y-m.y);
    for(int i=1;i<=n;i++)
    {
        v1.in(in[i].a.x-m.x,in[i].a.y-m.y);v2.in(in[i].b.x-m.x,in[i].b.y-m.y);
        if(dcmp(multi(v,v1)*multi(v,v2))>0) return 0;
    }
    return 1;
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        double a,b,c,d;
        flag=0;
        memset(p,0,sizeof(p));
        memset(in,0,sizeof(in));
        scanf("%d",&n);
        if(n==1) flag=1;
        for(int i=1;i<=n;i++)
        {
            scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
            in[i].in(a,b,c,d);
            p[i*2-1].in(a,b);
            p[i*2].in(c,d);
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

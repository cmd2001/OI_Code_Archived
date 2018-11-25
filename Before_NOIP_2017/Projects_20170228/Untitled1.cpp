#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define debug cout
using namespace std;
const double eps=1e-8;
int dcmp(double a)
{
    if(fabs(a)<=eps) return 0;
    return a>0?1:-1;
}
struct node
{
    double xx1,xx2,yy1,yy2;
    double mxx,mix,mxy,miy;
    void calc(){mxx=max(xx1,xx2);mix=min(xx1,xx2);mxy=max(yy1,yy2);miy=min(yy1,yy2);}
}p1,p2;
struct vec
{
    double dx,dy;
    void in(double x,double y){dx=x;dy=y;}
    vec(){;}
    friend double operator *(const vec &a,const vec &b)
    {
        return a.dx*b.dy-b.dx*a.dy;
    }
}vec1,vec2,vec3;
struct point{double xx,yy;point(double x,double y){xx=x;yy=y;}point(){;}}p,pa,pb;
bool per_judge(const node &a,const node &b)
{
    return ((dcmp(a.mxx-b.mix)>=0)||(dcmp(b.mxx-a.mix)>=0))&&((dcmp(a.mxy-b.miy)>=0)||(dcmp(b.mxy-a.miy)>=0));
}
bool judge(const node &a,const node &b)
{
    vec1.in(a.xx2-a.xx1,a.yy2-a.yy1);
    vec2.in(b.xx1-a.xx1,b.yy1-a.yy1);
    vec3.in(b.xx2-a.xx1,b.yy2-a.yy1);
    return dcmp((vec1*vec2)*(vec1*vec3))<=0;
}//20170302 debuged
void calc(const node &a,const node &b)
{
    double s1,s2;;
    vec2.in(b.xx1-a.xx1,b.yy1-a.yy1);vec3.in(b.xx2-a.xx1,b.yy2-a.yy1);
    s1=fabs(vec2*vec3);
    vec2.in(b.xx1-a.xx2,b.yy1-a.yy2);vec3.in(b.xx2-a.xx2,b.yy2-a.yy2);
    s2=fabs(vec2*vec3);
    p.xx=a.xx1+s1*(a.xx2-a.xx1)/(s1+s2);
    p.yy=a.yy1+s1*(a.yy2-a.yy1)/(s1+s2);
    //debug<<p.xx<<" "<<p.yy<<endl;
}
double deri(const point &p,const point &pa)
{
    return fabs((pa.yy-p.yy)/(pa.xx-p.xx));
}//calc the derivation;
bool conver(const point &p,const point &pa,const point &pb)
{
    debug<<(pa.xx-p.xx)<<(pb.xx-p.xx)<<endl;
    debug<<dcmp((pa.xx-p.xx)*(pb.xx-p.xx))<<endl;
    if(dcmp((pa.xx-p.xx)*(pb.xx-p.xx))<=0) return 1;
    if(pa.yy>pb.yy&&dcmp(fabs(pa.xx-p.xx)-fabs(pb.xx-p.xx))>=0&&dcmp(deri(p,pa)-deri(p,pb))>=0) return 0;
    else if(pb.yy>pa.yy&&dcmp(fabs(pb.xx-p.xx)-fabs(pa.xx-p.xx))>=0&&dcmp(deri(p,pb)-deri(p,pa))>=0) return 0;
    return 1;
}
int main()
{
    int n;
    scanf("%d",&n);
    //debug<<n<<endl;
    for(int i=1;i<=n;i++)
    {
        scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&p1.xx1,&p1.yy1,&p1.xx2,&p1.yy2,&p2.xx1,&p2.yy1,&p2.xx2,&p2.yy2);
        p1.calc();p2.calc();
        if(p1.xx1==p1.xx2||p2.xx1==p2.xx2){puts("0.00");continue;}
        if(!per_judge(p1,p2)){puts("0.00");continue;}
        if(!judge(p1,p2)){puts("0.00");continue;}
        calc(p1,p2);
        if(p1.yy1>p1.yy2){pa.xx=p1.xx1,pa.yy=p1.yy1;} else{pa.xx=p1.xx2,pa.yy=p1.yy2;}
        if(p2.yy1>p2.yy2){pb.xx=p2.xx1,pb.yy=p2.yy1;} else{pb.xx=p2.xx2,pb.yy=p2.yy2;}
        /*debug<<pa.xx<<pa.yy<<pb.xx<<pb.yy<<endl;
        debug<<p.xx<<p.yy<<endl;
        debug<<"judging cover"<<endl;*/
        if(!conver(p,pa,pb)){puts("0.00");continue;}
        //debug<<"uncover"<<endl;
        if(pb.yy>pa.yy) swap(pa,pb);
        pb.xx=(pb.xx-p.xx)*pa.yy/pb.yy+p.xx;
        /*debug<<pa.xx<<pa.yy<<pb.xx<<pb.yy<<endl;
        debug<<p.xx<<p.yy<<endl;
        debug<<pa.xx-pb.xx<<pa.yy-p.yy<<endl;*/
        double ans=abs((pa.xx-pb.xx)*(pa.yy-p.yy))/2;
        printf("%.2f\n",ans);
    }
    return 0;
}











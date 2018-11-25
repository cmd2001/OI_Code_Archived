#include <iostream>  
#include <string.h>  
#include <stdio.h>  
#include <algorithm>  
#include <math.h>  
#define debug cout
  
using namespace std;  
const double eps=1e-8;  
  
struct Point  
{  
    double x,y;  
};  
  
Point p[100100];  
  
double dist(Point A,Point B)  
{  
    return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));  
}  
  
/***返回三角形的外心 */  
Point circumcenter(Point A,Point B,Point C)  
{  
    Point ret;  
    double a1=B.x-A.x,b1=B.y-A.y,c1=(a1*a1+b1*b1)/2;  
    double a2=C.x-A.x,b2=C.y-A.y,c2=(a2*a2+b2*b2)/2;  
    double d=a1*b2-a2*b1;  
    ret.x=A.x+(c1*b2-c2*b1)/d;  
    ret.y=A.y+(a1*c2-a2*c1)/d;  
    return ret;  
}  
  
/***c为圆心，r为半径 */  
void min_cover_circle(Point *p,int n,Point &c,double &r)  
{  
    random_shuffle(p,p+n);  
    c=p[0]; r=0;  
    for(int i=1;i<n;i++)  
    {  
        if(dist(p[i],c)>r+eps)   //第一个点  
        {  
            c=p[i]; r=0;  
            for(int j=0;j<i;j++)  
                if(dist(p[j],c)>r+eps)  //第二个点  
                {  
                    c.x=(p[i].x+p[j].x)/2;  
                    c.y=(p[i].y+p[j].y)/2;  
                    r=dist(p[j],c);  
                    for(int k=0;k<j;k++)  
                        if(dist(p[k],c)>r+eps)  //第三个点  
                        {   //求外接圆圆心，三点必不共线  
                            c=circumcenter(p[i],p[j],p[k]);  
                            r=dist(p[i],c);  
                        }  
                }  
        }  
    }  
}  
  
int main()  
{  
	freopen("dat.txt","r",stdin);
    int n;  
    Point c;  
    double r;  
    while(~scanf("%d",&n)&&n)  
    {  
        for(int i=0;i<n;i++)  
            scanf("%lf%lf",&p[i].x,&p[i].y);  
        min_cover_circle(p,n,c,r);  
        printf("%.2lf %.2lf %.2lf\n",c.x,c.y,r);  
    }  
    return 0;  
}  

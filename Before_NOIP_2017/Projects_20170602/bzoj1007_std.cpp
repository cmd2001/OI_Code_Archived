#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#define eps 1e-8
using namespace std;
struct data{double a,b;int n;}l[50001];
data st[50001];bool ans[50001];
int top,n;
inline bool cmp(data a,data b)
{
	if(fabs(a.a-b.a)<eps)return a.b<b.b;
	else return a.a<b.a;
}
double crossx(data x1,data x2)
{return (x2.b-x1.b)/(x1.a-x2.a);}
void insert(data a)
{
	while(top)
	{
		if(fabs(st[top].a-a.a)<eps)top--;
		else if(top>1&&crossx(a,st[top-1])<=crossx(st[top],st[top-1]))
			top--;
		else break;
	}
	st[++top]=a;
}
void work()
{
	for(int i=1;i<=n;i++)insert(l[i]);
    for(int i=1;i<=top;i++)ans[st[i].n]=1;
    for(int i=1;i<=n;i++)
       if(ans[i])printf("%d ",i);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
	    scanf("%lf%lf",&l[i].a,&l[i].b);
	    l[i].n=i;
    }
    sort(l+1,l+n+1,cmp);
    work();
	return 0;
}

#include<iostream>
#include<cstdio>
#include<cstring>
#define debug cout
using namespace std;
const int maxn=3e2+1e2;
const double eps=1e-6;

int l,m,n;
double p[maxn],d[maxn];
double pos,ans;
double now,lam;

double fabs(double x)
{
	return x<0?-x:x;
}

inline double judge(double s)
{
	
	if(s<0||s>l-d[n]) return -1.0;
	double ret=0;
	int door=1;
	for(int i=1;i<=m;i++)
	{
		while(door<n&&fabs(d[door]+s-p[i])>fabs(d[door+1]+s-p[i])) door++;
		ret+=fabs(d[door]+s-p[i]);
		//if(fabs(s-0.5)<=eps) debug<<"person "<<i<<"	into door "<<door<<endl;
	}
	//if(fabs(s-3397166.5)<=eps) debug<<"s="<<"3397166.5"<<"ret=",printf("%f\n",ret);
	return ret;
}
	



inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}

int main()
{
	ans=-1.0,pos=-1.0;
	l=getint(),m=getint();
	for(int i=1;i<=m;i++) p[i]=getint();
	n=getint();
	for(int j=2;j<=n;j++) d[j]=getint();
	
	for(int i=1;i<=m;i++) // selecting person x
		for(int j=1;j<=n;j++) // x is facing door j or door (i+j)/2
		{
			now=d[j];
			now=p[i]-now;
			lam=judge(now);
			if(fabs(lam-ans)>eps&&lam>ans)
			{
				pos=now;
				ans=lam;
			}
			else if(fabs(lam-ans)<eps)
			{
				pos=min(pos,now);
			}
			if(j!=n)
			{
				now=(d[j]+d[j+1])/2.0;
				now=p[i]-now;
				lam=judge(now);
				if(fabs(lam-ans)>eps&&lam>ans)
				{
					pos=now;
					ans=lam;
				}
				else if(fabs(lam-ans)<eps)
				{
					pos=min(pos,now);
				}
			}
		}
	
	now=0.0,lam=judge(now);
	if(fabs(lam-ans)>eps&&lam>ans)
	{
		pos=now;
		ans=lam;
	}
	now=l-d[n],lam=judge(now);
	if(fabs(lam-ans)>eps&&lam>ans)
	{
		pos=now;
		ans=lam;
	}
	
	printf("%0.1f %0.1f\n",pos,ans);
	
	return 0;
}

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=1e5+1e2;
const double eps=1e-6;

struct node
{
	double real;
	long long int tme;
	node(double rr=0,int tt=0) {real=rr,tme=tt;}
	friend node operator * (const node &a,const node &b)
	{
		node ret(a.real*b.real,a.tme+b.tme);
		if(fabs(ret.real)>eps)
		{
			while(fabs(ret.real)<1) ret.real*=10,ret.tme--;
			while(fabs(ret.real)>10) ret.real/=10,ret.tme++;
		}
		return ret;
	}
	friend bool operator < (const node &a,const node &b)
	{
		if(a.real<=0&&b.real>=0) return 1;
		if(a.real>=0&&b.real<=0) return 0;
		if(a.real<0&&b.real<0)
		{
			if(a.tme!=b.tme) return a.tme>b.tme;
			return a.real<b.real;
		}
		else
		{
			if(a.tme!=b.tme) return a.tme<b.tme;
			return a.real<b.real;
		}
	}
	void in()
	{
		scanf("%lf",&real);
		if(fabs(real)>eps)
		{
			while(fabs(real)<1) real*=10,tme--;
			while(fabs(real)>10) real/=10,tme++;
		}
	}
	void print()
	{
		if(fabs(real)<eps) printf("%0.3f\n",real+eps);
		else if(tme) printf("%0.3fE%d\n",real,tme);
		else printf("%0.3f\n",real);
	}
};
	
		

int n,tme;
node in[maxn],ans;
node f[maxn][2];

inline void update(int pos)
{
	f[pos][0]=max(in[pos],max(in[pos]*f[pos-1][1],in[pos]*f[pos-1][0]));
	f[pos][1]=min(in[pos],min(in[pos]*f[pos-1][1],in[pos]*f[pos-1][0]));
	ans=max(ans,max(f[pos][0],f[pos][1]));
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		in[i].in();
	
	ans=f[1][1]=f[1][0]=in[1];
	
	for(int i=2;i<=n;i++)
		update(i);
	
	ans.print();

	
	return 0;
}

	

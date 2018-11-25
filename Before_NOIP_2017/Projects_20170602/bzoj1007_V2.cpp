#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=5e5+1e2;
const double eps=1e-7;

inline int judge(const double &a)
{
	if(fabs(a)<eps) return 0;
	return a<0?-1:1;
}
struct lie
{
	int id;
	double k,b;
	lie(double kk=0,double bb=0,int idd=0) {k=kk,b=bb,id=idd;}
	friend bool operator < (const lie &a,const lie &b)
	{
		if(!judge(a.k-b.k)) return a.b>b.b;
		return a.k<b.k;
	}
}line[maxn],s[maxn];

int n,top;
bool ans[maxn];

double get_cross(const lie &a,const lie &b)
{
	return (b.b-a.b)/(a.k-b.k);
}


int main()
{
	//static double cross=-1e20;
	scanf("%d",&n);
	for(int i=1,k,b;i<=n;i++)
	{
		scanf("%d%d",&k,&b);
		line[i]=lie(k,b,i);
	}
	sort(line+1,line+1+n);
	s[++top]=line[1];
	for(int i=2;i<=n;i++)
	{
		while(top)
		{
			//debug<<"this cross="<<get_cross(line[i],s[top])<<endl<<"last cross="<<get_cross(s[top],s[top-1])<<endl;
			if(top>1&&judge(get_cross(line[i],s[top])-get_cross(s[top],s[top-1]))>0) break;
			if(top==1&&judge(line[i].k-s[top].k)!=0)
			{
				//debug<<"k!=k"<<endl;
				break;
			}
			if(judge(line[i].k-s[top].k)==0) break;
			top--;
		}
		//debug<<"before insert top="<<top<<endl;
		if(top==0||judge(line[i].k-s[top].k)!=0) s[++top]=line[i];
		//debug<<"top="<<top<<endl;
	}
	while(top)
	{
		ans[s[top].id]=1;
		top--;
	}
	for(int i=1;i<=n;i++) if(ans[i]) printf("%d ",i);
	return 0;
}

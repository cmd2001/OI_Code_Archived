#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define si scanf
#define so printf
#define N 
#define INF  
#define mod %m
template<typename TP>inline bool rd(TP& r)
{
	r=0;
	char tmp=getchar();
	while(tmp<'0'||tmp>'9')
	{
		if(tmp==EOF)
			return 0;
		tmp=getchar();
	}
	while('0'<=tmp&&tmp<='9')
	{
		r=(r<<3)+(r<<1)+tmp-'0';
		tmp=getchar();
	}
	return 1;
	
} 

long long n,m;
struct mat
{
	int x,y;
	long long a[30][30];
	mat(int xx=0,int yy=0)
	{
		x=xx;
		y=yy;
		memset(a,0,sizeof(a));
	}
	mat operator * (mat b)
	{
		mat c=mat(b.x,y);
		for(int i=0;i<=c.y;i++)
		for(int j=0;j<=c.x;j++)
		{
			for(int k=0;k<=x;k++)
				c.a[i][j]=(c.a[i][j]+a[i][k]*b.a[k][j] mod)mod;
		}
		return c;
	}
	void print()
	{
		for(int i=0;i<=y;i++)
		{
			for(int j=0;j<=x;j++)
				so("%lld ",a[i][j]);
			so("\n");
		}
		so("\n\n");
	}
};
mat power(mat ori,long long p)
{
	mat re=mat(ori.x,ori.y);
	for(int i=1;i<=re.x;i++)
		re.a[i][i]=1;
	while(p>0)
	{
		if(p&1)
			re=re*ori;
		p>>=1;
		ori=ori*ori;
	}
	//re.print();
	return re;
}
/*
	0上面必须是1，其他上面必须不是1 
	0000
	0001
	0010
	0011
	0100
	0101
	0110
	0111
	1000
	1001
	1010
	1011
	1100
	1101
	1110
	1111
	002
	012
	102
	112
	020
	021
	120
	121
	200
	201
	210
	211
	22
	
	
	
	
	1111
	112
	121
	211
	22
*/
int h[3000];
int a[5],b[5],ta[5],tb[5];
mat mult,ori;
void dfs2(int now,int done,int l)
{
	if(done>4)
		return;
	if(done==4)
	{
		int i=1,j=0;
		for(;i<=now-1;i++)
		{
			if(b[i]==2)
			{
				tb[++j]=0;
				tb[++j]=0;
			}
			else
				tb[++j]=b[i];
		}
		bool fail=0;
		for(int i=1;i<=4;i++)
			if(ta[i]==tb[i])
				fail=1;
		if(!fail)
		{
			int ra=0,rb=0;
			for(int i=1;i<=l;i++)
				ra=ra*10+a[i];
			for(int i=1;i<=now-1;i++)
				rb=rb*10+b[i];
			ra=h[ra];
			rb=h[rb];
			mult.a[rb][ra]=1;
		}
		return;
	}
	for(int i=0;i<=2;i++)
	{
		b[now]=i;
		if(i==2)
			dfs2(now+1,done+2,l);
		else
			dfs2(now+1,done+1,l);
	}
	b[now]=0;
}
void dfs1(int now,int done)
{
	if(done>4)
		return;
	if(done==4)
	{
		int i=1,j=0;
		for(;i<=now-1;i++)
		{
			if(a[i]==2)
			{
				ta[++j]=1;
				ta[++j]=1;
			}
			else
				ta[++j]=a[i];
		}
		dfs2(1,0,now-1);
		return;
	}
	for(int i=0;i<=2;i++)
	{
		a[now]=i;
		if(i==2)
			dfs1(now+1,done+2);
		else
			dfs1(now+1,done+1);
	}
	a[now]=0;
}
void prepare()
{
	h[0]=0;
	h[1]=1;
	h[10]=2;
	h[11]=3;
	h[100]=4;
	h[101]=5;
	h[110]=6;
	h[111]=7;
	h[1000]=8;
	h[1001]=9;
	h[1010]=10;
	h[1011]=11;
	h[1100]=12;
	h[1101]=13;
	h[1110]=14;
	h[1111]=15;
	h[2]=16;
	h[12]=17;
	h[102]=18;
	h[112]=19;
	h[20]=20;
	h[21]=21;
	h[120]=20;
	h[121]=21;
	h[200]=22;
	h[201]=23;
	h[210]=24;
	h[211]=25;
	h[22]=26;
	ori=mat(26,0);
	mult=mat(26,26);
	dfs1(1,0);
	/*
		1111
		112
		121
		211
		22
	*/
	ori.a[0][h[1111]]=1;
	ori.a[0][h[112]]=1;
	ori.a[0][h[121]]=1;
	ori.a[0][h[211]]=1;
	ori.a[0][h[22]]=1;
}
long long dp()
{
	
	/*
		0000
		002
		020
		200
		22
	*/
	mat tmp=ori;
	tmp=tmp*power(mult,n-1);
	return tmp.a[0][h[0]]+tmp.a[0][h[2]]+tmp.a[0][h[20]]+tmp.a[0][h[200]]+tmp.a[0][h[22]];
}
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	prepare();
	while(1)
	{
		rd(n);
		rd(m);
		if(n==0&&m==0)
			break;
		so("%lld\n",dp());
	}
	
	
	return 0;	
	
} 

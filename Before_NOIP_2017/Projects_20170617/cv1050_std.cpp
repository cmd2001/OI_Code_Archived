#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdlib>
using namespace std;

const int inf=0x3f3f;
int n,maxn,maxm;
int lim,cur;
int dp[2][1<<13];
int map[110][7];
char inp[7];
bool finda;

void trans(int &k,int lar,int sm)//将一个状态中为lar的数都转化为sm。lar保证比sm大。 
{
	for(int i=0;i<6;i++)
	{
		if(((k>>(i<<1))&3)==lar)
		{
			k=k^(lar<<(i<<1))^(sm<<(i<<1));
		}
	}
}

void prom(int &k)//检查1有几种，如果有3没有2，则把3都变为2，以确保下一次增加进来的新的1在上方为0时直接赋值为3是正确的。 
{
	bool f2=false,f3=false;
	for(int i=0;i<5;i++)
	{
		if(((k>>(i<<1))&3)==2)f2=true;
		if(((k>>(i<<1))&3)==3)f3=true;
	}
	if(!f2 && f3 && finda)trans(k,3,2);
	else if(!f2 && f3 && !finda)
	{
		trans(k,3,1);
		finda=true;
	}
}

bool checka(int k)
{
	for(int i=0;i<5;i++)
	{
		if(((k>>(i<<1))&3)>1)return false;//如果有大于1的数，说明该状态有1没有和其他的连在一起，不合法。 
	}
	return true;
}

void getans()//获取答案。 
{
	int ans=inf;
	for(int k=0;k<lim-1;k++)if(checka(k))//check确定该状态是合法。 
	{
		ans=min(ans,dp[cur][k]);
	}
	printf("%d\n",ans);
}

void update(int a,int b,int type,int row)
{
	if(type>=1 && row>0)
	{
		int cur1=(a&3),cur2=(b&3);
		if(cur1!=cur2 && cur1>0)trans(b,max(cur1,cur2),min(cur1,cur2));
	}
	
	bool flag=true;
	int cnt=0;
	int check=(b>>10);
	if(a>0)
	{
		flag=false;
		if(check>1)cnt=1;
		for(int i=0;i<5;i++)
		{
			if(((b>>(i<<1))&3)==1)flag=true;
			if(check>1 && ((b>>(i<<1))&3)==check)cnt++;
		}
	}
	prom(b);
	
	if(flag==true && cnt!=1)
	{
		dp[cur][b^((b>>10)<<10)]=min(dp[cur][b^((b>>10)<<10)],dp[1-cur][a]+(type==2 ? 1 : 0));
	}
	else dp[cur][b^((b>>10)<<10)]=min(dp[cur][b^((b>>10)<<10)],inf);
}

int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		scanf("%s",inp);
		for(int j=0;j<5;j++)
		{
			map[i][j]=inp[j]-'0';
			if(map[i][j])maxn=i,maxm=j;
		}
	}
	memset(dp,inf,sizeof(dp));//给数组赋初始值为无限大（超过500即可）。 
		cur=0;//当前状态。 
		lim=1<<(5<<1);//每个阶段处理完毕后保存的最大状态，由于是使用四进制所以有10位而不是5位。 
		dp[0][0]=0;//在第0排前额外添加一排，其数字都为0。除了00000这个状态以外的状态大小都为无限大，该状态为0。 
		finda=false;//用于第一次找到1时赋值为1而非2。 
	
	for(int i=0;i<n;i++) 
	{
		for(int j=0;j<5;j++)//枚举阶段。 
		{
			if(!finda && !map[i][j])continue;
			if(i>maxn || (i>=maxn && j>maxm))break;//如果超过了最后一个1的界限直接退出。 
			cur^=1;//状态转换。 
			memset(dp[cur],inf,sizeof(dp[cur]));//初始化该状态值都为最大。 
			for(int k=0;k<lim;k++)//枚举上一阶段所有状态。 
			{
				if(map[i][j])update(k,(k<<2)^((k>>8)>0 ? (k>>8) : (((k&3)>0 && j) ? (k&3) : 3)),1,j);//如果该点是1，直接加入状态，由于是四进制，要确定新加节点上方的为0还是1要右推8位。 
				else//为0。 
				{
					update(k,(k<<2)^((k>>8)>0 ? (k>>8) : (((k&3)>0 && j) ? (k&3) : 3)),2,j);//改成1。 
					update(k,k<<2,0,j);//不改，直接加入。 
				}
			}
		}
	}
	getans();
	
	return 0;
}

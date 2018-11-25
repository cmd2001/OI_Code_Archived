#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define M 100100
using namespace std;
int n,c,m,block,ans,a[M];
int block_ans[320][320],block_cnt[320][M];
int f[M],tim[M],tot;
int stack[M],top;
int main()
{
    freopen("dat.txt","r",stdin);
    freopen("std.txt","w",stdout);
	int i,j,x,y;
	cin>>n>>c>>m;
	for(i=1;i<=n;i++)
		scanf("%d",&a[i]);
	block=static_cast<int>(sqrt(n)+1e-7);
	for(i=1;i<=block;i++)
	{
		++tot;
		int cnt=0;
		for(j=i*block+1;j<=n;j++)
		{
			int temp=a[j];
			if(tim[temp]!=tot)
				tim[temp]=tot,f[temp]=0;
			f[temp]++;
			if(~f[temp]&1&&f[temp])
				++cnt;
			else if(f[temp]&1&&f[temp]>=3)
				--cnt;
			if(j%block==0)
				block_ans[i][j/block]=cnt;
		}
	}
	for(i=1;i<=n;i++)
	{
		int temp=a[i];
		block_cnt[(i-1)/block][temp]++;
	}
	for(i=1;i*block+1<=n;i++)
		for(j=1;j<=c;j++)
			block_cnt[i][j]+=block_cnt[i-1][j];
	for(i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		x=(x+ans)%n+1;
		y=(y+ans)%n+1;
		if(x>y) swap(x,y);
		ans=0;
		if(y-x+1<=block<<1)
		{
			top=0;
			for(j=x;j<=y;j++)
				stack[++top]=a[j];
			sort(stack+1,stack+top+1);
			int cnt=0;
			for(j=1;j<=top;j++)
			{
				++cnt;
				if(stack[j]!=stack[j+1]||j==top)
					ans+=(cnt&&~cnt&1),cnt=0;
			}
			printf("%d\n",ans);
			continue;
		}
		int b1=(x-1)/block+1;
		int b2=(y-1)/block;
		ans=block_ans[b1][b2];
		top=0;
		for(j=x;j<=b1*block;j++)
			stack[++top]=a[j];
		for(j=b2*block+1;j<=y;j++)
			stack[++top]=a[j];
		sort(stack+1,stack+top+1);
		int cnt=0;
		for(j=1;j<=top;j++)
		{
			++cnt;
			if(stack[j]!=stack[j+1]||j==top)
			{
				int temp=block_cnt[b2-1][ stack[j] ]-block_cnt[b1-1][ stack[j] ];
				if(!temp&&~cnt&1)
					++ans;
				else if(temp&1&&cnt&1)
					++ans;
				else if(~temp&1&&temp&&cnt&1)
					--ans;
				cnt=0;
			}
		}
		printf("%d\n",ans);
	}
}

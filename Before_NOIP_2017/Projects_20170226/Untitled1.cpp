#include<cstdio>
#include<cstring>
#define debug cout
#define inf xx2+1
using namespace std;
struct node
{
	int dx,dy;
}vec[5010],tmp,tmpx;
int l[5010],ans[5010];
int m,n,xx1,yy1,xx2,yy2;
int multi(const node &a,const node &b)
{
	return a.dx*b.dy-b.dx*a.dy;
}
signed main()
{
	while(scanf("%d%d%d%d%d%d",&n,&m,&xx1,&yy2,&xx2,&yy1)==6&&n)
	{
		memset(vec,0,sizeof(vec));
		memset(l,0,sizeof(l));
		memset(ans,0,sizeof(ans));
		vec[0].dy=yy2-yy1;
		vec[0].dx=0;
		l[0]=0;
		for(int i=1,u,v;i<=n;i++)
		{
			scanf("%d%d",&u,&v);
			vec[i].dy=yy2-yy1;
			vec[i].dx=u-v;
			l[i]=v;
		}
		l[n+1]=inf;
		vec[n+1].dx=0;
		vec[n+1].dy=yy2-yy1;
		for(int i=1,x,y;i<=m;i++)
		{
			scanf("%d%d",&x,&y);
			for(int j=0;j<=n;j++)
			{
				tmp.dx=x-l[j];
				tmp.dy=y-yy1;
				tmpx.dx=x-l[j+1];
				tmpx.dy=y-yy1;
				if(multi(tmp,vec[j])>0&&multi(tmpx,vec[j+1])<0)
				{
					ans[j]++;
					break;
				}
			}
		}
		for(int i=0;i<=n;i++) printf("%d: %d\n",i,ans[i]);
		printf("\n");
	}
	return 0;
}

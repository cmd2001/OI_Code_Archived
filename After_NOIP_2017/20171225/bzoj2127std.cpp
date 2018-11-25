#include<iostream>
#include<cstring>
#include<cstdio>
#define T 10001
#define inf 0x7fffffff
#define FOR for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
#define rep(x,y) for(int i=1;i<=x;i++)for(int j=1;j<=y;j++)
#define ll long long
using namespace std;
int n,m,ans,tot,cnt=1,head[10002],h[10002];
int a[101][101],b[101][101],color[101][101],mark[101][101];
int xx[4]={0,0,1,-1},yy[4]={1,-1,0,0};
struct data{int to,next,v;}e[300001];
void ins(int u,int v,int w)
{cnt++;e[cnt].to=v;e[cnt].v=w;e[cnt].next=head[u];head[u]=cnt;}
void insert(int u,int v,int w)
{ins(u,v,w);ins(v,u,0);}
void ins2(int u,int v,int w)
{ins(u,v,w);ins(v,u,w);}
bool bfs()
{
     int q[10005],t=0,w=1,i,now;
     memset(h,-1,sizeof(h));
     q[0]=h[0]=0;
     while(t!=w)
     {
            now=q[t];t++;if(t==10001)t=0;
            for(i=head[now];i;i=e[i].next)
            {
                  if(e[i].v&&h[e[i].to]<0)
                        {h[e[i].to]=h[now]+1;q[w++]=e[i].to;if(w==10001)w=0;}
             }
     }
     if(h[T]==-1)return 0;return 1;
     }
int dfs(int x,int f)
{
    if(x==T)return f;
    int w,used=0;
    for(int i=head[x];i;i=e[i].next)
    {
            if(e[i].v&&h[e[i].to]==h[x]+1)
            {
                w=f-used;
                w=dfs(e[i].to,min(w,e[i].v));   
                e[i].v-=w;e[i^1].v+=w;
                used+=w;if(used==f)return f;                      
                }
            }
    if(!used)h[x]=-1;
    return used;
    }
void dinic(){while(bfs())ans+=dfs(0,inf);}
void build()
{
	int x;
	rep(n-1,m)
	{
	   scanf("%d",&x);tot+=x;
	   a[i][j]+=x;a[i+1][j]+=x;
	   ins2(mark[i][j],mark[i+1][j],x);
	   }
	rep(n-1,m)
	{
	   scanf("%d",&x);tot+=x;
	   b[i][j]+=x;b[i+1][j]+=x;
	   ins2(mark[i][j],mark[i+1][j],x);
	   }
	rep(n,m-1)
	{
	   scanf("%d",&x);tot+=x;
	   a[i][j]+=x;a[i][j+1]+=x;
	   ins2(mark[i][j],mark[i][j+1],x);
	   }
	rep(n,m-1)
	{
	   scanf("%d",&x);tot+=x;
	   b[i][j]+=x;b[i][j+1]+=x;
	   ins2(mark[i][j],mark[i][j+1],x);
	   }
	FOR{
		   insert(0,mark[i][j],a[i][j]);
		   insert(mark[i][j],T,b[i][j]);
	   }
}
int main()
{
	
	freopen("dat.txt","r",stdin);
	scanf("%d%d",&n,&m);
	FOR scanf("%d",&a[i][j]),tot+=a[i][j],a[i][j]<<=1;
	FOR scanf("%d",&b[i][j]),tot+=b[i][j],b[i][j]<<=1;
	FOR mark[i][j]=(i-1)*m+j;
	build();dinic();
	printf("%d",tot-(ans>>1));
	return 0;
}

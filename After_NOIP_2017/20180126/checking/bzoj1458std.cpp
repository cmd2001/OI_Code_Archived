#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define T 201
#define inf 0x7fffffff
inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(!(ch>='0'&&ch<='9')){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
    return x*f;
}
using namespace std;
int n,m,K,cnt=1,tot,ans;
int l[105],c[105],a[105],b[105];
bool mp[105][105];
int q[205],h[205],head[205],cur[205];
struct data{int to,next,v;}e[100001];
void ins(int u,int v,int w)
{e[++cnt].to=v;e[cnt].next=head[u];e[cnt].v=w;head[u]=cnt;}
void insert(int u,int v,int w)
{ins(u,v,w);ins(v,u,0);}
bool bfs()
{
    int t=0,w=1;
    for(int i=0;i<=T;i++)h[i]=-1;
    q[0]=0;h[0]=0;
    while(t!=w)
    {
        int now=q[t];t++;
        for(int i=head[now];i;i=e[i].next)
            if(e[i].v&&h[e[i].to]==-1)
            {
                h[e[i].to]=h[now]+1;
                q[w++]=e[i].to;
            }
    }
    if(h[T]==-1)return 0;
    return 1;
}
int dfs(int x,int f)
{
    if(x==T)return f;
    int w,used=0;
    for(int i=cur[x];i;i=e[i].next)
    {
        if(e[i].v&&h[e[i].to]==h[x]+1)
        {
            w=f-used;
            w=dfs(e[i].to,min(e[i].v,w));
            e[i].v-=w;
            if(e[i].v)cur[x]=i;
            e[i^1].v+=w;
            used+=w;if(used==f)return f;
        }
    }
    if(!used)h[x]=-1;
    return used;
}
void dinic()
{while(bfs()){for(int i=0;i<=T;i++)cur[i]=head[i];ans+=dfs(0,inf);}}
int main()
{
    m=read();n=read();K=read();
    int x,y;
	for(int i=1;i<=m;i++)
	    l[i]=n-read();
    for(int i=1;i<=n;i++)
        c[i]=m-read();
    for(int i=1;i<=K;i++)
    {
    	x=read();y=read();
    	mp[x][y]=1;
    	a[x]++;b[y]++;
    	if(a[x]>l[x]){printf("JIONG!\n");return 0;}
    	if(b[y]>c[y]){printf("JIONG!\n");return 0;}
    }
    tot=n*m-K;
    for(int i=1;i<=m;i++)
	    insert(0,i,l[i]-a[i]);
	for(int i=1;i<=n;i++)
	    insert(m+i,T,c[i]-b[i]); 
	for(int i=1;i<=m;i++)
	    for(int j=1;j<=n;j++)
	        if(!mp[i][j])insert(i,j+m,1);
    dinic();
    printf("%d\n",tot-ans);
    return 0;
}

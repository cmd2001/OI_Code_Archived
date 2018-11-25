#include<iostream>  
#include<cstdio>  
#include<cstdlib>  
#include<cstring>  
#include<cmath>  
#include<algorithm>  
#include<queue>  
#define F(i,j,n) for(int i=j;i<=n;i++)  
#define D(i,j,n) for(int i=j;i>=n;i--)  
#define ll long long  
#define pa pair<int,int>  
#define maxn 10100  
#define maxm 100100  
#define inf 1000000000  
#define f(x,y) (x-1)*m+y  
using namespace std;  
struct edge_type  
{  
    int next,to,v;  
}e[maxm];  
int head[maxn],cur[maxn],dis[maxn],a[105][105];  
int n,m,s,t,x,cnt=1,ans=0,tot=0;  
inline int read()  
{  
    int x=0,f=1;char ch=getchar();  
    while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}  
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}  
    return x*f;  
}  
inline void add_edge(int x,int y,int v1,int v2)  
{  
    e[++cnt]=(edge_type){head[x],y,v1};head[x]=cnt;  
    e[++cnt]=(edge_type){head[y],x,v2};head[y]=cnt;  
}  
inline bool bfs()  
{  
    queue<int>q;  
    memset(dis,-1,sizeof(dis));  
    dis[s]=0;q.push(s);  
    while (!q.empty())  
    {  
        int tmp=q.front();q.pop();  
        if (tmp==t) return true;  
        for(int i=head[tmp];i;i=e[i].next) if (e[i].v&&dis[e[i].to]==-1)  
        {  
            dis[e[i].to]=dis[tmp]+1;  
            q.push(e[i].to);  
        }  
    }  
    return false;  
}  
inline int dfs(int x,int f)  
{  
    if (x==t) return f;  
    int tmp,sum=0;  
    for(int &i=cur[x];i;i=e[i].next)  
    {  
        int y=e[i].to;  
        if (e[i].v&&dis[y]==dis[x]+1)  
        {  
            tmp=dfs(y,min(f-sum,e[i].v));  
            e[i].v-=tmp;e[i^1].v+=tmp;sum+=tmp;  
            if (sum==f) return sum;  
        }  
    }  
    if (!sum) dis[x]=-1;  
    return sum;  
}  
inline void dinic()  
{  
    while (bfs())  
    {  
        F(i,1,t) cur[i]=head[i];  
        ans+=dfs(s,inf);  
    }  
}  
int main()  
{  
    
    freopen("dat.txt","r",stdin);
    n=read();m=read();  
    s=n*m+1;t=s+1;  
    F(i,1,n) F(j,1,m)  
    {  
        x=read();  
        tot+=x;  
        if ((i+j)&1) add_edge(s,f(i,j),x,0);  
        else add_edge(f(i,j),t,x,0);  
    }  
    F(i,1,n) F(j,1,m)  
    {  
        x=read();  
        tot+=x;  
        if ((i+j)&1) add_edge(f(i,j),t,x,0);  
        else add_edge(s,f(i,j),x,0);  
    }  
    F(i,1,n) F(j,1,m) a[i][j]=read();  
    F(i,1,n) F(j,1,m-1)  
    {  
        int tmp=a[i][j]+a[i][j+1];  
        tot+=tmp;  
        add_edge(f(i,j),f(i,j+1),tmp,tmp);  
    }  
    F(i,1,n-1) F(j,1,m)  
    {  
        int tmp=a[i][j]+a[i+1][j];  
        tot+=tmp;  
        add_edge(f(i,j),f(i+1,j),tmp,tmp);  
    }  
    dinic();  
    printf("%d\n",tot-ans);  
}  
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#define inf 0x7fffffff
using namespace std;
struct heap{int v,x;}h[200010];
int n,m,a[100010];
long long tmp,sz,ans,tot;
int v[100010],cnt;
int next[100010],pre[100010],pos[100010];
inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(!(ch>='0'&&ch<='9')){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
    return x*f;
}
void pushup(int x)
{
    while(h[x].v<h[x>>1].v)
    {
        pos[h[x>>1].x]=x;
        swap(h[x],h[x>>1]);
        x=x>>1;
    }
    pos[h[x].x]=x;
}
void push(int v,int x)
{
    sz++;h[sz].v=v;h[sz].x=x;
    pos[x]=sz;
    pushup(sz);
}
void pushdown(int x)
{
    int to;
    while((x<<1)<=sz)
    {
        to=(x<<1);
        if(to<sz&&h[to].v>h[to+1].v)to++;
        if(h[x].v>h[to].v)
        {
            pos[h[to].x]=x;
            swap(h[to],h[x]);
            x=to;
        }
        else break;  
    }
    pos[h[x].x]=x;
}
void del(int x)
{
    h[x].v=inf;
    pushdown(x);
}
void init()
{
    n=read();m=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    for(int i=2;i<=n;i++)
    {
	    push(a[i]-a[i-1],i);
	    pre[i]=i-1;next[i]=i+1;
	}
	pre[2]=next[n]=-1;
}
void solve()
{
	int a,b;
    heap k;
    for(int i=1;i<=m;i++)
    {
    	 k=h[1];
    	 cout<<"k="<<k.v<<endl;
         if(pre[k.x]==-1)
         {
             ans+=k.v;
             del(1);del(pos[next[k.x]]);
             pre[next[next[k.x]]]=-1;
         }
         else if(next[k.x]==-1)
         {
             ans+=k.v;
             del(1);del(pos[pre[k.x]]);
             next[pre[pre[k.x]]]=-1;
         }
         else
         {
             ans+=k.v;
             a=next[k.x];b=pre[k.x];
             pre[k.x]=pre[b];next[pre[b]]=k.x;
             next[k.x]=next[a];pre[next[a]]=k.x;
             h[1].v=h[pos[a]].v+h[pos[b]].v-h[1].v;
             pushdown(1);
             del(pos[a]);del(pos[b]);
         }
    }
    printf("%lld\n",ans);
}
int main()
{
    init();
    solve();
    return 0;
}

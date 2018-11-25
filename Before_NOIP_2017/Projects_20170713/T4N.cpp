#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e2+1e1;
const int delta=1e4+1e2;

struct square
{
    int lx,ly,rx,ry;
    int s,id;
    friend bool operator < (const square &a,const square &b)
    {
        return a.s!=b.s?a.s>b.s:a.id<b.id;
    }
}in[55];
int n,k;
int xsrt[maxn],ysrt[maxn],xlen,ylen;
bool used[maxn][maxn]; // used[i] => (srt[i],srt[i+1])
int ans[maxn];

inline void getin()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d%d",&in[i].lx,&in[i].ly,&in[i].rx,&in[i].ry);
        in[i].lx+=delta;
        in[i].rx+=delta;
        in[i].ly+=delta;
        in[i].ry+=delta;
        xsrt[++xlen]=in[i].lx,xsrt[++xlen]=in[i].rx;
        ysrt[++ylen]=in[i].ly,ysrt[++ylen]=in[i].ry;
        in[i].id=i-1;
    }
}

inline void init()
{
    sort(xsrt+1,xsrt+1+xlen);
    sort(ysrt+1,ysrt+1+ylen);
    xlen=unique(xsrt+1,xsrt+1+xlen)-xsrt-1;
    ylen=unique(ysrt+1,ysrt+1+ylen)-ysrt-1;
}

inline void mark(int x,int xx,int y,int yy)
{
    int sx=lower_bound(xsrt+1,xsrt+1+xlen,x)-xsrt,tx=lower_bound(xsrt+1,xsrt+1+xlen,xx)-xsrt,
        sy=lower_bound(ysrt+1,ysrt+1+ylen,y)-ysrt,ty=lower_bound(ysrt+1,ysrt+1+ylen,yy)-ysrt;

    for(int i=sx;i<tx;i++)
        for(int j=sy;j<ty;j++)
            used[i][j]=1;
}
inline lli calc(int x,int xx,int y,int yy)
{
    lli ret=0;
    int sx=lower_bound(xsrt+1,xsrt+1+xlen,x)-xsrt,tx=lower_bound(xsrt+1,xsrt+1+xlen,xx)-xsrt,
        sy=lower_bound(ysrt+1,ysrt+1+ylen,y)-ysrt,ty=lower_bound(ysrt+1,ysrt+1+ylen,yy)-ysrt;

    for(int i=sx;i<tx;i++)
        for(int j=sy;j<ty;j++)
        {
            if(!used[i][j]) ret+=(xsrt[i+1]-xsrt[i])*(ysrt[i+1]-ysrt[i]);
        }
    return ret;
}

inline void getans()
{
    for(int i=n;i;i--)
    {
        in[i].s=calc(in[i].lx,in[i].rx,in[i].ly,in[i].ry);
        mark(in[i].lx,in[i].rx,in[i].ly,in[i].ry);
    }
    /*for(int i=1;i<=n;i++)
    {
        debug<<"i="<<i<<"s="<<in[i].s<<endl;
    }*/
    sort(in+1,in+1+n);
    for(int i=1;i<=k;i++) ans[i]=in[i].id;
    sort(ans+1,ans+1+k);
    for(int i=1;i<k;i++) printf("%d ",ans[i]);
    printf("%d\n",ans[k]);
}





int main()
{
    getin();
    init();
    getans();
    return 0;
}





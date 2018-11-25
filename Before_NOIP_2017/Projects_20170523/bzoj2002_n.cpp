//Cv2333_By_Cmd2001
#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=2e5+1e1;
int in[maxn],tme[maxn],to[maxn],bel[maxn];
int s[510],e[510],cnt,n,m,sq;
inline void build()
{
    sq=sqrt(n);
    s[1]=1,e[1]=sq;
    for(int i=1;i<=n;i++)
    {
        if(i>cnt*sq) cnt++,s[cnt]=(cnt-1)*sq+1,e[cnt]=min(cnt*sq,n);
        bel[i]=cnt;
    }
    for(int i=n;i>0;i--)
    {
        if(i+in[i]>e[bel[i]])
        {
            to[i]=i+in[i];
            tme[i]=1;
        }
        else
        {
            to[i]=to[i+in[i]];
            tme[i]=tme[i+in[i]]+1;
        }
    }
}
inline void update(int pos,int x)
{
    in[pos]=x;
    int st=s[bel[pos]];
    for(int i=pos;i>=st;i--)
    {
        if(i+in[i]>e[bel[i]])
        {
            to[i]=i+in[i];
            tme[i]=1;
        }
        else
        {
            to[i]=to[i+in[i]];
            tme[i]=tme[i+in[i]]+1;
        }
    }
}
inline int query(int pos)
{
    int ret=0;
    while(pos<=n)
    {
        ret+=tme[pos];
        pos=to[pos];
    }
    return ret;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    build();
    scanf("%d",&m);
    for(int i=1,c,pos,x;i<=m;i++)
    {
        scanf("%d%d",&c,&pos);
        ++pos;
        if(c==1) printf("%d\n",query(pos));
        else
        {
            scanf("%d",&x);
            update(pos,x);
        }
    }
    return 0;
}


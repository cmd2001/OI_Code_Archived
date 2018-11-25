#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=2e5+1e2,maxq=5e2+1e1;
int in[maxn],bls[maxn],ble[maxn],to[maxn],tme[maxn];
int n,m,sq,cnt;
inline void build()
{
    int k=0;
    for(int i=1;i<=n;i++)
    {
        if(i>(k+1)*sq) k++;
        bls[i]=k*sq+1;
        ble[i]=min((k+1)*sq,n);
    }
    for(int i=n;i>0;i--)
    {
        if(i+in[i]>ble[i])
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
    for(int i=pos;i>=bls[i];i--)
    {
        if(i+in[i]>ble[i])
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
        //debug<<"pos="<<pos<<endl;
    }
    return ret;
}
int main()
{
    scanf("%d",&n);
    sq=sqrt(n);
    for(int i=1;i<=n;i++) scanf("%d",&in[i]);
    build();
    /*for(int i=1;i<=n;i++) debug<<ble[i]<<endl;
    for(int i=1;i<=n;i++) debug<<to[i]<<endl;*/
    //for(int i=1;i<=n;i++) debug<<bls[i]<<endl;
    scanf("%d",&m);
    for(int i=1,c,pos,x;i<=m;i++)
    {
        scanf("%d%d",&c,&pos);
        pos++;
        if(c==1) printf("%d\n",query(pos));
        else if(c==2)
        {
            scanf("%d",&x);
            update(pos,x);
        }
    }
    return 0;
}

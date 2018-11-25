#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+1e2;
int in[maxn],vis[maxn],n,k,m,t,ans,st,mi,mx,mip,mxp,now;

int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&k);
        memset(in,0,sizeof(in));
        memset(vis,0,sizeof(vis));
        ans=1,st=1;
        for(int i=1;i<=n;i++) scanf("%d",in+i);
        for(int i=st;i<=n;i++)
        {
            for(int j=i+1;j<=n;j++)
            {
                memset(vis,0,sizeof(vis));
                now=0;
                for(int l=1;l<=m&&l<=(j-i+1)>>1;l++)
                {
                    mx=0,mi=0x3f3f3f3f;
                    for(int k=i;k<=j;k++)
                    {
                        if(in[k]<mi&&!vis[k]) mi=in[k],mip=k;
                        if(in[k]>mx&&!vis[k]) mx=in[k],mxp=k;
                    }
                    now+=(mx-mi)*(mx-mi);
                    vis[mip]=vis[mxp]=1;
                }
                if(now>k)
                {
                    st=j,ans++;
                    i=st;
                    break;
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}




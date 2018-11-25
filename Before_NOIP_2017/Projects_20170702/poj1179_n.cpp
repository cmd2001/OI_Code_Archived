#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e2;

int in[maxn],ope[maxn],n,ans=0xffffffff;
int f[maxn][maxn][2];
char c[5];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s%d",c,&in[i]);
        ope[i]=(*c=='t'?0:1); // 1 means *
    }
    for(int i=1;i<=n;i++)
    {
        in[n+i]=in[i];
        ope[n+i]=ope[i];
    }
    for(int i=1;i<(n<<1);i++) for(int j=1;j<(n<<1);j++) f[i][j][1]=0x3f3f,f[i][j][0]=-0x3f3f;
    for(int i=1;i<=(n<<1);i++) f[i][i][0]=f[i][i][1]=in[i];
    for(int len=1;len<=n;len++)
    {
        for(int st=1,ed;st+len<=(n<<1);st++)
        {
            ed=st+len;
            for(int k=st;k<ed;k++)
            {
                if(!ope[k+1])
                {
                    if(f[st][k][0]+f[k+1][ed][0]>f[st][ed][0]) f[st][ed][0]=f[st][k][0]+f[k+1][ed][0];
                    if(f[st][k][1]+f[k+1][ed][1]<f[st][ed][1]) f[st][ed][1]=f[st][k][1]+f[k+1][ed][1];
                }
                if(ope[k+1])
                {
                    if(f[st][k][0]*f[k+1][ed][0]>f[st][ed][0]) f[st][ed][0]=f[st][k][0]*f[k+1][ed][0];
                    if(f[st][k][1]*f[k+1][ed][1]>f[st][ed][0]) f[st][ed][0]=f[st][k][1]*f[k+1][ed][1];
                    if(f[st][k][1]*f[k+1][ed][0]<f[st][ed][1]) f[st][ed][1]=f[st][k][1]*f[k+1][ed][0];
                    if(f[st][k][0]*f[k+1][ed][1]<f[st][ed][1]) f[st][ed][1]=f[st][k][0]*f[k+1][ed][1];
                }
            }
            //debug<<"st="<<st<<"ed="<<ed<<"f1="<<f[st][ed][0]<<" f2="<<f[st][ed][1]<<endl;
        }
    }
    for(int i=1;i<=n;i++)
    {
        //debug<<"i="<<i<<"f="<<f[i][i+n][0]<<endl;
        ans=max(ans,f[i][i+n-1][0]);
    }
    printf("%d\n",ans);
    for(int i=1,t;i<=n;i++)
    {
        if(f[i][i+n-1][0]==ans)
        {
            t=i%n;
            printf("%d ",t?t:n);
        }

    }
    return 0;
}


#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e2;

int in[maxn],ope[maxn],n,ans=0xffffffff;
int f[maxn][maxn][2],from[maxn][maxn][2];
int sta[maxn][maxn][2];
int e[maxn],cnt;
char c[5];

inline void dfs(int st,int ed,int x)
{
    if(st==ed) return;
    if(ed==st+1)
    {
        e[++cnt]=st;
        return;
    }
    int k=from[st][ed][x],s=sta[st][ed][x];\
    dfs(st,k,s==1||s==4);
    dfs(k+1,ed,s==2||s==3);
}

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
                    if(f[st][k][0]+f[k+1][ed][0]>f[st][ed][0])
                    {
                        f[st][ed][0]=f[st][k][0]+f[k+1][ed][0];
                        from[st][ed][0]=k;
                        sta[st][ed][0]=1; // 1 means plus and above
                    }
                    if(f[st][k][1]+f[k+1][ed][1]<f[st][ed][1])
                    {
                        f[st][ed][1]=f[st][k][1]+f[k+1][ed][1];
                        from[st][ed][1]=k;
                        sta[st][ed][1]=2; // 2 means plus and below
                    }
                }
                if(ope[k+1])
                {
                    if(f[st][k][0]*f[k+1][ed][0]>f[st][ed][0])
                    {
                        f[st][ed][0]=f[st][k][0]*f[k+1][ed][0];
                        from[st][ed][0]=k;
                        sta[st][ed][0]=1; // 1 means double above
                    }
                    if(f[st][k][1]*f[k+1][ed][1]>f[st][ed][0])
                    {
                        f[st][ed][0]=f[st][k][1]*f[k+1][ed][1];
                        from[st][ed][0]=k;
                        sta[st][ed][0]=2; // 2 means double below
                    }
                    if(f[st][k][1]*f[k+1][ed][0]<f[st][ed][1])
                    {
                        f[st][ed][1]=f[st][k][1]*f[k+1][ed][0];
                        from[st][ed][1]=k;
                        sta[st][ed][1]=3; // 3 means below-above
                    }
                    if(f[st][k][0]*f[k+1][ed][1]<f[st][ed][1])
                    {
                        f[st][ed][1]=f[st][k][0]*f[k+1][ed][1];
                        from[st][ed][1]=k;
                        sta[st][ed][1]=4; // 4 means above-below
                    }
                }
            }
            debug<<"st="<<st<<"ed="<<ed<<"f1="<<f[st][ed][0]<<" f2="<<f[st][ed][1]<<endl;
        }
    }
    for(int i=1;i<=n;i++)
    {
        debug<<"i="<<i<<"f="<<f[i][i+n][0]<<endl;
        ans=max(ans,f[i][i+n-1][0]);
    }
    for(int i=1;i<=n;i++)
    {
        if(f[i][i+n-1][0]==ans) dfs(i,i+n-1,0);
    }
    printf("%d\n",ans);

    for(int i=1;i<=cnt;i++) debug<<e[i]<<" ";
    return 0;
}


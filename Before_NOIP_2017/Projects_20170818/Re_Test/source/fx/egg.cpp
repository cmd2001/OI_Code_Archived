#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+1e2;

int f[maxn][maxn],n,m;
inline int getlog(int x)
{
    int ret=-1;
    while(x)
    {
        ret++;
        x>>=1;
    }
    return ret;
}

int main()
{

scanf("%d%d",&n,&m);
    {
        memset(f,0x3f,sizeof(f));
        for(int i=0;i<=m;i++) f[0][i]=0;
        int l=getlog(n);
        if(l+1<=m) m=l+1;

        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                for(int k=1;k<=i;k++)
                    f[i][j]=min(f[i][j],max(f[k-1][j-1],f[i-k][j])+1);

        printf("%d\n",f[n][m]);
    }

    return 0;
}

